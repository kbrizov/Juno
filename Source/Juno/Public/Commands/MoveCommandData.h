#pragma once

#include "CoreMinimal.h"
#include "Commands/CommandData.h"

class FTile;

class FMoveCommandData final : public FCommandData
{
public:
	FMoveCommandData(FPiece* InPiece, FTile* InNewPosition);

	FTile* GetNewPosition() const;

private:
	FTile* NewPosition;
};

inline FTile* FMoveCommandData::GetNewPosition() const
{
	return NewPosition;
}
