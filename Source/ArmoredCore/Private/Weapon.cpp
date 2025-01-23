// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "Aim.h"

UWeapon::UWeapon()
{
	Damage = 0;
	ReloadTime = 0;
	MaxArmor = 0;
	RemainArmor = 0;
	IsReloading = false;
	IsProjectile = false;
}

void UWeapon::SetChoosenWeapon(EPlayerWeapon choosedWeapon)
{
	if (choosedWeapon == EPlayerWeapon::Rifle)
	{
		IsProjectile = true;
		Damage = 100.0f;
		ReloadTime = 3.0f;
		Magazine = 360;
		RemainArmor = 12;
		MaxArmor = 12;
	}
	else if (choosedWeapon == EPlayerWeapon::Missile)
	{
		IsProjectile = true;
		Damage = 500.0f;
		ReloadTime = 5.0f;
		Magazine = 100;
		RemainArmor = 4;
		MaxArmor = 4;
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Beam saber called"));
		IsProjectile = false;
	}
}

void UWeapon::Reload()
{
	UE_LOG(LogTemp,Warning,TEXT("Reload call"));
	
	if (!GetWorld()->GetTimerManager().IsTimerActive(ReloadTimerHandle) && !IsReloading)
		GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle,this,&UWeapon::RefillArmor,ReloadTime,false);

	if (!IsReloading)
		IsReloading = true;
}

void UWeapon::RefillArmor()
{
	UE_LOG(LogTemp,Warning,TEXT("Refill call"));
	if (Magazine >= MaxArmor)
	{
		RemainArmor = MaxArmor;
		Magazine -= MaxArmor;
		IsReloading = false;
		GetWorld()->GetTimerManager().ClearTimer(ReloadTimerHandle);
		AArmoredCoreCharacter* player = Cast<AArmoredCoreCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
		player->MainUI->PlayerAim->SetArmorValue(RemainArmor,MaxArmor);
	}
}
