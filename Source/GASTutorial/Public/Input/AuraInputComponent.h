// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraInputConfig.h"
#include "EnhancedInputComponent.h"
#include "AuraInputComponent.generated.h"

struct FAuraInputAction;
class UAuraInputConfig;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GASTUTORIAL_API UAuraInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAuraInputComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	//Pressed,Release,Held为函数指针
	template<class UserClass,typename PressedFuncType,typename ReleaseFuncType,typename HeldFuncType>
	void BindAbilityActions(const UAuraInputConfig* InputConfg,UserClass* Object,PressedFuncType PressedFunc,ReleaseFuncType ReleaseFunc,HeldFuncType HeldFunc);
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};

template <class UserClass, typename PressedFuncType, typename ReleaseFuncType, typename HeldFuncType>
void UAuraInputComponent::BindAbilityActions(const UAuraInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc,
	ReleaseFuncType ReleaseFunc, HeldFuncType HeldFunc)
{
	check(InputConfig);
	for (const FAuraInputAction& Action : InputConfig->AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (HeldFunc)
			BindAction(Action.InputAction,ETriggerEvent::Triggered,Object,HeldFunc,Action.InputTag);
			if (ReleaseFunc)
			BindAction(Action.InputAction,ETriggerEvent::Completed,Object,ReleaseFunc,Action.InputTag);
			if (PressedFunc)
			BindAction(Action.InputAction,ETriggerEvent::Started,Object,PressedFunc,Action.InputTag);
		}
	}
}
