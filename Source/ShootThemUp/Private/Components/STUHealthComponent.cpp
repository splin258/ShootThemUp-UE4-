// Fill out your copyright notice in the Description page of Project Settings.


#include "STUHealthComponent.h"
#include "GameFramework/Actor.h"
#include "Dev/STUFireDamageType.h"
#include "Dev/STUIceDamageType.h"
#include "Engine/World.h"
#include "TimerManager.h" 

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);
// Sets default values for this component's properties
USTUHealthComponent::USTUHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	SetHealth(MaxHeath);
	
	// ...
	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
	}
	
}

void USTUHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0 || IsDead() || !GetWorld()) return;
	
	//UE_LOG(LogHealthComponent, Display, TEXT("Damage: %f"), Damage);

	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	
	if(DamageType)
	{
		if(DamageType->IsA<USTUFireDamageType>())
		{
		//	UE_LOG(LogHealthComponent, Display, TEXT("hoooooot"));
		}
		else if(DamageType->IsA<USTUIceDamageType>())
		{
		//	UE_LOG(LogHealthComponent, Display, TEXT("cooooooooooold"));
		}
	}
	SetHealth(Health - Damage);
	
	if (IsDead())
	{
		OnDeath.Broadcast();
	}
	else if (AutoHeal)
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &USTUHealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
	}
	
}

void USTUHealthComponent::HealUpdate()
{
	SetHealth(Health + HealModifier);

	if (FMath::IsNearlyEqual(Health, MaxHeath) && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
}

void USTUHealthComponent::SetHealth(float NewHealth)
{
	Health = FMath::Clamp(NewHealth, 0.0f, MaxHeath);
	OnHealthChanged.Broadcast(Health);
}

