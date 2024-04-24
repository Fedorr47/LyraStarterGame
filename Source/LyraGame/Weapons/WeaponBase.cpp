// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapons/WeaponBase.h"
#include "Character/LyraCharacter.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	WeaponSkeletalMesh_TP = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponSkeletalMesh_TP"));
	RootComponent = WeaponSkeletalMesh_TP;
	
	WeaponSkeletalMesh_TP->SetOwnerNoSee(true);
	WeaponSkeletalMesh_TP->CastShadow = true;
	WeaponSkeletalMesh_TP->bCastHiddenShadow = true;

	WeaponSkeletalMesh_FP = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponSkeletalMesh_FP"));
	WeaponSkeletalMesh_FP->SetupAttachment(RootComponent);
	WeaponSkeletalMesh_TP->CastShadow = false;
	WeaponSkeletalMesh_TP->bCastHiddenShadow = false;
	WeaponSkeletalMesh_TP->SetOnlyOwnerSee(true);
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	if (GetNetMode() != NM_DedicatedServer)
	{
		if (auto Character = Cast<ALyraCharacter>(GetOwner()))
		{
			WeaponSkeletalMesh_FP->AttachToComponent(Character->GetSkeletalMeshComponentFPS(), FAttachmentTransformRules::SnapToTargetIncludingScale, AttachSocket);
		}
	}
	
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

