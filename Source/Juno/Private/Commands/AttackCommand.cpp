#include "Commands/AttackCommand.h"

FAttackCommand::FAttackCommand(TSharedPtr<FPiece> InAttacker, TSharedPtr<FPiece> InTarget)
	: FCommand(InAttacker), Target(InTarget)
{
}

void FAttackCommand::Execute(const float DeltaTime)
{
	checkf(false, TEXT("Implement this!"));
}
