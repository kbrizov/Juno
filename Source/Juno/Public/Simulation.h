// Christian Rizov's Juno.

#pragma once

#include "CoreMinimal.h"

class FCommandData;
class FGrid;
class FPiece;
class FTile;

/**
 * This class mocks a server.
 */
class JUNO_API FSimulation final
{
public:
    explicit FSimulation(
        TQueue<TUniquePtr<FCommandData>>* InCommandsData,
        const uint32 InGridRows,
        const uint32 InGridColumns,
        const int32 InRandomSeed = 1024);

    ~FSimulation();

    void FixedUpdate(const float InDeltaTime);

    const FGrid* GetGrid() const;
    const FPiece* GetPlayerPiece() const;
    const FPiece* GetEnemyPiece() const;

private:
    TQueue<TUniquePtr<FCommandData>>* CommandsData = nullptr;
    const int32 RandomSeed;

    TUniquePtr<FGrid> Grid;
    TUniquePtr<FPiece> PlayerPiece;
    TUniquePtr<FPiece> EnemyPiece;

    void UpdatePlayer();
    void UpdateEnemy();
    void UpdatePiece(
        FPiece& InAttacker,
        FPiece& InTarget);

    FTile* GetRandomEmptyTile(const int32 InSeed) const;
};

inline const FGrid* FSimulation::GetGrid() const
{
    return Grid.Get();
}

inline const FPiece* FSimulation::GetPlayerPiece() const
{
    return PlayerPiece.Get();
}

inline const FPiece* FSimulation::GetEnemyPiece() const
{
    return EnemyPiece.Get();
}
