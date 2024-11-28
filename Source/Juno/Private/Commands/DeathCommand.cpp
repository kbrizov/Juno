// Christian Rizov's Juno.

#include "Commands/DeathCommand.h"

FDeathCommand::FDeathCommand(APieceVisual* InPiece)
	: FCommand(InPiece)
{
}

void FDeathCommand::Execute(const uint32 InDeltaTime)
{
}
