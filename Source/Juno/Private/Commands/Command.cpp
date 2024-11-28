#include "Commands/Command.h"

FCommand::FCommand(APieceVisual* InPiece)
{
	check(InPiece)
	Piece = InPiece;
}

bool FCommand::IsExecuting() const
{
	return false;
}
