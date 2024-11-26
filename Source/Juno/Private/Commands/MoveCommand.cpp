#include "Commands/MoveCommand.h"
#include "Tile.h"

FMoveCommand::FMoveCommand(TSharedPtr<FPiece> InPiece, TSharedPtr<FTile> InNewPosition)
	: FCommand(InPiece)
{
	check(InNewPosition.IsValid());
	check(InNewPosition->IsEmpty());
	NewPosition = InNewPosition;
}

void FMoveCommand::Execute(const float DeltaTime)
{
	checkf(false, TEXT("Implement this!"));
}
