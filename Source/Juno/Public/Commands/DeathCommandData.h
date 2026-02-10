// Christian Rizov's Juno.

#pragma once

#include "CoreMinimal.h"
#include "CommandData.h"

class JUNO_API FDeathCommandData final : public FCommandData
{
public:
    explicit FDeathCommandData(FPiece* InPiece);
};
