// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/LyraMovementComponent.h"

#include "AbilitySystem/Attributes/LyraAttributeSet.h"
#include "LyraLogChannels.h"
#include "System/LyraAssetManager.h"
#include "System/LyraGameData.h"
#include "LyraGameplayTags.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystem/LyraAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/LyraMovementSet.h"
#include "Messages/LyraVerbMessage.h"
#include "Messages/LyraVerbMessageHelpers.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "GameFramework/PlayerState.h"
#include "Engine/World.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(LyraMovementComponent)


ULyraMovementComponent::ULyraMovementComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicatedByDefault(true);

	AbilitySystemComponent = nullptr;
	MovementSet = nullptr;
}

void ULyraMovementComponent::InitializeWithAbilitySystem(ULyraAbilitySystemComponent* InASC)
{
	AActor* Owner = GetOwner();
	check(Owner);

	if (AbilitySystemComponent)
	{
		UE_LOG(LogLyra, Error, TEXT("LyraHealthComponent: Health component for owner [%s] has already been initialized with an ability system."), *GetNameSafe(Owner));
		return;
	}

	AbilitySystemComponent = InASC;
	if (!AbilitySystemComponent)
	{
		UE_LOG(LogLyra, Error, TEXT("LyraHealthComponent: Cannot initialize health component for owner [%s] with NULL ability system."), *GetNameSafe(Owner));
		return;
	}

	MovementSet = AbilitySystemComponent->GetSet<ULyraMovementSet>();
	if (!MovementSet)
	{
		UE_LOG(LogLyra, Error, TEXT("LyraHealthComponent: Cannot initialize health component for owner [%s] with NULL health set on the ability system."), *GetNameSafe(Owner));
		return;
	}

	ClearGameplayTags();
}

void ULyraMovementComponent::UninitializeFromAbilitySystem()
{
	ClearGameplayTags();

	if (MovementSet)
	{
	}

	MovementSet = nullptr;
	AbilitySystemComponent = nullptr;
}

float ULyraMovementComponent::GetMoveSpeed() const
{
	return (MovementSet ? MovementSet->GetMoveSpeed() : 0.0f);
}

void ULyraMovementComponent::OnUnregister()
{
	UninitializeFromAbilitySystem();

	Super::OnUnregister();
}

void ULyraMovementComponent::ClearGameplayTags()
{
	if (AbilitySystemComponent)
	{
		//AbilitySystemComponent->SetLooseGameplayTagCount(LyraGameplayTags::Status_Death_Dying, 0);
	}
}
