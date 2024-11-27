#include "Commands/AttackCommand.h"

FAttackCommand::FAttackCommand(FPiece* InAttacker, FPiece* InTarget)
	: FCommand(InAttacker)
{
	check(InTarget);
	Target = InTarget;
}
