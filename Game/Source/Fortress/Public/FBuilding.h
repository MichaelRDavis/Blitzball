// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FBuilding.generated.h"

UCLASS()
class FORTRESS_API AFBuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	AFBuilding();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Mesh)
	UStaticMeshComponent* BuildingMesh;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Actor)
	int32 Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Actor)
	int32 MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Actor)
	float GridSize;
};
