// Christian Rizov's Juno.

#include "Commands/CommandData.h"

FCommandData::FCommandData(FPiece* InPiece, const ECommandType InType)
{
	check(InPiece);
	Piece = InPiece;
	Type = InType;
}
