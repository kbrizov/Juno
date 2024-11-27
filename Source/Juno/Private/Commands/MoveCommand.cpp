#include "Commands/MoveCommand.h"
#include "Tile.h"

FMoveCommand::FMoveCommand(FPiece* InPiece, FTile* InNewPosition)
	: FCommand(InPiece, ECommandType::Move)
{
	check(InNewPosition && InNewPosition->IsEmpty());
	NewPosition = InNewPosition;
}
