// Christian Rizov's Juno.

#include "GridVisual.h"
#include "Grid.h"
#include "TileVisual.h"

AGridVisual::AGridVisual()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AGridVisual::Initialize(const FGrid* InGrid)
{
	check(InGrid);

	UWorld* World = GetWorld();
	const uint32 Rows = InGrid->GetRows();
	const uint32 Columns = InGrid->GetColumns();

	for (uint32 Row = 0; Row < Rows; ++Row)
	{
		for (uint32 Column = 0; Column < Columns; ++Column)
		{
			const FVector GridLocation = GetActorLocation();

			// Alternating between light and dark tiles.
			TSubclassOf<ATileVisual> TileClass = ((Row + Column) % 2 != 0) ? LightTileClass : DarkTileClass;

			// Map the new tile's vector coordinates to their positions in a matrix (XY plane).
			constexpr uint32 Offset = 100;
			const float TileLocationX = GridLocation.X - (Row * Offset);
			const float TileLocationY = GridLocation.Y - (Column * Offset);
			const FVector TileLocation = FVector(TileLocationX, TileLocationY, 0.0f);
			const FRotator TileRotation = FRotator::ZeroRotator;

			ATileVisual* Tile = World->SpawnActor<ATileVisual>(TileClass, TileLocation, TileRotation);
			Tiles.Add(Tile);
		}
	}
}
