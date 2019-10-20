// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "FInventoryItem.h"
#include "FInvItem_WeaponAttachment.generated.h"

class AFWeapon;

UCLASS()
class FORTRESS_API AFInvItem_WeaponAttachment : public AFInventoryItem
{
	GENERATED_BODY()
	
public:
	AFInvItem_WeaponAttachment();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Mesh)
	USkeletalMeshComponent* AttachmentMesh;

	UPROPERTY()
	AFWeapon* WeaponOwner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attachment)
	FName AttachSocket;

	UFUNCTION(BlueprintCallable, Category = Attachment)
	void AttachToMesh();
	UFUNCTION(BlueprintCallable, Category = Attachment)
	void DetachFromMesh();
};
