// Christian Rizov's Juno.

#pragma once

#include "CoreMinimal.h"
#include "PieceVisual.h"

class AGridVisual;
class ATileVisual;
class APieceVisual;
class FTile;
class FPiece;
class FCommand;
class FAttackCommand;
class FMoveCommand;
class FDeathCommand;
class FCommandData;

/**
 * This class mocks a client.
 */
class JUNO_API FVisualization
{
public:
	explicit FVisualization(TQueue<TUniquePtr<FCommandData>>* InCommandsData, AGridVisual* InGrid, APieceVisual* InPlayerPiece, APieceVisual* InEnemyPiece);
	~FVisualization();

	void Update(const float InDeltaTime);

private:
	TQueue<TUniquePtr<FCommandData>>* CommandsData = nullptr;
	TUniquePtr<FCommand> CurrentCommand = nullptr;

	TWeakObjectPtr<AGridVisual> Grid;
	TWeakObjectPtr<APieceVisual> PlayerPiece;
	TWeakObjectPtr<APieceVisual> EnemyPiece;

	TUniquePtr<FMoveCommand> MakeMoveCommand(const FCommandData& InData) const;
	TUniquePtr<FAttackCommand> MakeAttackCommand(const FCommandData& InData) const;
	TUniquePtr<FDeathCommand> MakeDeathCommand(const FCommandData& InData) const;

	APieceVisual* GetPieceVisualFrom(const FPiece* InPiece) const;

	ATileVisual* GetTileVisualFrom(const FTile* InTile) const;

	TUniquePtr<FCommand> GetNextCommand() const;
};
