// Christian Rizov's Juno.

#include "Commands/AttackCommand.h"
#include "PieceVisual.h"

FAttackCommand::FAttackCommand(
    APieceVisual* InAttacker,
    APieceVisual* InTarget)
    : FCommand(InAttacker)
    , Target(InTarget)
{
    check(InTarget);
}

void FAttackCommand::Execute(const float InDeltaTime)
{
    Piece->Attack(Target);
    Status = ECommandStatus::Completed;
}
