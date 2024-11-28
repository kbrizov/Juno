// Christian Rizov's Juno.

#pragma once

#include "CoreMinimal.h"
#include "PieceVisual.h"

class AGridVisual;
class FGrid;
class ATileVisual;
class FTile;
class APieceVisual;
class FPiece;
class FCommandData;

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

	void ExecuteCommand(const FCommandData* InCommand);

	APieceVisual* GetPieceVisualFrom(const FPiece* InPiece) const;

	ATileVisual* GetTileVisualFrom(const FTile* InTile) const;
};
