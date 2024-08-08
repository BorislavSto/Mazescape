// Fill out your copyright notice in the Description page of Project Settings.


#include "ClosingWall.h"
#include "DelegateHandler.h"
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
 
    DelegateHandler::MyDelegate.BindUObject(this, &AClosingWall::Yippie2);
	    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("This is an on-screen message!"));

        DelegateHandler::MyDelegate2.AddUObject(this, &AClosingWall::Yippie3);
    /*if (GeneratorToWatch)
    {
	    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("This is an on-screen message!"));
        GeneratorToWatch->OnMazeCompleteDelegate.AddDynamic(this, &AClosingWall::Yippie);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("GeneratorToWatch is not assigned!"));
    }*/
}

// Called every frame
void AClosingWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AClosingWall::Yippie3(AActor* gengen)
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("This is an on-screen message!"));
}

void AClosingWall::Yippie2()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("This is an on-screen message!"));
}

void AClosingWall::Yippie(AActor* ActiveGen)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, TEXT("This is an on-screen message!"));
	SetActorScale3D(GetActorScale3D() + 1.0f);
}

