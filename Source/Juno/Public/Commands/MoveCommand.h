// Christian Rizov's Juno.

#pragma once

#include "CoreMinimal.h"
#include "Command.h"

class ATileVisual;

class JUNO_API FMoveCommand final : public FCommand
{
public:
    explicit FMoveCommand(
        APieceVisual* InPiece,
        ATileVisual* InNewTile,
        const float InDuration,
        const FVector& InOffset = FVector::Zero());

    virtual ~FMoveCommand() = default;

    virtual void Execute(float InDeltaTime) override;

private:
    ATileVisual* NewTile;
    const float Duration;
    const FVector Offset;

    FVector StartLocation;
    FVector EndLocation;
    float ElapsedTime;
};
