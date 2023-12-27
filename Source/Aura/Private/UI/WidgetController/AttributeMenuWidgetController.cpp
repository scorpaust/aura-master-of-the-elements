// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "AuraGameplayTags.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
    UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);

    check(AttributeInfo);

    for (auto& Pair : AS->TagsToAttributes)
    {
        AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
            [this, Pair](const FOnAttributeChangeData& Data)
            {
                BroadcastAtributeInfo(Pair.Key, Pair.Value());
            }
        );
    }
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
    UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);

    check(AttributeInfo);

    for (auto& Pair : AS->TagsToAttributes)
    {
        BroadcastAtributeInfo(Pair.Key, Pair.Value());
    }
}

void UAttributeMenuWidgetController::BroadcastAtributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const 
{
    FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);

    Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);

    AttributeInfoDelegate.Broadcast(Info);
}
