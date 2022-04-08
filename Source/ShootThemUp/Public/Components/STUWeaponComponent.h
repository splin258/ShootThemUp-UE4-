// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUWeaponComponent.generated.h"

class ASTUBaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USTUWeaponComponent();

	void Fire();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ASTUBaseWeapon> WeaponClass;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	FName WeaponAttachPointName = "WeaponSocket";

	// Called when the game starts
	virtual void BeginPlay() override;

private:	

	UPROPERTY()
	ASTUBaseWeapon* CurrentWeapon = nullptr;

	void SpawnWeapon();
};
