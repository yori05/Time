// Copyright Epic Games, Inc. All Rights Reserved.

#include "TimeGameMode.h"
#include "TimeCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATimeGameMode::ATimeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
