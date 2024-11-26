#pragma once

#include "CoreMinimal.h"
#include "Commands/Command.h"

class FAttackCommand final : public FCommand
{
public:
	FAttackCommand(TSharedPtr<FPiece> InAttacker, TSharedPtr<FPiece> InTarget);

	virtual void Execute(const float DeltaTime) override;

private:
	TSharedPtr<FPiece> Target;
};
