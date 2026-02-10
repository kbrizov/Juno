// Christian Rizov's Juno.

#include "Commands/AttackCommandData.h"

FAttackCommandData::FAttackCommandData(
    FPiece* InAttacker,
    FPiece* InTarget)
    : FCommandData(InAttacker, ECommandType::Attack)
    , Target(InTarget)
{
    check(InTarget);
}
