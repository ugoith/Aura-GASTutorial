// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraGameplayTags.h"

#include "GameplayTagsManager.h"

//静态成员变量的定义,用于在内存中为 FAuraGameplayTags 结构体的静态实例分配空间,是单例模式能够生效的关键.
FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"),FString("Reduce Damage Taken , improves Block  Chance"));
	
}
