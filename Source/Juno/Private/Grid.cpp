// Christian Rizov's Juno.

#include "Grid.h"
#include "Tile.h"

FGrid::FGrid(const uint32 InRows, const uint32 InColumns)
	: Rows(InRows), Columns(InColumns)
{
	Tiles = TArray<TArray<FTile>>();
	Tiles.SetNum(Rows);

	for (uint32 Row = 0; Row < Rows; ++Row)
	{
		Tiles[Row] = TArray<FTile>();
		Tiles[Row].SetNum(Columns);

		for (uint32 Column = 0; Column < Columns; ++Column)
		{
			Tiles[Row][Column] = FTile(Row, Column, 1.f);
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

TArray<const FTile*> FGrid::FindPath(
	const FTile* InStart,
	const FTile* InEnd,
	const uint32 InAcceptanceRadius,
	TFunction<float(const FTile&, const FTile&)> InDistanceHeuristic) const
{
	check(InStart);
	check(InEnd);

	auto AStarOutput = CalculatePathUsingAStar(InStart, InEnd, InDistanceHeuristic);
	auto Path = BacktrackFromEndToStart(*InEnd, AStarOutput);

	if (!Path.IsEmpty())
	{
		Path.RemoveAt(0, 1, true); // Exclude the start.

		for (uint32 i = 0; i < InAcceptanceRadius; ++i) // Exclude N elements from the end.
		{
			Path.Pop();
		}
	}

	return Path;
}

TArray<const FTile*> FGrid::GetTileNeighbors(const FTile& InTile) const
{
	return GetTileNeighbors(InTile.GetRow(), InTile.GetColumn());
}

TArray<const FTile*> FGrid::GetTileNeighbors(const uint32 InRow, const uint32 InColumn) const
{
	check(IsRowInRange(InRow));
	check(IsColumnInRange(InColumn));

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

	TArray<const FTile*> Neighbors;
	Neighbors.Reserve(Directions.Num());

	const FVector2D Position = Tiles[InRow][InColumn].ToVector2D();

	for (const auto& Direction : Directions)
	{
		const FVector2D NeighborPosition = Position + Direction;
		if (IsTileInRange(NeighborPosition.X, NeighborPosition.Y))
		{
			const FTile* Neighbor = &Tiles[NeighborPosition.X][NeighborPosition.Y];
			Neighbors.Add(Neighbor);
		}
	}

	return Neighbors;
}

TMap<const FTile*, const FTile*> FGrid::CalculatePathUsingAStar(const FTile* InStart, const FTile* InEnd, TFunction<float(const FTile&, const FTile&)> InDistanceHeuristic) const
{
	check(InStart);
	check(InEnd);

	auto Costs = CalculateInitialCosts();
	Costs[InStart] = 0.0f;

	auto HeuristicComparer = [&](const FTile& Lhs, const FTile& Rhs) -> bool
	{
		const float LhsPriority = Costs[&Lhs] + InDistanceHeuristic(Lhs, *InEnd);
		const float RhsPriority = Costs[&Rhs] + InDistanceHeuristic(Rhs, *InEnd);

		return LhsPriority < RhsPriority;
	};

	TArray<const FTile*> Frontier;
	Frontier.HeapPush(InStart, HeuristicComparer);

	auto Visited  = TMap<const FTile*, const FTile*>();
	Visited.Add(InStart, nullptr);

	while (!Frontier.IsEmpty())
	{
		const FTile* Current = nullptr;
		Frontier.HeapPop(Current, HeuristicComparer);

		if (Current == InEnd)
		{
			break;
		}

		auto Neighbors = GetTileNeighbors(*Current);

		for (const auto& Tile : Neighbors)
		{
			const float CurrentCost = Costs[Tile];
			const float NewCost = Costs[Current] + Tile->GetWeight();

			const bool IsVisited = Visited.Contains(Tile);

			if (NewCost < CurrentCost)
			{
				Costs[Tile] = NewCost;

				// A cheaper path is found, so the tile predecessor must be replaced with the current tile.
				if (IsVisited)
				{
					Visited[Tile] = Current;
				}
			}

			if (!IsVisited)
			{
				Frontier.HeapPush(Tile, HeuristicComparer);
				Visited.Add(Tile, Current);
			}
		}
	}

	return Visited;
}

TMap<const FTile*, float> FGrid::CalculateInitialCosts() const
{
	TMap<const FTile*, float> Costs;

	for (uint32 Row = 0; Row < GetRows(); ++Row)
	{
		for (uint32 Column = 0; Column < GetColumns(); ++Column)
		{
			const FTile* Tile = &(*this)[Row][Column];
			constexpr float Cost = TNumericLimits<float>::Max();

			Costs.Add(Tile, Cost);
		}
	}

	return Costs;
}

TArray<const FTile*> FGrid::BacktrackFromEndToStart(const FTile& InEnd, const TMap<const FTile*, const FTile*>& InAStarOutput) const
{
	if (InAStarOutput.IsEmpty() || !InAStarOutput.Contains(&InEnd))
	{
		ensure(false);
		return TArray<const FTile*>();
	}

	TArray<const FTile*> Path;

	const FTile* Current = &InEnd;
	while (Current != nullptr)
	{
		Path.Add(Current);
		Current = InAStarOutput.FindRef(Current);
	}

	Algo::Reverse(Path);

	return Path;
}

float FGrid::CalculateManhattanDistance(const FTile& A, const FTile& B)
{
	const float ARow = static_cast<float>(A.GetRow());
	const float AColumn = static_cast<float>(A.GetColumn());

	const float BRow = static_cast<float>(B.GetRow());
	const float BColumn = static_cast<float>(B.GetColumn());

	const float ManhattanDistance = FMath::Abs(ARow - BRow) + FMath::Abs(AColumn - BColumn);
	return ManhattanDistance;
}

float FGrid::CalculateEuclideanDistance(const FTile& A, const FTile& B)
{
	const float EuclideanDistance = FVector2D::Distance(A.ToVector2D(), B.ToVector2D());
	return EuclideanDistance;
}
