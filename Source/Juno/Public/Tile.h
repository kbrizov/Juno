// Christian Rizov's Juno.

#pragma once

#include "CoreMinimal.h"

class JUNO_API FTile
{
public:
	FTile(const uint32 InRow, const uint32 InColumn, const float InWeight);
	~FTile() = default;

	uint32 GetRow() const;

	uint32 GetColumn() const;

	float GetWeight() const;
	void SetWeight(const float InWeight);

	bool operator<(const FTile& InOther) const;
	bool operator>(const FTile& InOther) const;
	bool operator==(const FTile& InOther) const;
	bool operator!=(const FTile& InOther) const;

private:
	uint32 Row;
	uint32 Column;
	float Weight;
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
