// Copyright Epic Games, Inc. All Rights Reserved.

#include "MazescapeGameMode.h"
#include "MazescapeCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMazescapeGameMode::AMazescapeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	/*if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}*/
}
