// Christian Rizov's Juno.

#include "GridVisual.h"
#include "Grid.h"
#include "TileVisual.h"
#include "Tile.h"

AGridVisual::AGridVisual()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AGridVisual::Initialize(const FGrid& InGrid)
{
	UWorld* World = GetWorld();
	const uint32 Rows = InGrid.GetRows();
	const uint32 Columns = InGrid.GetColumns();

	Tiles.SetNum(Rows);
	for (uint32 Row = 0; Row < Rows; ++Row)
	{
		Tiles[Row].SetNum(Columns);
		for (uint32 Column = 0; Column < Columns; ++Column)
		{
			const FTile& Tile = InGrid[Row][Column];
			ATileVisual* TileVisual = SpawnTileVisual(*World, Tile);
			check(TileVisual);
			Tiles[Row][Column] = TileVisual;
		}
	}
}

TArray<TObjectPtr<ATileVisual>>& AGridVisual::operator[](const uint32 Index)
{
	// Reusing const TArray<TObjectPtr<ATileVisual>>& AGridVisual::operator[](const uint32 Index) const
	return const_cast<TArray<TObjectPtr<ATileVisual>>&>(static_cast<const AGridVisual&>(*this)[Index]);
}

const TArray<TObjectPtr<ATileVisual>>& AGridVisual::operator[](const uint32 Index) const
{
	return Tiles[Index];
}

ATileVisual* AGridVisual::SpawnTileVisual(UWorld& InWorld, const FTile& InTile)
{
	const FVector GridLocation = GetActorLocation();
	const uint32 Row = InTile.GetRow();
	const uint32 Column = InTile.GetColumn();

	// Alternating between light and dark tiles.
	const TSubclassOf<ATileVisual> TileClass = ((Row + Column) % 2 != 0) ? LightTileClass : DarkTileClass;

	// Map the new tile's vector coordinates to their positions in a matrix (XY plane).
	constexpr uint32 Offset = 100;
	const float TileLocationX = GridLocation.X - (Row * Offset);
	const float TileLocationY = GridLocation.Y + (Column * Offset);
	const FVector TileLocation = FVector(TileLocationX, TileLocationY, 0.0f);
	const FRotator TileRotation = FRotator::ZeroRotator;

	ATileVisual* Tile = InWorld.SpawnActor<ATileVisual>(TileClass, TileLocation, TileRotation);
	return Tile;
}
