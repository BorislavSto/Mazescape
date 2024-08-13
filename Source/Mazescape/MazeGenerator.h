// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeGenerator.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMazeCompleteDelegate, AActor*, ActiveGen);

UCLASS()
class MAZESCAPE_API AMazeGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMazeGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SimulateMaze(bool* outBool);
	void GenerateMaze();

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnMazeCompleteDelegate OnMazeCompleteDelegate;

	UPROPERTY(EditAnywhere, Category = "Maze Config")
	TSubclassOf<ACharacter> PlayerCharacterClass;

	UPROPERTY(EditAnywhere, Category = "Maze Config")
	TSubclassOf<ACharacter> EnemyCharacterClass;

	UPROPERTY(EditAnywhere, Category = "Maze Config")
	int32 Width = 10;

	UPROPERTY(EditAnywhere, Category = "Maze Config")
	int32 Height = 10;

	UPROPERTY(EditAnywhere, Category = "Maze Config")
	int32 MaxIterations = 10;

	UPROPERTY(EditAnywhere, Category = "Maze Config")
	TSubclassOf<AActor> SpecialFloorActorClass;

	UPROPERTY(EditAnywhere, Category = "Maze Config")
	TSubclassOf<AActor> WallActorClass;

	UPROPERTY(EditAnywhere, Category = "Maze Config")
	TSubclassOf<AActor> FloorActorClass;

	UPROPERTY(EditAnywhere, Category = "Maze Config")
	FVector2D StartPos = FVector2D(0.0f, 0.0f);

	UPROPERTY(EditAnywhere, Category = "Maze Config")
	FVector2D EndPos = FVector2D(0.0f, 0.0f);

private:

	int32 Iterations = 0;

	FVector2D CurrentPosition;

	TArray<bool> Grid;

	void SetValue(FVector2D Position, bool Value);

	void ForceSetValue(FVector2D Position, bool Value);

	bool GetValue(FVector2D Position) const;

	bool IsWithinBounds(FVector2D Position) const;

	int32 ValidPosition(FVector2D Position) const;

	void SpawnPlayer();

	void SpawnEnemy(FVector2D Position);

	void CustomInit();

};
