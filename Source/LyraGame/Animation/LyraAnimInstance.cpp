// Copyright Epic Games, Inc. All Rights Reserved.

#include "LyraAnimInstance.h"
#include "AbilitySystemGlobals.h"
#include "Character/LyraCharacter.h"
#include "Camera/LyraCameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Weapons/WeaponBase.h"
#include "Character/LyraCharacterMovementComponent.h"

#if WITH_EDITOR
#include "Misc/DataValidation.h"
#endif

#include UE_INLINE_GENERATED_CPP_BY_NAME(LyraAnimInstance)


ULyraAnimInstance::ULyraAnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void ULyraAnimInstance::InitializeWithAbilitySystem(UAbilitySystemComponent* ASC)
{
	check(ASC);

	GameplayTagPropertyMap.Initialize(this, ASC);
}

#if WITH_EDITOR
EDataValidationResult ULyraAnimInstance::IsDataValid(FDataValidationContext& Context) const
{
	Super::IsDataValid(Context);

	GameplayTagPropertyMap.IsDataValid(this, Context);

	return ((Context.GetNumErrors() > 0) ? EDataValidationResult::Invalid : EDataValidationResult::Valid);
}
#endif // WITH_EDITOR

void ULyraAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (AActor* OwningActor = GetOwningActor())
	{
		if (UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OwningActor))
		{
			InitializeWithAbilitySystem(ASC);
		}
	}
}

void ULyraAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (LyraCharacter == nullptr)
	{
		LyraCharacter = Cast<ALyraCharacter>(GetOwningActor());
	}
	if (LyraCharacter == nullptr)
	{
		return;
	}

	ULyraCharacterMovementComponent* CharMoveComp = CastChecked<ULyraCharacterMovementComponent>(LyraCharacter->GetCharacterMovement());
	const FLyraCharacterGroundInfo& GroundInfo = CharMoveComp->GetGroundInfo();
	GroundDistance = GroundInfo.GroundDistance;
}


#pragma region PROCEFURAL_IK

void ULyraAnimInstance::OnNewWeaponEquipped(float InWeaponOffset)
{
	SightOffset = InWeaponOffset;

	FTimerHandle SyncWeapon_TimerHandle;

	GetWorld()->GetTimerManager().SetTimer(SyncWeapon_TimerHandle, this, &ThisClass::FinalizeWeaponSync, 0.5f, false);
}

void ULyraAnimInstance::SetSightTransform()
{
	if (IsValid(LyraCharacter) &&
		LyraCharacter->IsLocallyControlled() &&
		LyraCharacter->GetNetMode() != NM_DedicatedServer)
	{
		const FTransform CameraTransform = LyraCharacter->GetCameraComponent()->GetComponentTransform();
		const FTransform MeshTransform = LyraCharacter->GetSkeletalMeshComponentFPS()->GetComponentTransform();

		SightTransform = UKismetMathLibrary::MakeRelativeTransform(CameraTransform, MeshTransform);

		SightTransform.SetLocation(SightTransform.GetLocation() + SightTransform.GetRotation().Vector() * SightOffset);
	}
}

void ULyraAnimInstance::SetRelativeHandTransform()
{
	if (IsValid(LyraCharacter) &&
		LyraCharacter->IsLocallyControlled() &&
		LyraCharacter->GetNetMode() != NM_DedicatedServer)
	{
		if (LyraCharacter->GetCurrentWeapon() != nullptr ||
			IsValid(LyraCharacter->GetCurrentWeapon()->GetWeaponSkeletalMeshFP()))
		{
			const FTransform OpticTransfrom = 
				LyraCharacter->GetCurrentWeapon()->GetWeaponSkeletalMeshFP()->GetSocketTransform(FName("S_IronSight"));
			const FTransform MeshTransform = 
				LyraCharacter->GetSkeletalMeshComponentFPS()->GetSocketTransform(FName("hand_r"));

			RelativeHandTransform = UKismetMathLibrary::MakeRelativeTransform(OpticTransfrom, MeshTransform);
		}
	}
}

void ULyraAnimInstance::FinalizeWeaponSync()
{
	SetSightTransform();
	SetRelativeHandTransform();
}

#pragma endregion
