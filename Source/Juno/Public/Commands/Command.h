// Christian Rizov's Juno.

#pragma once

#include "CoreMinimal.h"

class APieceVisual;

class JUNO_API FCommand
{
public:
	explicit FCommand(APieceVisual* InPiece);
	virtual ~FCommand() = default;

	virtual void Execute(const uint32 InDeltaTime) = 0;

protected:
	APieceVisual* Piece;

	virtual bool IsExecuting() const;
};
