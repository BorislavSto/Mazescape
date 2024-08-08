// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ClosingWall.generated.h"

UCLASS()
class MAZESCAPE_API AClosingWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClosingWall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UFUNCTION()
	void Yippie(AActor* ActiveGen);

	UFUNCTION()
	void Yippie2();

	UFUNCTION()
	void Yippie3(AActor* gengen);

	UPROPERTY(EditAnywhere)
	class AMazeGenerator* GeneratorToWatch;
};
