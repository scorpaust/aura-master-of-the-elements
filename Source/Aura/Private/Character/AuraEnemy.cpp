// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraEnemy.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "UI/Widget/AuraUserWidget.h"
#include "AuraGameplayTags.h"
#include "AI/AuraAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/CharacterMovementComponent.h"

AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");

	AbilitySystemComponent->SetIsReplicated(true);

	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");

    HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");

    HealthBar->SetupAttachment(GetRootComponent());

    bUseControllerRotationPitch = false;

    bUseControllerRotationRoll = false;

    bUseControllerRotationYaw = false;

    GetCharacterMovement()->bUseControllerDesiredRotation = true;
}

void AAuraEnemy::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    if (!HasAuthority()) return;

    AuraAIController = Cast<AAuraAIController>(NewController);

    if (AuraAIController)
    {
        AuraAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);

        AuraAIController->RunBehaviorTree(BehaviorTree);

        AuraAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), false);

        AuraAIController->GetBlackboardComponent()->SetValueAsBool(FName("RangedAttacker"), CharacterClass != ECharacterClass::Warrior);
    }
}

void AAuraEnemy::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);

	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);

	Weapon->SetRenderCustomDepth(true);

	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AAuraEnemy::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);

	Weapon->SetRenderCustomDepth(false);
}

int32 AAuraEnemy::GetPlayerLevel() 
{
    return Level;
}

void AAuraEnemy::Die()
{
    SetLifeSpan(LifeSpan);

    Super::Die();
}

void AAuraEnemy::SetCombatTarget_Implementation(AActor* InCombatTarget)
{
    CombatTarget = InCombatTarget;
}

AActor* AAuraEnemy::GetCombatTarget_Implementation() const
{
    return CombatTarget;
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();

	InitAbilityActorInfo();

    if (HasAuthority())
    {
        UAuraAbilitySystemLibrary::GiveStartupAbilities(this, AbilitySystemComponent, CharacterClass);
    }

    GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;

    if (UAuraUserWidget* AuraUserWidget = Cast<UAuraUserWidget>(HealthBar->GetUserWidgetObject()))
    {
        AuraUserWidget->SetWidgetController(this);
    }

    if (const UAuraAttributeSet* AuraAS = CastChecked<UAuraAttributeSet>(AttributeSet))
    {
        AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetHealthAttribute()).AddLambda(
            [this](const FOnAttributeChangeData& Data)
            {
                OnHealthChanged.Broadcast(Data.NewValue);
            }
        );

        AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetMaxHealthAttribute()).AddLambda(
            [this](const FOnAttributeChangeData& Data)
            {
                OnMaxHealthChanged.Broadcast(Data.NewValue);
            }
        );

        AbilitySystemComponent->RegisterGameplayTagEvent(FAuraGameplayTags().Get().Effects_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(
            this,
            &AAuraEnemy::HitReactTagChanged
        );

        OnHealthChanged.Broadcast(AuraAS->GetHealth());

        OnMaxHealthChanged.Broadcast(AuraAS->GetMaxHealth());
    }    
}

void AAuraEnemy::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
    bHitReacting = NewCount > 0;

    GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;

    if (AuraAIController && AuraAIController->GetBlackboardComponent())
    {
        AuraAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), bHitReacting);
    }
}


void AAuraEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

    if (HasAuthority())
    {
        InitializeDefaultAttributes();
    }
}

void AAuraEnemy::InitializeDefaultAttributes() const
{
    UAuraAbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
}
