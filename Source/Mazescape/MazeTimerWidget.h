// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MazeTimerWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimerRanOut);

UCLASS()
class MAZESCAPE_API UMazeTimerWidget : public UUserWidget
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "Timer")
	void StartTimer();

	UFUNCTION(BlueprintCallable, Category = "Timer")
	void StopTimer(bool bTimerRanOut);

	UFUNCTION(BlueprintCallable, Category = "Timer")
	void ResetTimer();

	UPROPERTY(EditAnywhere, Category = "Timer")
	int32 CountdownTime;

public:
	UPROPERTY(BlueprintReadOnly, Category = "Timer")
	float CurrentTime;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnTimerRanOut OnTimerRanOut;

protected:
	FTimerHandle TimerHandle;

	void UpdateTimer();

    virtual void NativeConstruct() override;

};
