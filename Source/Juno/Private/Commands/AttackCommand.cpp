// Christian Rizov's Juno.

#include "Commands/AttackCommand.h"
#include "PieceVisual.h"

FAttackCommand::FAttackCommand(APieceVisual* InAttacker, APieceVisual* InTarget)
	: FCommand(InAttacker)
{
	check(InTarget);
	Target = InTarget;
}

void FAttackCommand::Execute(const uint32 InDeltaTime)
{
	Piece->Attack(Target);
}
