// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/GameFrameworkComponent.h"
#include "LyraMovementComponent.generated.h"


class ULyraMovementComponent;

class ULyraAbilitySystemComponent;
class ULyraMovementSet;
class UObject;
struct FFrame;
struct FGameplayEffectSpec;

UCLASS(Blueprintable, Meta = (BlueprintSpawnableComponent))
class LYRAGAME_API ULyraMovementComponent : public UGameFrameworkComponent
{
	GENERATED_BODY()

public:

	ULyraMovementComponent(const FObjectInitializer& ObjectInitializer);

	// Initialize the component using an ability system component.
	UFUNCTION(BlueprintCallable, Category = "Lyra|Movement")
	void InitializeWithAbilitySystem(ULyraAbilitySystemComponent* InASC);

	// Uninitialize the component, clearing any references to the ability system.
	UFUNCTION(BlueprintCallable, Category = "Lyra|Movement")
	void UninitializeFromAbilitySystem();

	UFUNCTION(BlueprintCallable, Category = "Lyra|Movement")
	float GetMoveSpeed() const;

protected:

	virtual void OnUnregister() override;
	void ClearGameplayTags();

protected:

	// Ability system used by this component.
	UPROPERTY()
	TObjectPtr<ULyraAbilitySystemComponent> AbilitySystemComponent;

	// Health set used by this component.
	UPROPERTY()
	TObjectPtr<const ULyraMovementSet> MovementSet;
};
