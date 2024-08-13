// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "MazescapeCharacter.h"
#include "DelegateHandler.h"
#include "AFinalPlatform.h"

// Sets default values
AAFinalPlatform::AAFinalPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    RootComponent = CollisionBox;

    if (CollisionBox)
        CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AAFinalPlatform::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AAFinalPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAFinalPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAFinalPlatform::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // Check if the overlapping actor is the player character
    AMazescapeCharacter* PlayerCharacter = Cast<AMazescapeCharacter>(OtherActor);

    if (PlayerCharacter)
    {
        // Trigger the event here
        UE_LOG(LogTemp, Warning, TEXT("Player reached the final platform!"));

        // You can call a BlueprintImplementable function here, or trigger an event
        DelegateHandler::OnTimerStop.Broadcast(true);
        //DelegateHandler::OnPlayerWin.ExecuteIfBound();
    }
}
