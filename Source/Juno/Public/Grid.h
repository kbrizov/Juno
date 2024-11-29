// Christian Rizov's Juno.

#pragma once

#include "CoreMinimal.h"
#include "Tile.h"

/**
 * Used to simulate/mock the grid on the server.
 */
class JUNO_API FGrid
{
public:
	explicit FGrid(const uint32 InRows = 8, const uint32 InColumns = 8);

	uint32 GetRows() const;
	uint32 GetColumns() const;

	TArray<FTile>& operator[](const uint32 Index);
	const TArray<FTile>& operator[](const uint32 Index) const;

	/**
	 * Finds a path in range (Start, End). Uses A*.
	 */
	TArray<const FTile*> FindPath(
		const FTile* InStart,
		const FTile* InEnd,
		const uint32 InAcceptanceRadius = 0,
		TFunction<float(const FTile&, const FTile&)> InDistanceHeuristic = &FGrid::CalculateEuclideanDistance) const;

private:
	uint32 Rows;
	uint32 Columns;
	TArray<TArray<FTile>> Tiles;

	TArray<const FTile*> GetTileNeighbors(const FTile& InTile) const;

	TArray<const FTile*> GetTileNeighbors(const uint32 InRow, const uint32 InColumn) const;

	bool IsTileInRange(const uint32 InTileRow, const uint32 InTileColumn) const;

	bool IsRowInRange(const uint32 InRow) const;

	bool IsColumnInRange(const uint32 InColumn) const;

	TMap<const FTile*, float> GetInitialCosts() const;

	TArray<const FTile*> GetPathTo(const FTile& InEnd, const TMap<const FTile*, const FTile*>& InVisited) const;

	static float CalculateManhattanDistance(const FTile& A, const FTile& B);

	static float CalculateEuclideanDistance(const FTile& A, const FTile& B);
};

inline uint32 FGrid::GetRows() const
{
	return Rows;
}

inline uint32 FGrid::GetColumns() const
{
	return Columns;
}

inline bool FGrid::IsTileInRange(const uint32 InTileRow, const uint32 InTileColumn) const
{
	return IsRowInRange(InTileRow) && IsColumnInRange(InTileColumn);
}

inline bool FGrid::IsRowInRange(const uint32 InRow) const
{
	return InRow < Rows;
}

inline bool FGrid::IsColumnInRange(const uint32 InColumn) const
{
	return InColumn < Columns;
}
