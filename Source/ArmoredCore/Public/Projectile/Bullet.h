// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class ARMOREDCORE_API ABullet : public AActor
{
	GENERATED_BODY()



public:
	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* ProjectileMovementComponent;
	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void FireInDirection(const FVector& ShootDirection);
	
	UPROPERTY(EditAnywhere)
	class UBoxComponent* Root;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	float LifeTime;

	UPROPERTY(EditAnywhere)
	float CurrentTime;
};
