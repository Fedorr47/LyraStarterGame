// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Animation/AnimInstance.h"
#include "GameplayEffectTypes.h"
#include "LyraAnimInstance.generated.h"

class UAbilitySystemComponent;
class ALyraCharacter;

/**
 * ULyraAnimInstance
 *
 *	The base game animation instance class used by this project.
 */
UCLASS(Config = Game)
class ULyraAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	ULyraAnimInstance(const FObjectInitializer& ObjectInitializer);

	virtual void InitializeWithAbilitySystem(UAbilitySystemComponent* ASC);

protected:

#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;
#endif // WITH_EDITOR

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:

	// Gameplay tags that can be mapped to blueprint variables. The variables will automatically update as the tags are added or removed.
	// These should be used instead of manually querying for the gameplay tags.
	UPROPERTY(EditDefaultsOnly, Category = "GameplayTags")
	FGameplayTagBlueprintPropertyMap GameplayTagPropertyMap;

	UPROPERTY(BlueprintReadOnly, Category = "Character State Data")
	float GroundDistance = -1.0f;

#pragma region PROCEFURAL_IK

public:
	UPROPERTY(BlueprintReadOnly, Category = "Precedural IK")
	ALyraCharacter* LyraCharacter = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Precedural IK")
	FTransform RelativeHandTransform;

	UPROPERTY(BlueprintReadOnly, Category = "Precedural IK")
	FTransform SightTransform;

	UFUNCTION(BlueprintCallable, Category = "Lyra|Character")
	void OnNewWeaponEquipped(float InWeaponOffset);

protected:
	void SetSightTransform();
	void SetRelativeHandTransform();

private:

	float SightOffset = 30.0f;

	void FinalizeWeaponSync();

#pragma endregion
};
