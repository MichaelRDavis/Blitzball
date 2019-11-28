// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BGoal.generated.h"

class UBoxComponent;

UCLASS()
class BLITZBALL_API ABGoal : public AActor
{
	GENERATED_BODY()
	
public:	
	ABGoal();

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = GameObject)
	int32 GetTeamNumber() const;

private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* GoalMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* GoalBox;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* SaveBox;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameObject)
	int32 TeamNumber;
};
