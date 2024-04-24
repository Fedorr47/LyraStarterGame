// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Attributes/LyraAttributeSet.h"
#include "LyraMovementSet.generated.h"

/**
 * 
 */
UCLASS()
class LYRAGAME_API ULyraMovementSet : public ULyraAttributeSet
{
	GENERATED_BODY()
public:
	ULyraMovementSet();

	ATTRIBUTE_ACCESSORS(ULyraMovementSet, MoveSpeed);

	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_MoveSpeed, Category = "Lyra|Movement")
	FGameplayAttributeData MoveSpeed;

protected:
	UFUNCTION()
	void OnRep_MoveSpeed(const FGameplayAttributeData& OldValue);

	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
};
