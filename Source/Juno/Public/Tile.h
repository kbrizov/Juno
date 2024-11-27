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
	FTile(const uint32 InRow = 0, const uint32 InColumn = 0, const float InWeight = 1.f, FPiece* InPiece = nullptr);

	uint32 GetRow() const;

	uint32 GetColumn() const;

	float GetWeight() const;
	void SetWeight(const float InWeight);

	FPiece* GetPiece() const;
	void SetPiece(FPiece* InPiece);

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
	float CachedWeight;
	FPiece* Piece;
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
	return Piece;
}

inline bool FTile::IsEmpty() const
{
	return Piece == nullptr;
}
