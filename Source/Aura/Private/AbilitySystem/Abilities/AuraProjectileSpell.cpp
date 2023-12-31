// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"
#include "Interaction/CombatInterface.h"
#include "Actor/AuraProjectile.h"
#include "Engine/World.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UAuraProjectileSpell::SpawnProjectile()
{
    const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();

    if (!bIsServer) return;

    ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());

    if (CombatInterface)
    {

        const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();

        FTransform SpawnTransform;

        SpawnTransform.SetLocation(SocketLocation);
        AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass, SpawnTransform, GetOwningActorFromActorInfo(), Cast<APawn>(GetOwningActorFromActorInfo()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

        Projectile->FinishSpawning(SpawnTransform);
    }
}
