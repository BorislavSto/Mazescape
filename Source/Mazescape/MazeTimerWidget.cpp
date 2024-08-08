// Fill out your copyright notice in the Description page of Project Settings.

#include "DelegateHandler.h"
#include "MazeTimerWidget.h"

void UMazeTimerWidget::NativeConstruct()
{
	Super::NativeConstruct();
	DelegateHandler::OnTimerStart.BindUObject(this, &UMazeTimerWidget::StartTimer);
	DelegateHandler::OnTimerStop.BindUObject(this, &UMazeTimerWidget::StopTimer);
	DelegateHandler::OnTimerReset.BindUObject(this, &UMazeTimerWidget::ResetTimer);
}

void UMazeTimerWidget::StartTimer()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Time Left")));
	if (CountdownTime > 0)
	{
		CurrentTime = CountdownTime;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UMazeTimerWidget::UpdateTimer, 1.0f, true);
	}
}

void UMazeTimerWidget::StopTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void UMazeTimerWidget::ResetTimer()
{
	StopTimer();
	CurrentTime = CountdownTime;
	StartTimer();
}

void UMazeTimerWidget::UpdateTimer()
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