#include "Commands/MoveCommandData.h"
#include "Tile.h"

FMoveCommandData::FMoveCommandData(FPiece* InPiece, FTile* InNewTile)
	: FCommandData(InPiece, ECommandType::Move), NewTile(InNewTile)
{
	check(InNewTile);
}
