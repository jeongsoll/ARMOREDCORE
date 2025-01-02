// Copyright Epic Games, Inc. All Rights Reserved.

#include "ArmoredCoreGameMode.h"
#include "ArmoredCoreCharacter.h"
#include "UObject/ConstructorHelpers.h"

AArmoredCoreGameMode::AArmoredCoreGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
