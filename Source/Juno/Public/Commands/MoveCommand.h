// Christian Rizov's Juno.

#pragma once

#include "CoreMinimal.h"
#include "Command.h"

class ATileVisual;

class JUNO_API FMoveCommand final : public FCommand
{
public:
	explicit FMoveCommand(APieceVisual* InPiece, ATileVisual* InNewTile, const FVector& InOffset = FVector::Zero());
	virtual ~FMoveCommand() = default;

	virtual void Execute(const uint32 InDeltaTime) override;

private:
	ATileVisual* NewTile;
	FVector Offset;
};
