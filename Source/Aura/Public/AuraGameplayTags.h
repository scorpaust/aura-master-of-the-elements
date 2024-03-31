// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Aura/Public/AuraGameplayTags.h"

/**
 * Aura Gameplay Tags
 * Singleton containing native Gameplay Tags
 */
struct FAuraGameplayTags
{
public:

    static const FAuraGameplayTags Get() { return GameplayTags; }

    static void InitializeNativeGameplayTags();


    FGameplayTag Attributes_Primary_Strength;

    FGameplayTag Attributes_Primary_Intelligence;

    FGameplayTag Attributes_Primary_Resilience;

    FGameplayTag Attributes_Primary_Vigor;


    FGameplayTag Attributes_Secondary_Armor;

    FGameplayTag Attributes_Secondary_ArmorPenetration;

    FGameplayTag Attributes_Secondary_BlockChance;

    FGameplayTag Attributes_Secondary_CriticalHitChance;

    FGameplayTag Attributes_Secondary_CriticalHitDamage;

    FGameplayTag Attributes_Secondary_CriticalHitResistance;

    FGameplayTag Attributes_Secondary_HealthRegeneration;

    FGameplayTag Attributes_Secondary_ManaRegeneration;

    FGameplayTag Attributes_Secondary_MaxHealth;

    FGameplayTag Attributes_Secondary_MaxMana;


    FGameplayTag Attributes_Resistance_Fire;

    FGameplayTag Attributes_Resistance_Lightning;

    FGameplayTag Attributes_Resistance_Arcane;

    FGameplayTag Attributes_Resistance_Physical;

    
    FGameplayTag Abilities_Attack;


    FGameplayTag Montage_Attack_Weapon;

    FGameplayTag Montage_Attack_RightHand;

    FGameplayTag Montage_Attack_LeftHand;


    FGameplayTag InputTag_LMB;

    FGameplayTag InputTag_RMB;

    FGameplayTag InputTag_01;

    FGameplayTag InputTag_02;

    FGameplayTag InputTag_03;

    FGameplayTag InputTag_04;

    FGameplayTag Damage;

    FGameplayTag Damage_Fire;

    FGameplayTag Damage_Lightning;

    FGameplayTag Damage_Arcane;

    FGameplayTag Damage_Physical;


    TMap<FGameplayTag, FGameplayTag> DamageTypesToResistances;

    FGameplayTag Effects_HitReact;


private:

    static FAuraGameplayTags GameplayTags;
};
