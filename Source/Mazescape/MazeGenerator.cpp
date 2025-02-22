#include "MazeGenerator.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"
#include "DelegateHandler.h"

AMazeGenerator::AMazeGenerator()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMazeGenerator::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("BeginPlay called"));

    if (!FloorActorClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("FloorActorClass is not valid or not derived from AActor"));
        return;
    }
    else
        UE_LOG(LogTemp, Warning, TEXT("FloorActorClass is valid"));
    
    if (!WallActorClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("WallActorClass is not valid or not derived from AActor"));
        return;
    }
    else
        UE_LOG(LogTemp, Warning, TEXT("WallActorClass is valid"));
    
    if (!PlayerCharacterClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerCharacterClass is not valid or not derived from AActor"));
        return;
    }
    else
        UE_LOG(LogTemp, Warning, TEXT("PlayerCharacterClass is valid"));

    DelegateHandler::OnRestartGame.BindUObject(this, &AMazeGenerator::RegenerateMaze);

    GetWorld()->GetTimerManager().SetTimerForNextTick(this, &AMazeGenerator::CustomInit);
}

void AMazeGenerator::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMazeGenerator::CustomInit()
{
    for (int i = Iterations; i < MaxIterations; i++) 
    {
        bool acceptableSimulation;
        SimulateMaze(&acceptableSimulation);

        if (acceptableSimulation)
            break;
    }

    GenerateMaze();
}

void AMazeGenerator::SimulateMaze(bool* outBool)
{
    Grid.Empty();
    Grid.SetNumZeroed(Width * Height);
    ForceSetValue(StartPos, true);

    TArray<FVector2D> PathStack;
    CurrentPosition = StartPos;

    ForceSetValue(CurrentPosition, true);
    PathStack.Add(CurrentPosition);

    int32 PathLengthCounter = 0;
    while (PathStack.Num() > 0)
    {
        FVector2D LastPosition = PathStack.Last();
        TArray<FVector2D> PossibleDirections = {
            FVector2D(0, 1),   // Up
            FVector2D(0, -1),  // Down
            FVector2D(-1, 0),  // Left
            FVector2D(1, 0)    // Right
        };

        bool bMoved = false;

        while (PossibleDirections.Num() > 0)
        {
            int32 RandomIndex = FMath::RandRange(0, PossibleDirections.Num() - 1);
            FVector2D RandomDirection = PossibleDirections[RandomIndex];
            PossibleDirections.RemoveAt(RandomIndex);

            FVector2D NewPosition = LastPosition + RandomDirection;

            if (IsWithinBounds(NewPosition) && !GetValue(NewPosition) && ValidPosition(NewPosition) <= 1)
            {
                SetValue(NewPosition, true);
                PathStack.Add(NewPosition);
                CurrentPosition = NewPosition;
                PathLengthCounter++;
                bMoved = true;
                SpawnEnemy(CurrentPosition);

                if (CurrentPosition == EndPos)
                {
                    UE_LOG(LogTemp, Warning, TEXT("Reached the end position"));
                    *outBool = true;
                    return;
                }
                break;
            }
        }

        if (!bMoved)
        {
            PathStack.Pop();
        
            if (PathStack.Num() > 0)
                CurrentPosition = PathStack.Last();
        }
    }

    Iterations++;
    *outBool = false;
    return;
}

void AMazeGenerator::GenerateMaze()
{
    FVector ActorLocation = GetActorLocation(); // Get the actor's location

    for (int32 Y = 0; Y < Height; ++Y)
    {
        for (int32 X = 0; X < Width; ++X)
        {
            FVector Location = ActorLocation + FVector(X * 500.0f, Y * 500.0f, 0.0f); // Offset by actor location

            AActor* SpawnedActor = nullptr;

            if (GetValue(FVector2D(X, Y)))
            {
                if (FVector2D(X, Y) == EndPos)
                    SpawnedActor = GetWorld()->SpawnActor<AActor>(SpecialFloorActorClass, Location, FRotator::ZeroRotator);
                else
                    SpawnedActor = GetWorld()->SpawnActor<AActor>(FloorActorClass, Location, FRotator::ZeroRotator);
            }
            else
                SpawnedActor = GetWorld()->SpawnActor<AActor>(WallActorClass, Location, FRotator::ZeroRotator);

            if (SpawnedActor)
                SpawnedActors.Add(SpawnedActor);
        }
    }

    SpawnPlayer();
}

void AMazeGenerator::SetValue(FVector2D Position, bool Value)
{
    if (IsWithinBounds(Position))
        Grid[int(Position.Y) * Width + int(Position.X)] = Value;
}

void AMazeGenerator::ForceSetValue(FVector2D Position, bool Value)
{
    Grid[int(Position.Y) * Width + int(Position.X)] = Value;
}

bool AMazeGenerator::GetValue(FVector2D Position) const
{
    if (!IsWithinBounds(Position))
        return false;

    return Grid[int(Position.Y) * Width + int(Position.X)];
}

bool AMazeGenerator::IsWithinBounds(FVector2D Position) const
{
    return Position.X >= 1 && Position.X < Width - 1 && Position.Y >= 1 && Position.Y < Height - 1;
}

int32 AMazeGenerator::ValidPosition(FVector2D Position) const
{
    int32 TrueCount = 0;
    TArray<FVector2D> Directions = {
        FVector2D(0, 1),   // Up
        FVector2D(0, -1),  // Down
        FVector2D(-1, 0),  // Left
        FVector2D(1, 0)    // Right
    };

    for (const FVector2D& Direction : Directions)
    {
        FVector2D Neighbor = Position + Direction;
        
        if (IsWithinBounds(Neighbor) && GetValue(Neighbor))
            TrueCount++;
    }

    return TrueCount;
}

void AMazeGenerator::SpawnPlayer()
{
    if (PlayerCharacterClass)
    {
        FVector PlayerSpawnLocation = GetActorLocation() + FVector(StartPos.X * 500.0f, StartPos.Y * 500.0f, 200.0f);

        FRotator PlayerSpawnRotation(0.0f, 0.0f, 0.0f);
        ACharacter* PlayerCharacter = GetWorld()->SpawnActor<ACharacter>(PlayerCharacterClass, PlayerSpawnLocation, PlayerSpawnRotation);

        if (PlayerCharacter)
        {
            APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
 
            if (PlayerController)
                PlayerController->Possess(Cast<APawn>(PlayerCharacter)); // Cast to APawn

            SpawnedActors.Add(PlayerCharacter);
        }
    }

    DelegateHandler::OnTimerStart.ExecuteIfBound();

    if (DelegateHandler::MyDelegate2.IsBound())
        DelegateHandler::MyDelegate2.Broadcast(this);

    if (DelegateHandler::MyDelegate.IsBound())
        DelegateHandler::MyDelegate.Execute();
    else 
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("This is an on-screen message!"));

    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("This is an on-screen message!"));
    OnMazeCompleteDelegate.Broadcast(this);
}


void AMazeGenerator::SpawnEnemy(FVector2D Position)
{
    int32 RandomNumber = FMath::RandRange(1, 30);
    if (RandomNumber == 1)
    {
        if (EnemyCharacterClass)
        {
            FVector EnemySpawnLocation = GetActorLocation() + FVector(Position.X * 500.0f, Position.Y * 500.0f, 101.0f);

            FRotator EnemySpawnRotation(0.0f, 0.0f, 0.0f);

            ACharacter* EnemyCharacter = GetWorld()->SpawnActor<ACharacter>(EnemyCharacterClass, EnemySpawnLocation, EnemySpawnRotation);

            if (EnemyCharacter)
            {
                EnemyCharacter->SpawnDefaultController();
                SpawnedEnemies.Add(EnemyCharacter);
            }
        }
    }
}

void AMazeGenerator::ClearMaze()
{
    for (AActor* SpawnedActor : SpawnedActors)
    {
        if (IsValid(SpawnedActor))
            SpawnedActor->Destroy();
    }
    SpawnedActors.Empty();

    for (ACharacter* SpawnedEnemy : SpawnedEnemies)
    {
        if (IsValid(SpawnedEnemy))
            SpawnedEnemy->Destroy();
    }
    SpawnedEnemies.Empty();
}


void AMazeGenerator::RegenerateMaze()
{
    ClearMaze();
    CustomInit();
}
