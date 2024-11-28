// Christian Rizov's Juno.

#pragma once

#include "CoreMinimal.h"
#include "PieceVisual.h"
#include "Commands/MoveCommandData.h"

class AGridVisual;
class ATileVisual;
class FTile;
class APieceVisual;
class FPiece;
class FCommandData;
class FAttackCommand;
class FMoveCommand;
class FDeathCommand;

/**
 * This class mocks a client.
 */
class JUNO_API FVisualization
{
public:
	explicit FVisualization(TQueue<TSharedPtr<FCommandData>>* InCommandsData, AGridVisual* InGrid, APieceVisual* InPlayerPiece, APieceVisual* InEnemyPiece);
	~FVisualization();

	void FixedUpdate(const float InDeltaTime);

private:
	TQueue<TSharedPtr<FCommandData>>* CommandsData = nullptr;

	TWeakObjectPtr<AGridVisual> Grid;
	TWeakObjectPtr<APieceVisual> PlayerPiece;
	TWeakObjectPtr<APieceVisual> EnemyPiece;

	TUniquePtr<FMoveCommand> MakeMoveCommand(const FCommandData& InData) const;
	TUniquePtr<FAttackCommand> MakeAttackCommand(const FCommandData& InData) const;
	TUniquePtr<FDeathCommand> MakeDeathCommand(const FCommandData& InData) const;

	APieceVisual* GetPieceVisualFrom(const FPiece* InPiece) const;

	ATileVisual* GetTileVisualFrom(const FTile* InTile) const;
};
