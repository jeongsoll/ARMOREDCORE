// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

#include "ArmoredCoreCharacter.h"
#include "JS_Boss.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
ABullet::ABullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	Root->SetBoxExtent(FVector(32.0f, 16.0f, 16.0f));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
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


	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(Root);
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

	Root->SetGenerateOverlapEvents(true);
	Root->SetCollisionProfileName(TEXT("Bullet"));
	
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	Root->OnComponentBeginOverlap.AddDynamic(this,&ABullet::OnMyBeginOverlap);
	LifeTime = 8.0f;
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurrentTime += DeltaTime;
	if (CurrentTime > LifeTime)
		this->Destroy();
}

void ABullet::OnMyBeginOverlap(UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult)
{
	auto* boss = Cast<AJS_Boss>(OtherActor);
	if (boss)
	{
		UE_LOG(LogTemp,Warning,TEXT("Boss hit"));
		Destroy();
	}

	auto* player = Cast<AArmoredCoreCharacter>(OtherActor);
	if (player)
	{
		UE_LOG(LogTemp,Warning,TEXT("Player hit"));
		Destroy();
	}
}


void ABullet::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}



