#pragma once

#include "CoreMinimal.h"
#include "Commands/Command.h"

class FAttackCommand final : public FCommand
{
public:
	FAttackCommand(FPiece* InAttacker, FPiece* InTarget);

	virtual void Execute(const float DeltaTime) override;

private:
	FPiece* Target;
};
