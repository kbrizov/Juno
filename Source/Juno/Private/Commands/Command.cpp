// Christian Rizov's Juno.

#include "Commands/Command.h"

FCommand::FCommand(FPiece* InPiece)
{
	check(InPiece);
	Piece = InPiece;
}
