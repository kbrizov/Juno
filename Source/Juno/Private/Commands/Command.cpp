// Christian Rizov's Juno.

#include "Commands/Command.h"

FCommand::FCommand(FPiece* InPiece, const ECommandType InType)
{
	check(InPiece);
	Piece = InPiece;
	Type = InType;
}
