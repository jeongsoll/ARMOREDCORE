﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacterClass.h"
#include "GameFramework/Character.h"
#include "JS_Boss.generated.h"

UCLASS()
class ARMOREDCORE_API AJS_Boss : public ABaseCharacterClass
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AJS_Boss();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class AArmoredCoreCharacter* PlayerCharacter;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Dead() override;
};
