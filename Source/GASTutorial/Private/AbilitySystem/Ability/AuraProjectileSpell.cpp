// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/AuraProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

}

void UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	
	//确定自己是否在服务器
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;
	
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface)
	{
		//生成对应飞行物并给予命中后的效果
		const FVector SpawnSocketLocation = CombatInterface->GetCombatSocketLocation();
		
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SpawnSocketLocation);
		//设置生成的发射物旋转
		FRotator Rotation = (ProjectileTargetLocation - SpawnSocketLocation).Rotation();
		Rotation.Pitch = 0.f;
		SpawnTransform.SetRotation(Rotation.Quaternion());
		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetAvatarActorFromActorInfo()),ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		// 命中敌人后造成伤害
		const UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
		FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get(); 
		Projectile->DamageEffectSpecHandle = ASC->MakeOutgoingSpec(AuraDamageEffect,GetAbilityLevel(),ASC->MakeEffectContext());
		const float ScaledDamage = Damage.GetValueAtLevel(GetAbilityLevel());//ScaledDamage
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(Projectile->DamageEffectSpecHandle,GameplayTags.Damage,ScaledDamage);
		Projectile->FinishSpawning(SpawnTransform);
	}
}
