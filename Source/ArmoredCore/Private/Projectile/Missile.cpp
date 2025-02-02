// Fill out your copyright notice in the Description page of Project Settings.


#include "Missile.h"

#include "Components/BoxComponent.h"

// Sets default values
AMissile::AMissile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root->SetBoxExtent(FVector(32.0f, 16.0f, 16.0f));
	Mesh->SetRelativeScale3D(FVector(1.0f, 0.25f, 0.25f));
	
	ConstructorHelpers::FObjectFinder<UStaticMesh> bulletMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (bulletMesh.Succeeded())
	{
		Mesh->SetStaticMesh(bulletMesh.Object);
	}
	
	ConstructorHelpers::FObjectFinder<UMaterial> bulletMaterial(TEXT("/Script/Engine.Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
	if (bulletMaterial.Succeeded())
	{
		Mesh->SetMaterial(0, bulletMaterial.Object);
	}
	
	Root->SetCollisionProfileName(TEXT("Missile"));
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

