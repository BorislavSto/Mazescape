// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeTimer.h"

// Sets default values for this component's properties
UMazeTimer::UMazeTimer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	CountdownTime = 0;
	CurrentTime = 0.0f;
	// ...
}


// Called when the game starts
void UMazeTimer::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}


// Called every frame
void UMazeTimer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UMazeTimer::StartTimer() 
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Time Left")));
	if (CountdownTime > 0)
	{
		CurrentTime = CountdownTime;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UMazeTimer::UpdateTimer, 1.0f, true);
	}
}

void UMazeTimer::StopTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void UMazeTimer::ResetTimer()
{
	StopTimer();
	CurrentTime = CountdownTime;
	StartTimer();
}

void UMazeTimer::UpdateTimer()
{
	if (CurrentTime > 0)
	{
		CurrentTime -= 1.0f;
		// You can add a debug message or update your UI here
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Time Left: %f"), CurrentTime));
		}
	}
	else
	{
		StopTimer();
		// Handle the event when the timer reaches zero
	}
}
