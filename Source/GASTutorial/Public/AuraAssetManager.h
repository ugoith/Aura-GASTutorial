// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "AuraAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class GASTUTORIAL_API UAuraAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	//传回自身
	static UAuraAssetManager& Get();

protected:
	//引擎初始化加载时调用,完成游戏标签的添加
	virtual void StartInitialLoading() override;
};
