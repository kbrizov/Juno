// Christian Rizov's Juno.

#include "Commands/DeathCommand.h"

FDeathCommand::FDeathCommand(FPiece* InPiece)
	: FCommand(InPiece)
{
}

void FDeathCommand::Execute(const float DeltaTime)
{
	checkf(false, TEXT("Implement this!"));
}
