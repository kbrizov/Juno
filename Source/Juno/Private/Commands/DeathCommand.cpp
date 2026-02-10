// Christian Rizov's Juno.

#include "Commands/DeathCommand.h"
#include "PieceVisual.h"

FDeathCommand::FDeathCommand(APieceVisual* InPiece)
    : FCommand(InPiece)
{
}

void FDeathCommand::Execute(const float InDeltaTime)
{
    Piece->Die();
    Status = ECommandStatus::Completed;
}
