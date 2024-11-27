#include "Commands/AttackCommand.h"

FAttackCommand::FAttackCommand(FPiece* InAttacker, FPiece* InTarget)
	: FCommand(InAttacker, ECommandType::Attack)
{
	check(InTarget);
	Target = InTarget;
}
