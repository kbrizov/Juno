// Christian Rizov's Juno.

#include "Commands/Command.h"

FCommand::FCommand(TSharedPtr<FPiece> InPiece)
{
	check(InPiece.IsValid());
	Piece = InPiece;
}
