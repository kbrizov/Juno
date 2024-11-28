// Christian Rizov's Juno.

#pragma once

#include "CoreMinimal.h"
#include "CommandData.h"

class JUNO_API FDeathCommandData : public FCommandData
{
public:
	explicit FDeathCommandData(FPiece* InPiece);
};
