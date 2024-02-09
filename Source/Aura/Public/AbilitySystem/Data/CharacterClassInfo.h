// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterClassInfo.generated.h"

/**
 * Forward declarations
 */

class UGameplayEffect;
class UGameplayAbility;

/**
 * Enums
 */

UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
    Elementalist,
    Warrior,
    Ranger
};

/**
 * Structs
 */

USTRUCT(BlueprintType)
struct FCharacterClassDefaultInfo
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, Category = "Class Defaults")
    TSubclassOf<UGameplayEffect> PrimaryAttributes;
};

/**
 * 
 */
UCLASS()
class AURA_API UCharacterClassInfo : public UDataAsset
{
	GENERATED_BODY()

public: 

    UPROPERTY(EditDefaultsOnly, Category="Class Defaults")
    TMap<ECharacterClass, FCharacterClassDefaultInfo> CharacterClassInformation;

    UPROPERTY(EditDefaultsOnly, Category = "Common Class Defaults")
    TSubclassOf<UGameplayEffect> SecondaryAttributes;

    UPROPERTY(EditDefaultsOnly, Category = "Common Class Defaults")
    TSubclassOf<UGameplayEffect> VitalAttributes;

    UPROPERTY(EditDefaultsOnly, Category = "Common Class Defaults")
    TArray<TSubclassOf<UGameplayAbility>> CommonAbilities;
	
    FCharacterClassDefaultInfo GetClassDefaultInfo(ECharacterClass CharacterClass);
};
