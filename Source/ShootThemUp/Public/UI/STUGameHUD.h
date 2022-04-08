// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STUGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUGameHUD : public AHUD
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "HUD")
	float HalfLineSize = 10.0f;

	UPROPERTY(EditAnywhere, Category = "HUD")
	float LineThickness = 2.0f;

	UPROPERTY(EditAnywhere, Category = "HUD")
	FLinearColor LineColor = FLinearColor::Black;
	
	virtual void DrawHUD() override;

	
	
private:

	void DrawCrossHair();
};
