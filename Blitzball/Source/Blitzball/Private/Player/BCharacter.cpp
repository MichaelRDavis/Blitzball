// Fill out your copyright notice in the Description page of Project Settings.

#include "BCharacter.h"
#include "BPlayerState.h"
#include "BPlayerController.h"
#include "BCharacterMovement.h"
#include "BBlitzball.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"

#define RED_TEAM 254
#define BLUE_TEAM 253

ABCharacter::ABCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UBCharacterMovement>(ACharacter::CharacterMovementComponentName))
{
	//
	CameraBoom = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->CameraLagSpeed = 15.0f;
	CameraBoom->CameraRotationLagSpeed = 15.0f;
	CameraBoom->TargetArmLength = 350.0f;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->bEnableCameraRotationLag = true;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a CameraComponent
	FollowCamera = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FirstPersonCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 90.0f));
	FollowCamera->SetRelativeRotation(FRotator(-10.0f, 0.0f, 0.0f));
	FollowCamera->FieldOfView = 110.0f;
	FollowCamera->bUsePawnControlRotation = false;

	//
	CollisionComp = ObjectInitializer.CreateDefaultSubobject<UCapsuleComponent>(this, TEXT("CollisionComp"));
	CollisionComp->SetupAttachment(GetMesh());
	CollisionComp->SetRelativeLocation(FVector(0.0f, 80.0f, 45.0f));
	CollisionComp->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	CollisionComp->SetCapsuleSize(45.0f, 45.0f);
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ABCharacter::OnOverlapBegin);
	CollisionComp->OnComponentEndOverlap.AddDynamic(this, &ABCharacter::OnOverlapEnd);

	BCharacterMovement = Cast<UBCharacterMovement>(GetCharacterMovement());

	GetMesh()->SetCollisionObjectType(ECC_Pawn);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;
	GetMesh()->bReceivesDecals = false;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	KickImpulse = 350000.0f;

	MinNetUpdateFrequency = 100.0f;
	bAlwaysRelevant = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ABCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void ABCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (GetCharacterMovement()->MovementMode == MOVE_Walking)
	{
		float Speed = GetCharacterMovement()->Velocity.Size();
		if (Speed > 0.0f && GetWorld()->TimeSeconds - LastFootStepTime > 0.35f * GetCharacterMovement()->MaxWalkSpeed / Speed)
		{
			PlayFootstep();
		}
	}
}

void ABCharacter::Destroyed()
{
	Super::Destroyed();
}

void ABCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	UpdateTeamColors();
}

void ABCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	UpdateTeamColors();
}

void ABCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (GetPlayerState() != nullptr)
	{
		UpdateTeamColors();
	}
}

void ABCharacter::MoveForward(float Value)
{
	if (Value != 0.0f && !bIsPlayingEmote)
	{
		// Find out which way is forward
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

		// Add movement in forward direction
		AddMovementInput(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X), Value);
	}
}

void ABCharacter::MoveRight(float Value)
{
	if (Value != 0.0f && !bIsPlayingEmote)
	{
		// Find out which way is right
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

		// Add movement in right direction
		AddMovementInput(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y), Value);
	}
}

void ABCharacter::StartSprinting()
{
	if (BCharacterMovement)
	{
		BCharacterMovement->bIsSprinting = true;
	}
}

void ABCharacter::StopSprinting()
{
	if (BCharacterMovement)
	{
		BCharacterMovement->bIsSprinting = false;
	}
}

bool ABCharacter::CanSprint()
{
	return BCharacterMovement ? BCharacterMovement->SprintDuration <= 0.0f : false;
}

bool ABCharacter::IsSprinting() const
{
	return BCharacterMovement ? BCharacterMovement->bIsSprinting : false;
}

bool ABCharacter::IsJumping() const
{
	return bPressedJump;
}

void ABCharacter::UpdateTeamColors()
{
	ABPlayerState* Player = Cast<ABPlayerState>(GetPlayerState());
	if (Player)
	{
		if (Player->GetTeamNumber() == 0)
		{
			GetMesh()->SetRenderCustomDepth(true);
			GetMesh()->SetCustomDepthStencilValue(BLUE_TEAM);
		}
		else if (Player->GetTeamNumber() == 1)
		{
			GetMesh()->SetRenderCustomDepth(true);
			GetMesh()->SetCustomDepthStencilValue(RED_TEAM);
		}
	}
}

void ABCharacter::Kick()
{
	if (Role < ROLE_Authority)
	{
		ServerKick();
	}

	if (PossesedBall)
	{
		UPrimitiveComponent* HitComp = Cast<UPrimitiveComponent>(PossesedBall->GetCollisionComp());
		if (HitComp)
		{
			const FVector KickDirection = GetActorForwardVector();
			HitComp->AddImpulseAtLocation(KickDirection * KickImpulse, PossesedBall->GetActorLocation());
			PlayKick();
		}
	}
}

void ABCharacter::ServerKick_Implementation()
{
	Kick();
}

bool ABCharacter::ServerKick_Validate()
{
	return true;
}

ABBlitzball* ABCharacter::GetPossesedBall() const
{
	return PossesedBall;
}

void ABCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr)
	{
		ABBlitzball* Ball = Cast<ABBlitzball>(OtherActor);
		if (Ball)
		{
			PossesedBall = Ball;
			PossesedBall->SetLastPlayer(this);
		}
	}
}

void ABCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (PossesedBall != nullptr)
	{
		PossesedBall = nullptr;
	}
}

void ABCharacter::PlayEmote(UAnimMontage* EmoteToPlay)
{
	if (EmoteToPlay != nullptr && !bIsPlayingEmote)
	{
		GetMesh()->bPauseAnims = false;
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(EmoteToPlay, 1.0f);
			bUseControllerRotationYaw = false;
			bIsPlayingEmote = true;
			CurrentEmote = EmoteToPlay;

			FOnMontageEnded EndDelegate;
			EndDelegate.BindUObject(this, &ABCharacter::ResetEmote);
			AnimInstance->Montage_SetEndDelegate(EndDelegate);
		}
	}
}

void ABCharacter::ResetEmote(UAnimMontage* Montage, bool bInterrupted)
{
	bIsPlayingEmote = false;
	bUseControllerRotationYaw = true;
}

void ABCharacter::PlayFootstep()
{
	if (GetWorld()->TimeSeconds - LastFootStepTime < 0.1f)
	{
		return;
	}

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), FootstepSound, GetActorLocation());

	LastFootStepTime = GetWorld()->TimeSeconds;
}

void ABCharacter::PlayKick()
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), KickSound, GetActorLocation());
}

