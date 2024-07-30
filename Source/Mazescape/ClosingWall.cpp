// Fill out your copyright notice in the Description page of Project Settings.


#include "ClosingWall.h"
#include "MazeGenerator.h"

// Sets default values
AClosingWall::AClosingWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AClosingWall::BeginPlay()
{
	Super::BeginPlay();
	

    if (GeneratorToWatch)
    {
	    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("This is an on-screen message!"));
        GeneratorToWatch->OnMazeCompleteDelegate.AddDynamic(this, &AClosingWall::Yippie);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("GeneratorToWatch is not assigned!"));
    }
}

// Called every frame
void AClosingWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AClosingWall::Yippie(AActor* ActiveGen)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("This is an on-screen message!"));
	SetActorScale3D(GetActorScale3D() + 1.0f);
}

