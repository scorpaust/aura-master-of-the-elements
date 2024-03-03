// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_FindNearestPlayer.h"
#include "AIController.h"
#include "AI/AuraAIController.h"
#include "Character/AuraEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_FindNearestPlayer::UBTService_FindNearestPlayer()
{
    bTickIntervals = true;
}

void UBTService_FindNearestPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    AAuraAIController* AIController = Cast<AAuraAIController>(OwnerComp.GetAIOwner());

    APawn* OwningPawn = AIController->GetPawn();

    if (!OwningPawn || !AIController) {
        return; // Ensure pawn is valid
    }

    const FName TargetTag = OwningPawn->ActorHasTag(FName("Player")) ? FName("Enemy") : FName("Player");
    
    TArray<AActor*> ActorsWithTag;
    
    UGameplayStatics::GetAllActorsWithTag(OwningPawn, TargetTag, ActorsWithTag);

    float ClosestDistance = TNumericLimits<float>::Max();
    
    AActor* ClosestActor = nullptr;
    
    for (AActor* Actor : ActorsWithTag)
    {
        if (IsValid(Actor) && IsValid(OwningPawn))
        {
            const float Distance = OwningPawn->GetDistanceTo(Actor);
            
            if (Distance < ClosestDistance)
            {
                ClosestDistance = Distance;
                ClosestActor = Actor;
            }
        }
    }

    if (ClosestActor && IsValid(&OwnerComp)) {
        // It's crucial to ensure that the OwnerComp is valid and correctly referenced
        UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
        
        if (BlackboardComp) {
            
            BlackboardComp->SetValueAsObject(TargetToFollowSelector.SelectedKeyName, ClosestActor);
            
            BlackboardComp->SetValueAsFloat(DistanceToTargetSelector.SelectedKeyName, ClosestDistance);
        }
    }
}
