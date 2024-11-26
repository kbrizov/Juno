// Christian Rizov's Juno.

#include "Grid.h"
#include "Tile.h"

static TArray<FVector2D> Directions =
{
	FVector2D(1, 0),
	FVector2D(1, 1),
	FVector2D(0, 1),
	FVector2D(-1, 1),
	FVector2D(-1, 0),
	FVector2D(-1, -1),
	FVector2D(0, -1),
	FVector2D(1, -1)
};

FGrid::FGrid(const uint32 InRows, const uint32 InColumns)
	: Rows(InRows), Columns(InColumns)
{
	Tiles = TArray<TArray<FTile>>();
	Tiles.Reserve(Rows);

	for (uint32 Row = 0; Row < Rows; ++Row)
	{
		Tiles[Row] = TArray<FTile>();
		Tiles[Row].Reserve(Columns);

		for (uint32 Column = 0; Column < Columns; ++Column)
		{
			Tiles[Row][Column] = FTile(Row, Column);
		}
	}
}

TArray<FTile>& FGrid::operator[](const uint32 Index)
{
	// A trick I learned from Scott Meyers. The idea is to avoid code duplication.
	// 1. Treat *this as a const in order to call the const version of operator[].
	// 2. Cast away the constness of the result with const_cast.
	return const_cast<TArray<FTile>&>(static_cast<const FGrid&>(*this)[Index]);
}

const TArray<FTile>& FGrid::operator[](const uint32 Index) const
{
	return Tiles[Index];
}

TArray<const FTile*> FGrid::GetTileNeighbors(const FTile& InTile) const
{
	return GetTileNeighbors(InTile.GetRow(), InTile.GetColumn());
}

TArray<const FTile*> FGrid::GetTileNeighbors(const uint32 InRow, const uint32 InColumn) const
{
	check(IsRowInRange(InRow));
	check(IsColumnInRange(InColumn));

	TArray<const FTile*> Neighbors;
	Neighbors.Reserve(Directions.Num());

	const FVector2D Position = (*this)[InRow][InColumn].ToVector2D();

	for (const auto& Direction : Directions)
	{
		const FVector2D CurrentPosition = Position + Direction;
		if (IsTileInRange(CurrentPosition.X, CurrentPosition.Y))
		{
			Neighbors.Add(&((*this)[InRow][InColumn]));
		}
	}

	return Neighbors;
}
