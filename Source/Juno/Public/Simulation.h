// Christian Rizov's Juno.

#pragma once

#include "CoreMinimal.h"

class FCommand;
class FGrid;
class FPiece;

/**
 * This class mocks a server.
 */
class JUNO_API FSimulation
{
public:
	FSimulation(TQueue<FCommand*>* InCommands, const uint32 GridRows, const uint32 GridColumns);
	~FSimulation();

	void FixedUpdate(const float DeltaTime);

	const FGrid* GetGrid() const;
	const FPiece* GetPlayerPiece() const;
	const FPiece* GetEnemyPiece() const;

private:
	TQueue<FCommand*>* Commands = nullptr;

	TUniquePtr<FGrid> Grid;
	TUniquePtr<FPiece> PlayerPiece;
	TUniquePtr<FPiece> EnemyPiece;

	void UpdatePlayer();
	void UpdateEnemy();
	void UpdatePiece(const FPiece& InAttacker, const FPiece& InTarget);
};

inline const FGrid* FSimulation::GetGrid() const
{
	return Grid.Get();
}

inline const FPiece* FSimulation::GetPlayerPiece() const
{
	return PlayerPiece.Get();
}

inline const FPiece* FSimulation::GetEnemyPiece() const
{
	return EnemyPiece.Get();
}
