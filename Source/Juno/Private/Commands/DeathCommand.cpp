// Christian Rizov's Juno.

#include "Commands/DeathCommand.h"

FDeathCommand::FDeathCommand(FPiece* InPiece)
	: FCommand(InPiece, ECommandType::Death)
{
}
