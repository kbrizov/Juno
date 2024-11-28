// Christian Rizov's Juno.

#pragma once

#include "CoreMinimal.h"
#include "Command.h"

class ATileVisual;

class JUNO_API FMoveCommand final : public FCommand
{
public:
	explicit FMoveCommand(APieceVisual* InPiece, ATileVisual* InNewTile);
	virtual ~FMoveCommand() = default;

	virtual void Execute(const uint32 InDeltaTime) override;

private:
	ATileVisual* NewTile;
};
