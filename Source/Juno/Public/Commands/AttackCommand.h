#pragma once

#include "CoreMinimal.h"
#include "Commands/Command.h"

class FAttackCommand final : public FCommand
{
public:
	FAttackCommand(FPiece* InAttacker, FPiece* InTarget);

private:
	FPiece* Target;
};
