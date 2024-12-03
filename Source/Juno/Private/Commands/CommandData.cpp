// Christian Rizov's Juno.

#include "Commands/CommandData.h"

FCommandData::FCommandData(FPiece* InPiece, const ECommandType InType)
	: Piece(InPiece), Type(InType)
{
	check(InPiece);
}

FCommandData::~FCommandData() = default;
