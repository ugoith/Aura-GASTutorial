// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseCharacter.h"
#include "AbilitySystemComponent.h"
// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Weapon=CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");//创建一个名为Weapon的骨骼网格体组件
	Weapon->SetupAttachment(GetMesh(),FName("WeaponHandSocket"));//附加到父级（首个骨骼网格体）的名为WeaponHandSocket的插槽中
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);//设置武器碰撞为无碰撞
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* ABaseCharacter::GetAttributeSet() const
{
	return AttributeSet;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseCharacter::InitializePrimaryAttributes() const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(DefaultPrimaryAttributes);
	const FGameplayEffectContextHandle GECH = GetAbilitySystemComponent()->MakeEffectContext();
	const FGameplayEffectSpecHandle GES = GetAbilitySystemComponent()->MakeOutgoingSpec(DefaultPrimaryAttributes,1.0,GECH);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*GES.Data.Get(),GetAbilitySystemComponent());	//const FGameplayEffectSpec &Spec, UAbilitySystemComponent *Target, FPredictionKey PredictionKey
}

void ABaseCharacter::InitAbilityActorInfo()
{
	
}



