// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GASTUTORIAL_API IEnemyInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//在控制器中使用GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);
	//每帧检测光标下是否有相对应的Actor来决定是否高光显示（别忘了在控制器中加入对此类的指针，需要将碰撞的结果Actor Cast至此类）
	
	virtual void HighLightActor()=0;//纯虚函数
	virtual void UnHighLightActor()=0;

	
};
