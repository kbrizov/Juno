// Christian Rizov's Juno.

#pragma once

#include "CoreMinimal.h"
#include "Commands/CommandData.h"

class FTile;

class FMoveCommandData final : public FCommandData
{
public:
    FMoveCommandData(
        FPiece* InPiece,
        FTile* InNewTile);

    FTile* GetNewTile() const;

private:
    FTile* NewTile;
};

inline FTile* FMoveCommandData::GetNewTile() const
{
    return NewTile;
}
