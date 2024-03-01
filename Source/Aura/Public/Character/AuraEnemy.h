// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "AuraEnemy.generated.h"

#define CUSTOM_DEPTH_RED 250

/**
 * Forward declarations
 */

class UWidgetComponent;
class UBehaviorTree;
class AAuraAIController;

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:

	AAuraEnemy();

    virtual void PossessedBy(AController* NewController) override;

	/** Enemy Interface */
	virtual void HighlightActor() override;

	virtual void UnHighlightActor() override;
	/** End Enemy Interface */

    /** Combat Interface */

    virtual int32 GetPlayerLevel() override;

    virtual void Die() override;

    /** End Combat Interface */

    UPROPERTY(BlueprintAssignable)
    FOnAttributeChangedSignature OnHealthChanged;

    UPROPERTY(BlueprintAssignable)
    FOnAttributeChangedSignature OnMaxHealthChanged;

    void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

    UPROPERTY(BlueprintReadOnly, Category = "Combat")
    bool bHitReacting = false;

    UPROPERTY(BlueprintReadOnly, Category = "Combat")
    float BaseWalkSpeed = 250.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
    float LifeSpan = 5.f;

protected:

	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;

    virtual void InitializeDefaultAttributes() const override;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Class Defaults")
    int32 Level = 1;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
    ECharacterClass CharacterClass = ECharacterClass::Warrior;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<UWidgetComponent> HealthBar;

    UPROPERTY(EditAnywhere, Category = "AI")
    TObjectPtr<UBehaviorTree> BehaviorTree;

    UPROPERTY()
    TObjectPtr<AAuraAIController> AuraAIController;
};
