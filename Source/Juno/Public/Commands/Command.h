// Christian Rizov's Juno.

#pragma once

#include "CoreMinimal.h"

enum class ECommandType
{
	None,
	Move,
	Attack,
	Death
};

class FPiece;

class JUNO_API FCommand
{
public:
	explicit FCommand(FPiece* InPiece, const ECommandType InType);
	virtual ~FCommand() = default;

	const FPiece* GetPiece() const;
	ECommandType GetType() const;

private:
	FPiece* Piece = nullptr;
	ECommandType Type = ECommandType::None;
};

inline const FPiece* FCommand::GetPiece() const
{
	return Piece;
}

inline ECommandType FCommand::GetType() const
{
	return Type;
}
