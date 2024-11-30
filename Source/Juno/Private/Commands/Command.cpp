#include "Commands/Command.h"

FCommand::FCommand(APieceVisual* InPiece)
	: Piece(InPiece), Status(ECommandStatus::Pending)
{
	check(InPiece)
}
