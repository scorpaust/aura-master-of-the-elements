// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Aura/Aura.h"


AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

    GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECollisionResponse::ECR_Ignore);

    GetCapsuleComponent()->SetGenerateOverlapEvents(false);

    GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECollisionResponse::ECR_Ignore);

    GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECollisionResponse::ECR_Overlap);

    GetMesh()->SetGenerateOverlapEvents(true);

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");

	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));

	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAnimMontage* AAuraCharacterBase::GetHitReactMontage_Implementation()
{
    return HitReactMontage;
}

void AAuraCharacterBase::Die()
{
    Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));

    MulticastHandleDeath();
}

void AAuraCharacterBase::MulticastHandleDeath_Implementation()
{
    Weapon->SetSimulatePhysics(true);

    Weapon->SetEnableGravity(true);

    Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

    GetMesh()->SetEnableGravity(true);

    GetMesh()->SetSimulatePhysics(true);

    GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

    GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECollisionResponse::ECR_Block);

    GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    Dissolve();

    bDead = true;
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraCharacterBase::InitAbilityActorInfo()
{
}

int32 AAuraCharacterBase::GetPlayerLevel()
{
    return int32();
}

FVector AAuraCharacterBase::GetCombatSocketLocation_Implementation()
{
    check(Weapon);

    return Weapon->GetSocketLocation(WeaponTipSocketName);
}

bool AAuraCharacterBase::IsDead_Implementation() const
{
    return bDead;
}

AActor* AAuraCharacterBase::GetAvatar_Implementation() 
{
    return this;
}

void AAuraCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
    check(IsValid(GetAbilitySystemComponent()));

    check(GameplayEffectClass);

    FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();

    ContextHandle.AddSourceObject(this);

    const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);

    GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void AAuraCharacterBase::InitializeDefaultAttributes() const
{
    ApplyEffectToSelf(DefaultPrimaryAttributes, 1.0f);

    ApplyEffectToSelf(DefaultSecondaryAttributes, 1.0f);

    ApplyEffectToSelf(DefaultVitalAttributes, 1.0f);
}

void AAuraCharacterBase::AddCharacterAbilities()
{
    if (HasAuthority())
    {
        UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent);

        AuraASC->AddCharacterAbilities(StartupAbilities);
    }
}

void AAuraCharacterBase::Dissolve()
{
    if (IsValid(DissolveMaterialInstance))
    {
        UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(DissolveMaterialInstance, this);

        GetMesh()->SetMaterial(0, DynamicMatInst);

        StartDissolveTimeline(DynamicMatInst);
    }

    if (IsValid(WeaponDissolveMaterialInstance))
    {
        UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(WeaponDissolveMaterialInstance, this);

        Weapon->SetMaterial(0, DynamicMatInst);

        StartWeaponDissolveTimeline(DynamicMatInst);
    }
}
