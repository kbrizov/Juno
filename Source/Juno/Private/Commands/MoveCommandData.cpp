#include "Commands/MoveCommandData.h"
#include "Tile.h"

FMoveCommandData::FMoveCommandData(FPiece* InPiece, FTile* InNewPosition)
	: FCommandData(InPiece, ECommandType::Move)
{
	check(InNewPosition);
	NewPosition = InNewPosition;
}
