// Christian Rizov's Juno.

#pragma once

#include "CoreMinimal.h"

class FPiece;

class JUNO_API FCommand
{
public:
	explicit FCommand(TSharedPtr<FPiece> InPiece);
	virtual ~FCommand() = default;

	virtual void Execute(const float DeltaTime) = 0;

protected:
	FPiece* GetPiece();

private:
	TSharedPtr<FPiece> Piece;
};

inline FPiece* FCommand::GetPiece()
{
	return Piece.Get();
}
