// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitializeNativeGameplayTags()
{
    /*
    * Primary Attributes
    */

    GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attributes.Primary.Strength"),
        FString("Increases physical damage."));

    GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attributes.Primary.Intelligence"),
        FString("Increases magical damage."));

    GameplayTags.Attributes_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attributes.Primary.Resilience"),
        FString("Increases armor and armor penetration."));

    GameplayTags.Attributes_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attributes.Primary.Vigor"),
        FString("Increases health."));

    /*
    * Secondary Attributes
    */

    GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attributes.Secondary.Armor"), 
        FString("Reduces damage taken. Improves block chance."));

    GameplayTags.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attributes.Secondary.ArmorPenetration"),
        FString("Ignored percentage of enemy armor. Increases critical hit chance."));

    GameplayTags.Attributes_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attributes.Secondary.BlockChance"),
        FString("Chance to cut incoming damage in half."));

    GameplayTags.Attributes_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attributes.Secondary.CriticalHitChance"),
        FString("Chance to double damage plus critical hit bonus."));

    GameplayTags.Attributes_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attributes.Secondary.CriticalHitDamage"),
        FString("Bonus damage added when a critical hit is scored."));

    GameplayTags.Attributes_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attributes.Secondary.CriticalHitResistance"),
        FString("Reduces critical hit chance of attacking enemies."));

    GameplayTags.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attributes.Secondary.HealthRegeneration"),
        FString("Amount of health regenerated every 1 second."));

    GameplayTags.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attributes.Secondary.ManaRegeneration"),
        FString("Amount of mana regenerated every 1 second."));

    GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attributes.Secondary.MaxHealth"),
        FString("Maximum amount of health obtainable."));

    GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attributes.Secondary.MaxMana"),
        FString("Maximum amount of mana obtainable."));

    /*
    * Input Tags
    */

    GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("InputTag.LMB"),
        FString("Input tag for left mouse button."));

    GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("InputTag.RMB"),
        FString("Input tag for right mouse button."));

    GameplayTags.InputTag_01 = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("InputTag.01"),
        FString("Input tag for key 1."));

    GameplayTags.InputTag_02 = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("InputTag.02"),
        FString("Input tag for key 2."));

    GameplayTags.InputTag_03 = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("InputTag.03"),
        FString("Input tag for key 3."));

    GameplayTags.InputTag_04 = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("InputTag.04"),
        FString("Input tag for key 4."));

    GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Damage"),
        FString("Damage."));
}
