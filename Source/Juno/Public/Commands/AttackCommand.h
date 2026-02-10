// Christian Rizov's Juno.

#pragma once

#include "CoreMinimal.h"
#include "Command.h"

class JUNO_API FAttackCommand final : public FCommand
{
public:
    explicit FAttackCommand(
        APieceVisual* InAttacker,
        APieceVisual* InTarget);

    virtual ~FAttackCommand() = default;

    virtual void Execute(float InDeltaTime) override;

private:
    APieceVisual* Target;
};
