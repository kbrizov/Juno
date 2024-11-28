#pragma once

#include "CoreMinimal.h"
#include "Commands/Command.h"

class FAttackCommand final : public FCommand
{
public:
	FAttackCommand(FPiece* InAttacker, FPiece* InTarget);

	FPiece* GetTarget() const;

private:
	FPiece* Target;
};

inline FPiece* FAttackCommand::GetTarget() const
{
	return Target;
}
