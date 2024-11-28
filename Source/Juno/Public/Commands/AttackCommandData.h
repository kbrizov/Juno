#pragma once

#include "CoreMinimal.h"
#include "Commands/CommandData.h"

class FAttackCommandData final : public FCommandData
{
public:
	FAttackCommandData(FPiece* InAttacker, FPiece* InTarget);

	FPiece* GetTarget() const;

private:
	FPiece* Target;
};

inline FPiece* FAttackCommandData::GetTarget() const
{
	return Target;
}
