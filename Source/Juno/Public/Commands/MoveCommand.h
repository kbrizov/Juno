#pragma once

#include "CoreMinimal.h"
#include "Commands/Command.h"

class FTile;

class FMoveCommand final : public FCommand
{
public:
	FMoveCommand(FPiece* InPiece, FTile* InNewPosition);

private:
	FTile* NewPosition;
};
