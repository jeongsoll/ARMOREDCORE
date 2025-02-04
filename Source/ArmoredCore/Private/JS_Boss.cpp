// Fill out your copyright notice in the Description page of Project Settings.


#include "JS_Boss.h"

#include "ArmoredCoreCharacter.h"

// Sets default values
AJS_Boss::AJS_Boss()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJS_Boss::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = Cast<AArmoredCoreCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
}

// Called every frame
void AJS_Boss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AJS_Boss::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AJS_Boss::Dead()
{
	Super::Dead();
	if (PlayerCharacter)
	{
		PlayerCharacter->GameClear();
		PlayerCharacter->CurrentHP = 99999.0f;
	}

	SetActorHiddenInGame(true);
		
}
