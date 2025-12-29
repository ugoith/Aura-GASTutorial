// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseCharacter.h"
#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GASTutorial/GASTutorial.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Projectile,ECR_Overlap);
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	
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

int32 ABaseCharacter::GetLevel () const
{
	return 0;
}

FVector ABaseCharacter::GetCombatSocketLocation()
{	//check(Weapon);
	return Weapon->GetSocketLocation(WeaponTipSocketName);
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}
//子类PlayerCharacter的InitAbilityActorInfo()进行调用
void ABaseCharacter::InitializeAttributes() const
{
	ApplyGameplayEffectToSelf(DefaultPrimaryAttributes,1.f);
	ApplyGameplayEffectToSelf(DefaultSecondaryAttributes,1.f);
	ApplyGameplayEffectToSelf(DefaultVitalAttributes,1.f);
}

void ABaseCharacter::ApplyGameplayEffectToSelf(const TSubclassOf<UGameplayEffect>& GameplayEffect,float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffect);
	FGameplayEffectContextHandle GECH = GetAbilitySystemComponent()->MakeEffectContext();
	GECH.AddSourceObject(this);
	const FGameplayEffectSpecHandle GES = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffect,Level,GECH);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*GES.Data.Get(),GetAbilitySystemComponent());
	//const FGameplayEffectSpec &Spec, UAbilitySystemComponent *Target, FPredictionKey PredictionKey
}

void ABaseCharacter::InitAbilityActorInfo()
{
	
}

void ABaseCharacter::AddCharacterAbilities()
{
	if (!HasAuthority()) return;
	AbilitySystemComponent->AddCharacterAbilities(StartUpAbilities);
	
}



