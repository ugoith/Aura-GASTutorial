// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "Engine/NetworkObjectList.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Player/PlayerControllerBase.h"


UAuraAttributeSet::UAuraAttributeSet()
{
	//UE_LOG(LogTemp,Warning,TEXT("InitProperty"));
	//InitHealth(75.0f);
	//InitMaxHealth(100.0f);
	//InitMana(75.0f);
	//InitMaxMana(100.0f);
	/*InitStrength(100.0f);
	InitIntelligence(100.0f);
	InitResilience(100.0f);*/
	//拿到所有的标签
	const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();
	
	//FAttributeSignature StrengthDelegate;
	//StrengthDelegate.BindStatic(GetStrengthAttribute);
	//TagToAttributes.Add(GameplayTags.Attribute_Primary_Intelligence, StrengthDelegate);

	//Primary Attributes
	TagToAttributes.Add(GameplayTags.Attribute_Primary_Strength, GetStrengthAttribute);
	TagToAttributes.Add(GameplayTags.Attribute_Primary_Intelligence, GetIntelligenceAttribute);
	TagToAttributes.Add(GameplayTags.Attribute_Primary_Resilience, GetResilienceAttribute);
	TagToAttributes.Add(GameplayTags.Attribute_Primary_Vigor, GetVigorAttribute);

	//Secondary Attributes
	TagToAttributes.Add(GameplayTags.Attribute_Secondary_Armor, GetArmorAttribute);
	TagToAttributes.Add(GameplayTags.Attribute_Secondary_BlockChance, GetBlockChanceAttribute);
	TagToAttributes.Add(GameplayTags.Attribute_Secondary_ArmorPenetration, GetArmorPenetrationAttribute);
	TagToAttributes.Add(GameplayTags.Attribute_Secondary_CriticalHitChance, GetCriticalHitChanceAttribute);
	TagToAttributes.Add(GameplayTags.Attribute_Secondary_CriticalHitDamage, GetCriticalHitDamageAttribute);
	TagToAttributes.Add(GameplayTags.Attribute_Secondary_HealthRegeneration, GetHealthRegenerationAttribute);
	TagToAttributes.Add(GameplayTags.Attribute_Secondary_ManaRegeneration, GetManaRegenerationAttribute);
	TagToAttributes.Add(GameplayTags.Attribute_Secondary_CriticalHitResistance, GetCriticalHitResistanceAttribute);
	TagToAttributes.Add(GameplayTags.Attribute_Secondary_MaxHealth, GetMaxHealthAttribute);
	TagToAttributes.Add(GameplayTags.Attribute_Secondary_MaxMana, GetMaxManaAttribute);
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//TODO:设置网络复制模式
	/*Vital Attributes*/
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Health,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Mana,COND_None,REPNOTIFY_Always);
	/*Primary Attributes*/
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Strength,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Intelligence,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Resilience,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Vigor,COND_None,REPNOTIFY_Always);
	/*Secondary Attributes*/
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Armor,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,ArmorPenetration,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,CriticalHitChance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,CriticalHitDamage,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,HealthRegeneration,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,ManaRegeneration,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,BlockChance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,CriticalHitResistance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,MaxHealth,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,MaxMana,COND_None,REPNOTIFY_Always);
}


void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute==GetHealthAttribute())
	NewValue=FMath::Clamp(NewValue,0,GetMaxHealth());
	if (Attribute==GetManaAttribute())
		NewValue=FMath::Clamp(NewValue,0,GetMaxMana());
}
void UAuraAttributeSet::SetFEffectProperties(const struct FGameplayEffectModCallbackData& Data,
	FEffectProperties& Props) const
{
	//Data → 当前正在执行的 属性修改回调（比如血量减少）。
	//EffectSpec → 这个修改来自哪个 GameplayEffect 规格 (Spec)。
	//GetContext() → 从 Spec 里拿到它的 上下文 (EffectContextHandle)，保存了额外信息。
	Props.EffectContextHandle=Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();
	//查看发起者有没有效果
	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && IsValid(Props.SourceASC->GetAvatarActor()) )
	{
		Props.SourceAvatarActor = Props.SourceASC->GetAvatarActor();
		Props.SourceController=Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		//若PlayerController没有获取到 且 拥有源发起者
		if (Props.SourceController==nullptr && Props.SourceAvatarActor!= nullptr)
		{
			//把SourceAvatarActor的控制器赋值给空的SourceController，作为新的控制者
			if (APawn* Pawn=Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}		
		}
		//如果是玩家控制器，则将控制器的控制的Pawn转换为Character
		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
			
		}
	}
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.GetAvatarActor())
	{
		Props.TargetAvatarActor = Data.Target.GetAvatarActor();
		Props.TargetController =	Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
	
}

void UAuraAttributeSet::ShowFloatingText(const FEffectProperties& Props, float Damage)
{
	if (Props.SourceCharacter != Props.TargetCharacter)
	{
		APlayerControllerBase* PC =	Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(Props.SourceCharacter,0));
		if (PC)
		{
			PC->ShowDamageText(Damage,Props.TargetCharacter);
		}
	}
}


/*当一个 GameplayEffect (GE) 修改了 AttributeSet 中的属性后，这个回调会被触发。
* AbilitySystemComponent 应用了某个 GameplayEffect（比如 GE_Damage，减少角色生命值）。
GameplayEffectSpec 会修改 AttributeSet 里的某个属性（比如 Health）。
修改完成后，自动调用 PostGameplayEffectExecute。
参数 Data 包含了：
修改了哪个属性
修改的数值（Magnitude）
施法者、命中点等上下文信息
 */
void UAuraAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	FEffectProperties Props;
	//存相关变化的参数和对应的拥有者、控制器、AbilitySystem等
	SetFEffectProperties(Data,Props);
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(),0,GetMaxHealth()));
	}
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(),0,GetMaxMana()));
	}
	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		const float LocalIncomingDamage = GetIncomingDamage();
		SetIncomingDamage(0.f);
		if (LocalIncomingDamage > 0)
		{
			const float NewHealth = GetHealth() - LocalIncomingDamage;
			SetHealth(FMath::Clamp(NewHealth,0,GetMaxHealth() ) );

			const bool bFatal = NewHealth <= 0.f; //是否死亡 
			if (bFatal)
			{
				ICombatInterface* CombatInterface = Cast<ICombatInterface>(Data.Target.GetOwnerActor());
				if (CombatInterface)
				CombatInterface->Die();
			}
			else
			{
				FGameplayTagContainer GameplayTags;
				GameplayTags.AddTag(FAuraGameplayTags::Get().Effects_HitReact);
				Data.Target.TryActivateAbilitiesByTag(GameplayTags);
			}
			ShowFloatingText(Props,LocalIncomingDamage);
		}
	}
}
//@Region:PrimaryAttributes
void UAuraAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Strength,OldStrength);
}

void UAuraAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Intelligence,OldIntelligence);
}

void UAuraAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Resilience,OldResilience);
}

void UAuraAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Vigor,OldVigor);
}
//@Region:SecondaryAttributes
void UAuraAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Armor,OldArmor);
}

void UAuraAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,ArmorPenetration,OldArmorPenetration);
}

void UAuraAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,BlockChance,OldBlockChance);
}

void UAuraAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,CriticalHitChance,OldCriticalHitChance);
}

void UAuraAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,CriticalHitDamage,OldCriticalHitDamage);
}

void UAuraAttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,CriticalHitResistance,OldCriticalHitResistance);
}

void UAuraAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,HealthRegeneration,OldHealthRegeneration);
}

void UAuraAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,ManaRegeneration,OldManaRegeneration);
}
//@RegionVitalAttributes
void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	 GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Health,OldHealth);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,MaxHealth,OldMaxHealth);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Mana,OldMana);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,MaxMana,OldMaxMana);
}