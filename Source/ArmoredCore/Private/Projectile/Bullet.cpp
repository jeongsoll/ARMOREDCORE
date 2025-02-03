// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

#include "ArmoredCoreCharacter.h"
#include "JS_Boss.h"
#include "PlayerMainUI.h"
#include "Components/BoxComponent.h"

// Sets default values
ABullet::ABullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root->SetBoxExtent(FVector(32.0f, 16.0f, 16.0f));
	Root->SetCollisionProfileName(TEXT("Bullet"));
	
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
	
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABullet::OnMyBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnMyBeginOverlap(OverlappedComponent , OtherActor , OtherComp , OtherBodyIndex , bFromSweep , SweepResult);

	auto* player = Cast<AArmoredCoreCharacter>(OtherActor);
	if (player)
	{
		player->CharacterTakeDamage(Damage);
		if (player->CurrentHP <= 0)
			player->Dead();
		Destroy();
		return;
	}

	auto* boss = Cast<AJS_Boss>(OtherActor);
	if (boss)
	{
		UE_LOG(LogTemp,Warning,TEXT("Boss hit bullet"));
		boss->CharacterTakeDamage(Damage);
		if (boss->CurrentHP <= 0)
			boss->Dead();
		Destroy();
		
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Boss call failed"));
	}
}



