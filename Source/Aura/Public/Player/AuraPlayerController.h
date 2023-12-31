// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "AuraPlayerController.generated.h"

/**
 * 
 */

/* Forward declarations */
class UInputMappingContext;
class UInputAction;
class UAuraInputConfig;
struct FInputActionValue;
class IEnemyInterface;
class UAuraAbilitySystemComponent;
class USplineComponent;

UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AAuraPlayerController();

	virtual void PlayerTick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

private:

	IEnemyInterface* LastActor;

	IEnemyInterface* ThisActor;

    FHitResult CursorHit;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> AuraContext;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	void CursorTrace();

	void Move(const FInputActionValue& InputActionValue);

    void AbilityInputTagPressed(FGameplayTag InputTag);

    void AbilityInputTagReleased(FGameplayTag InputTag);

    void AbilityInputTagHeld(FGameplayTag InputTag);

    void AutoRun();

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    TObjectPtr<UAuraInputConfig> InputConfig;

    UPROPERTY()
    TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;

    UAuraAbilitySystemComponent* GetASC();

    FVector CachedDestination = FVector::ZeroVector;

    float FollowTime = 0.f;

    float ShortPressThreshold = 0.5f;

    bool bAutoRunning = false;

    bool bTargeting = false;

    UPROPERTY(EditDefaultsOnly)
    float AutoRunAcceptanceRadius = 50.f;

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<USplineComponent> Spline;
};
