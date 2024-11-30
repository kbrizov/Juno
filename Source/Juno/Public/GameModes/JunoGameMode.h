// Christian Rizov's Juno.

#pragma once

#include "CoreMinimal.h"
#include "Simulation.h"
#include "Visualization.h"
#include "Commands/CommandData.h"
#include "GameFramework/GameModeBase.h"
#include "JunoGameMode.generated.h"

class FTile;
class FGrid;
class FPiece;
class ATileVisual;
class AGridVisual;
class APieceVisual;

UCLASS(Abstract)
class JUNO_API AJunoGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AJunoGameMode();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	/**
	 * This queue is the bridge between the "Simulation" and the "Visualization". It serves as input from the server.
	 */
	TQueue<TUniquePtr<FCommandData>> Commands;

	TUniquePtr<FSimulation> Simulation;

	TUniquePtr<FVisualization> Visualization;

	FTimerHandle FixedUpdateTimerHandle;

	UPROPERTY(EditDefaultsOnly)
	float TimeStepInSeconds = 0.1f; // 100 ms.

	UPROPERTY(EditDefaultsOnly)
	int32 RandomSeed = 1024;

	UPROPERTY(EditDefaultsOnly, Category="Grid")
	uint32 GridRows = 8;

	UPROPERTY(EditDefaultsOnly, Category="Grid")
	uint32 GridColumns = 8;

	UPROPERTY(EditDefaultsOnly, Category="Grid")
	TSubclassOf<AGridVisual> GridVisualClass;

	UPROPERTY()
	TObjectPtr<AGridVisual> GridVisual;

	UPROPERTY(EditDefaultsOnly, Category="Pieces")
	TSubclassOf<APieceVisual> PlayerVisualClass;

	UPROPERTY()
	TObjectPtr<APieceVisual> PlayerVisual;

	UPROPERTY(EditDefaultsOnly, Category="Pieces")
	TSubclassOf<APieceVisual> EnemyVisualClass;

	UPROPERTY()
	TObjectPtr<APieceVisual> EnemyVisual;

	void FixedUpdate();

	void InitializeGridVisual(const FGrid& InGrid);

	void InitializePlayerVisual(const FPiece& InPlayerPiece);

	void InitializeEnemyVisual(const FPiece& InEnemyPiece);
};
