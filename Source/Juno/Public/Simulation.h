// Christian Rizov's Juno.

#pragma once

#include "CoreMinimal.h"
#include "Grid.h"
#include "Piece.h"
#include "Commands/Command.h"

/**
 * This class mocks a server.
 */
class JUNO_API FSimulation
{
public:
	FSimulation(TQueue<FCommand*>* InCommands, const FGrid& InGrid);
	~FSimulation();

	void FixedUpdate(const float DeltaTime);

private:
	TQueue<FCommand*>* Commands = nullptr;

	FGrid Grid;
	FPiece PlayerPiece;
	FPiece EnemyPiece;
};
