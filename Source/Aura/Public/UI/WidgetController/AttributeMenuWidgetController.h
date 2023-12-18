// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

/**
* Forward declarations
*/

struct FAuraAttributeInfo;
class UAttributeInfo;

/**
* Delegates
*/

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FAuraAttributeInfo&, Info);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API UAttributeMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
	
public:

    virtual void BindCallbacksToDependencies() override;

    virtual void BroadcastInitialValues() override;

    UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
    FAttributeInfoSignature AttributeInfoDelegate;

protected:

    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<UAttributeInfo> AttributeInfo;
};
