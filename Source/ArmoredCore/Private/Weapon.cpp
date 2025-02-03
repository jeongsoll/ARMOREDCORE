// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "Aim.h"
#include "LockAim.h"
#include "PlayerMainUI.h"


UWeapon::UWeapon()
{
	Damage = 0;
	ReloadTime = 0;
	MaxAmmo = 0;
	RemainAmmo = 0;
	IsReloading = false;
	IsProjectile = false;
}

void UWeapon::SetChoosenWeapon(EPlayerWeapon choosedWeapon, EPlayerUsedWeaponPos weaponPos)
{
	WeaponPos = weaponPos;
	if (choosedWeapon == EPlayerWeapon::Rifle)
	{
		IsProjectile = true;
		ProjectileType = EProjectileType::Bullet;
		Damage = 100.0f;
		ReloadTime = 3.0f;
		Magazine = 360;
		RemainAmmo = 12;
		MaxAmmo = 12;
	}
	else if (choosedWeapon == EPlayerWeapon::Missile)
	{
		IsProjectile = true;
		ProjectileType = EProjectileType::Missile;
		Damage = 500.0f;
		ReloadTime = 5.0f;
		Magazine = 100;
		RemainAmmo = 4;
		MaxAmmo = 4;
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
		GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle,this,&UWeapon::RefillAmmo,ReloadTime,false);

	if (!IsReloading)
		IsReloading = true;
}

void UWeapon::RefillAmmo()
{
	UE_LOG(LogTemp,Warning,TEXT("Refill call"));
	if (Magazine >= MaxAmmo)
	{
		RemainAmmo = MaxAmmo;
		Magazine -= MaxAmmo;
		IsReloading = false;
		GetWorld()->GetTimerManager().ClearTimer(ReloadTimerHandle);
		AArmoredCoreCharacter* player = Cast<AArmoredCoreCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
		player->MainUI->PlayerAim->SetAmmoValue(WeaponPos,RemainAmmo,MaxAmmo);
		player->MainUI->PlayerLockAim->SetAmmoValue(WeaponPos,RemainAmmo,MaxAmmo);
	}
}
