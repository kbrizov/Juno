#include "Commands/AttackCommandData.h"

FAttackCommandData::FAttackCommandData(FPiece* InAttacker, FPiece* InTarget)
	: FCommandData(InAttacker, ECommandType::Attack)
{
	check(InTarget);
	Target = InTarget;
}
