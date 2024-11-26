// Christian Rizov's Juno.

#include "Tile.h"

FTile::FTile(const uint32 InRow, const uint32 InColumn, const float InWeight)
	: Row(InRow), Column(InColumn), Weight(InWeight)
{
}

bool FTile::operator<(const FTile& InOther) const
{
	return Weight < InOther.Weight;
}

bool FTile::operator>(const FTile& InOther) const
{
	return Weight > InOther.Weight;
}

bool FTile::operator==(const FTile& InOther) const
{
	const bool bEqualRows = Row == InOther.Row;
	const bool bEqualColumns = Column == InOther.Column;
	const bool bEqualWeight = FMath::IsNearlyEqual(Weight, InOther.Weight);
	const bool bAreEqual = bEqualRows && bEqualColumns && bEqualWeight;
	return bAreEqual;
}

bool FTile::operator!=(const FTile& InOther) const
{
	return !(*this == InOther);
}
