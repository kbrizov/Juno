#include "Commands/AttackCommand.h"

FAttackCommand::FAttackCommand(FPiece* InAttacker, FPiece* InTarget)
	: FCommand(InAttacker)
{
	check(InTarget);
	Target = InTarget;
}

void FAttackCommand::Execute(const float DeltaTime)
{
	checkf(false, TEXT("Implement this!"));
}
