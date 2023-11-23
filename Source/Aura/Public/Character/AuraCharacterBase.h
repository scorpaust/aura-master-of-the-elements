// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AuraCharacterBase.generated.h"

/*
* Forward declarations
*/

class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;


UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:

	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo();

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
    TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
    TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

    void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;

    void InitializeDefaultAttributes() const;
};
