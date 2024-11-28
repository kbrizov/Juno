// Christian Rizov's Juno.

#include "Commands/MoveCommand.h"
#include "TileVisual.h"

FMoveCommand::FMoveCommand(APieceVisual* InPiece, ATileVisual* InNewTile)
	:FCommand(InPiece)
{
	check(InNewTile);
	NewTile = InNewTile;
}

void FMoveCommand::Execute(const uint32 InDeltaTime)
{
}
