// Fill out your copyright notice in the Description page of Project Settings.

#include "DelegateHandler.h"
#include "MazeTimerWidget.h"

void UMazeTimerWidget::NativeConstruct()
{
	Super::NativeConstruct();
	DelegateHandler::OnTimerStart.BindUObject(this, &UMazeTimerWidget::StartTimer);
	DelegateHandler::OnTimerStop.AddUObject(this, &UMazeTimerWidget::StopTimer);
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

void UMazeTimerWidget::StopTimer(bool bTimerRanOut)
{
	//DelegateHandler::OnTimerStop.ExecuteIfBound(bTimerRanOut);
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("TimerRanOut")));
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	OnTimerRanOut.Broadcast();
}

void UMazeTimerWidget::ResetTimer()
{
	StopTimer(true);
	CurrentTime = CountdownTime;
	StartTimer();
}

void UMazeTimerWidget::UpdateTimer()
{
	if (CurrentTime > 0)
	{
		CurrentTime -= 1.0f;
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Time Left: %f"), CurrentTime));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("TimerRanOut")));
		DelegateHandler::OnTimerStop.Broadcast(false);
		StopTimer(true);
	}
}

void UMazeTimerWidget::RestartGame()
{
	DelegateHandler::OnRestartGame.ExecuteIfBound();
}
