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

class JUNO_API FCommandData
{
public:
	explicit FCommandData(FPiece* InPiece, const ECommandType InType);

	const FPiece* GetPiece() const;
	ECommandType GetType() const;

private:
	FPiece* Piece = nullptr;
	ECommandType Type = ECommandType::None;
};

inline const FPiece* FCommandData::GetPiece() const
{
	return Piece;
}

inline ECommandType FCommandData::GetType() const
{
	return Type;
}
