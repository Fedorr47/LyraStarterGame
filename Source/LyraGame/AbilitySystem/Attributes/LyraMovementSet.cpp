// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attributes/LyraMovementSet.h"
#include "AbilitySystem/Attributes/LyraAttributeSet.h"
#include "LyraGameplayTags.h"
#include "Net/UnrealNetwork.h"
#include "AbilitySystem/LyraAbilitySystemComponent.h"
#include "Engine/World.h"
#include "GameplayEffectExtension.h"
#include "Messages/LyraVerbMessage.h"
#include "GameFramework/GameplayMessageSubsystem.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(LyraMovementSet)

ULyraMovementSet::ULyraMovementSet()
	: MoveSpeed(600.0f)
{
}

void ULyraMovementSet::OnRep_MoveSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULyraMovementSet, MoveSpeed, OldValue);
}

bool ULyraMovementSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	return true;
}

void ULyraMovementSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute == GetMoveSpeedAttribute())
	{
		SetMoveSpeed(FMath::Clamp(GetMoveSpeed(), 0.0f, 1200.0f));
	}
}

void ULyraMovementSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
}

void ULyraMovementSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
}

void ULyraMovementSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
}

void ULyraMovementSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ULyraMovementSet, MoveSpeed, COND_None, REPNOTIFY_Always);
}