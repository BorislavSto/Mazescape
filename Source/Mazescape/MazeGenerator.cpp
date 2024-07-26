#include "MazeGenerator.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"

AMazeGenerator::AMazeGenerator()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMazeGenerator::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("BeginPlay called"));

    // Initialize the grid
    Grid.SetNumZeroed(Width * Height);

    SetValue(StartPos, true);

    SimulateMaze();
    GenerateMaze();
}

void AMazeGenerator::SimulateMaze()
{
    TArray<FVector2D> PathStack;
    FVector2D CurrentPosition = StartPos;

    SetValue(CurrentPosition, true);
    PathStack.Add(CurrentPosition);

    int32 PathLengthCounter = 1; // Initialize path length counter

    while (PathStack.Num() > 0 && PathLengthCounter < PathLength)
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

            if (IsWithinBounds(NewPosition) && !GetValue(NewPosition))
            {
                SetValue(NewPosition, true);
                PathStack.Add(NewPosition);
                CurrentPosition = NewPosition;
                PathLengthCounter++; // Increment path length counter
                bMoved = true;
                break;
            }
        }

        if (!bMoved)
        {
            PathStack.Pop();
            if (PathStack.Num() > 0)
            {
                CurrentPosition = PathStack.Last();
            }
        }
    }
}

void AMazeGenerator::GenerateMaze()
{
    FVector ActorLocation = GetActorLocation(); // Get the actor's location

    for (int32 Y = 0; Y < Height; ++Y)
    {
        for (int32 X = 0; X < Width; ++X)
        {
            FVector Location = ActorLocation + FVector(X * 100.0f, Y * 100.0f, 0.0f); // Offset by actor location

            if (GetValue(FVector2D(X, Y)))
                GetWorld()->SpawnActor<AActor>(FloorActorClass, Location, FRotator::ZeroRotator);
            else
                GetWorld()->SpawnActor<AActor>(WallActorClass, Location, FRotator::ZeroRotator);
        }
    }
}

void AMazeGenerator::SetValue(FVector2D Position, bool Value)
{
    if (IsWithinBounds(Position))
    {
        Grid[int(Position.Y) * Width + int(Position.X)] = Value;
    }
}

bool AMazeGenerator::GetValue(FVector2D Position) const
{
    if (!IsWithinBounds(Position))
        return false;

    return Grid[int(Position.Y) * Width + int(Position.X)];
}

bool AMazeGenerator::IsWithinBounds(FVector2D Position) const
{
    return Position.X >= 0 && Position.X < Width && Position.Y >= 0 && Position.Y < Height;
}
