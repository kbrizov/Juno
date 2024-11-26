// Christian Rizov's Juno.

#pragma once

#include "CoreMinimal.h"

class FPiece;

/**
 * Used to simulate/mock tiles on the server.
 */
class JUNO_API FTile
{
public:
	FTile(const uint32 InRow, const uint32 InColumn, const float InWeight = 1.f, TSharedPtr<FPiece> InPiece = nullptr);

	uint32 GetRow() const;

	uint32 GetColumn() const;

	float GetWeight() const;
	void SetWeight(const float InWeight);

	FPiece* GetPiece() const;
	void SetPiece(TSharedPtr<FPiece> InPiece);

	void Clear();
	FVector2D ToVector2D() const;

	bool IsEmpty() const;

	bool operator<(const FTile& InOther) const;
	bool operator>(const FTile& InOther) const;
	bool operator==(const FTile& InOther) const;
	bool operator!=(const FTile& InOther) const;

private:
	uint32 Row;
	uint32 Column;
	float Weight;
	TSharedPtr<FPiece> Piece;
};

inline uint32 FTile::GetRow() const
{
	return Row;
}

inline uint32 FTile::GetColumn() const
{
	return Column;
}

inline float FTile::GetWeight() const
{
	return Weight;
}

inline void FTile::SetWeight(const float InWeight)
{
	Weight = InWeight;
}

inline FPiece* FTile::GetPiece() const
{
	return Piece.Get();
}

inline void FTile::Clear()
{
	Piece.Reset();
}

inline bool FTile::IsEmpty() const
{
	return Piece.Get() == nullptr;
}
