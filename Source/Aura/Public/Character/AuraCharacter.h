// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/CombatInterface.h"
#include "AuraCharacter.generated.h"


/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase, public ICombatInterface
{
	GENERATED_BODY()
	
public:

	AAuraCharacter();

	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;

    /** Combat Interface */

    virtual int32 GetPlayerLevel() override;

    /** End Combat Interface */

private: 

	virtual void InitAbilityActorInfo() override;
};
