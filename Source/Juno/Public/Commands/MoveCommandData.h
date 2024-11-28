#pragma once

#include "CoreMinimal.h"
#include "Commands/CommandData.h"

class FTile;

class FMoveCommandData final : public FCommandData
{
public:
	FMoveCommandData(FPiece* InPiece, FTile* InNewTile);

	FTile* GetNewPosition() const;

private:
	FTile* NewTile;
};

inline FTile* FMoveCommandData::GetNewPosition() const
{
	return NewTile;
}
