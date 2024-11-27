#include "Commands/MoveCommand.h"
#include "Tile.h"

FMoveCommand::FMoveCommand(FPiece* InPiece, FTile* InNewPosition)
	: FCommand(InPiece)
{
	check(InNewPosition && InNewPosition->IsEmpty());
	NewPosition = InNewPosition;
}

void FMoveCommand::Execute(const float DeltaTime)
{
	checkf(false, TEXT("Implement this!"));
}
