// Copyright Epic Games, Inc. All Rights Reserved.

#include "MazescapeGameMode.h"
#include "MazescapeCharacter.h"
#include "DelegateHandler.h"
#include "UObject/ConstructorHelpers.h"

AMazescapeGameMode::AMazescapeGameMode()
{
	DelegateHandler::OnTimerStop.AddUObject(this, &AMazescapeGameMode::TimerRanOut);
    DelegateHandler::OnPlayerLoose.BindUObject(this, &AMazescapeGameMode::PlayerLost);
    
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Game Mode Initialized"));
    else
        UE_LOG(LogTemp, Warning, TEXT("GEngine is not available"));
    
    // set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	/*if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}*/
}

void AMazescapeGameMode::TimerRanOut(bool bTimerRanOut)
{
    RemovePlayerCharacter();
}

void AMazescapeGameMode::PlayerLost() 
{
    RemovePlayerCharacter();
}

void AMazescapeGameMode::RemovePlayerCharacter()
{
    UWorld* World = GetWorld();
    if (!World)
        return;

    APlayerController* PlayerController = World->GetFirstPlayerController();
    if (!PlayerController)
        return;

    ACharacter* PlayerCharacter = PlayerController->GetCharacter();
    if (!PlayerCharacter)
        return;

    PlayerCharacter->Destroy();

    DelegateHandler::OnTimerStop.Broadcast(true);
}
