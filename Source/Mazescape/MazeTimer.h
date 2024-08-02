// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MazeTimer.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimerUpdated, int32, RemainingTime); //FOnTimerUpdated, int32, RemainingTime);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimerFinished);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAZESCAPE_API UMazeTimer : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMazeTimer();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/*UFUNCTION(BlueprintCallable, Category = "Timer")
	void StartTimer();

	UFUNCTION(BlueprintCallable, Category = "Timer")
	void StopTimer();

	UFUNCTION(BlueprintCallable, Category = "Timer")
	void ResetTimer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
	int32 CountdownTime;*/

	//UPROPERTY(BlueprintAssignable, Category = "Timer")
	//FOnTimerUpdated OnTimerUpdated;

	/*UPROPERTY(BlueprintAssignable, Category = "Timer")
	FTimerFinished OnTimerFinished;*/


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
