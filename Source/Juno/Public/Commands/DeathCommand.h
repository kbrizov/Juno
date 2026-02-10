// Christian Rizov's Juno.

#pragma once

#include "CoreMinimal.h"
#include "Command.h"

class JUNO_API FDeathCommand final : public FCommand
{
public:
    explicit FDeathCommand(APieceVisual* InPiece);
    virtual ~FDeathCommand() = default;

    virtual void Execute(float InDeltaTime) override;
};
