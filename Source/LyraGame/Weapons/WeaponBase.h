// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

class USkeletalMeshComponent;

UCLASS()
class LYRAGAME_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

	UFUNCTION(BlueprintPure, Category = Weapon)
	FORCEINLINE USkeletalMeshComponent* GetWeaponSkeletalMeshFP() { return WeaponSkeletalMesh_FP; }

	UFUNCTION(BlueprintPure, Category = Weapon)
	FORCEINLINE USkeletalMeshComponent* GetWeaponSkeletalMeshTP() { return WeaponSkeletalMesh_TP; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = Weapon)
	USkeletalMeshComponent* WeaponSkeletalMesh_FP;

	UPROPERTY(EditDefaultsOnly, Category = Weapon)
	USkeletalMeshComponent* WeaponSkeletalMesh_TP;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Weapon)
	FName AttachSocket = "None";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponRotation)
	FRotator WeaponRotation{};

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
