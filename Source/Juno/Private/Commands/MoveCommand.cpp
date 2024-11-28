// Christian Rizov's Juno.

#include "Commands/MoveCommand.h"

#include "PieceVisual.h"
#include "TileVisual.h"

FMoveCommand::FMoveCommand(APieceVisual* InPiece, ATileVisual* InNewTile, const FVector& InOffset)
	:FCommand(InPiece), Offset(InOffset)
{
	check(InNewTile);
	NewTile = InNewTile;
}

void FMoveCommand::Execute(const uint32 InDeltaTime)
{
	Piece->MoveTo(NewTile, Offset);
}
