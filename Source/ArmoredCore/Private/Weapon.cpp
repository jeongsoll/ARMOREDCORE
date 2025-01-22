// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

UWeapon::UWeapon()
{
	Damage = 0;
	ReloadTime = 0;
	MaxArmor = 0;
	RemainArmor = 0;
}

void UWeapon::SetChoosenWeapon(EPlayerWeapon choosedWeapon)
{
	if (choosedWeapon == EPlayerWeapon::Rifle)
	{
		Damage = 100.0f;
		ReloadTime = 3.0f;
		Magazine = 300;
		RemainArmor = 12;
		MaxArmor = 12;
	}
	else if (choosedWeapon == EPlayerWeapon::Missile)
	{
		Damage = 500.0f;
		ReloadTime = 5.0f;
		Magazine = 100;
		RemainArmor = 4;
		MaxArmor = 4;
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("beam saber called"));
	}
}
