// Christian Rizov's Juno.

#include "Tile.h"
#include "Piece.h"

FTile::FTile(
    const uint32 InRow,
    const uint32 InColumn,
    const float InWeight,
    FPiece* InPiece)
    : Row(InRow)
    , Column(InColumn)
    , Weight(InWeight)
    , CachedWeight(InWeight)
    , Piece(InPiece)
{
}

void FTile::SetPiece(FPiece* InPiece)
{
    check(InPiece != nullptr);
    check(IsEmpty());

    Piece = InPiece;
    Piece->SetPosition(this);

    Weight = TNumericLimits<float>::Max();
}

void FTile::Clear()
{
    Piece = nullptr;
    Weight = CachedWeight;
}

FVector2D FTile::ToVector2D() const
{
    return FVector2D(Row, Column);
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
    const bool bEqualPieces = Piece == InOther.Piece;
    const bool bAreEqual = bEqualRows && bEqualColumns && bEqualPieces && bEqualWeight;
    return bAreEqual;
}

bool FTile::operator!=(const FTile& InOther) const
{
    return !(*this == InOther);
}
