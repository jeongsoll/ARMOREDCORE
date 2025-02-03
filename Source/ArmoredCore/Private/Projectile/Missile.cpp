// Fill out your copyright notice in the Description page of Project Settings.


#include "Missile.h"

#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AMissile::AMissile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root->SetBoxExtent(FVector(32.0f, 16.0f, 16.0f));
	Root->SetCollisionProfileName(TEXT("Missile"));

	ProjectileMovementComponent->bShouldBounce = false;
	ProjectileMovementComponent->InitialSpeed = 1500.0f;
}

// Called when the game starts or when spawned
void AMissile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

