// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AuraProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameplayEffectTypes.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Aura/Aura.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

// Sets default values
AAuraProjectile::AAuraProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    bReplicates = true;

    Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");

    SetRootComponent(Sphere);

    Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

    Sphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

    Sphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);

    Sphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);

    Sphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

    Sphere->SetCollisionObjectType(ECC_Projectile);

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");

    ProjectileMovement->InitialSpeed = 550.f;

    ProjectileMovement->MaxSpeed = 550.f;

    ProjectileMovement->ProjectileGravityScale = 0.f;
}

// Called when the game starts or when spawned
void AAuraProjectile::BeginPlay()
{
	Super::BeginPlay();

    SetLifeSpan(LifeSpan);

    Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraProjectile::OnSphereOverlap);

    LoopingSoundComponent = UGameplayStatics::SpawnSoundAttached(LoopingSound, GetRootComponent());
}

void AAuraProjectile::Destroyed()
{
    if (!bHit && !HasAuthority())
    {
        UGameplayStatics::PlaySoundAtLocation(
            this,
            ImpactSound,
            GetActorLocation(),
            FRotator::ZeroRotator
        );

        UNiagaraFunctionLibrary::SpawnSystemAtLocation(
            this,
            ImpactEffect,
            GetActorLocation()
        );

        if (LoopingSoundComponent) LoopingSoundComponent->Stop();
    }

    Super::Destroyed();
}

void AAuraProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    UGameplayStatics::PlaySoundAtLocation(
        this,
        ImpactSound,
        GetActorLocation(),
        FRotator::ZeroRotator
    );

    UNiagaraFunctionLibrary::SpawnSystemAtLocation(
        this,
        ImpactEffect,
        GetActorLocation()
    );

    LoopingSoundComponent->Stop();

    if (HasAuthority())
    {
        if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
        {
            TargetASC->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data.Get());
        }

        Destroy();
    }
    else
    {
        bHit = true;
    }
}
