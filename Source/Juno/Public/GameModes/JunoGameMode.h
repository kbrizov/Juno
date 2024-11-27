// Christian Rizov's Juno.

#pragma once

#include "CoreMinimal.h"
#include "Simulation.h"
#include "Commands/Command.h"
#include "GameFramework/GameModeBase.h"
#include "JunoGameMode.generated.h"

class AGridVisual;
class APieceVisual;

UCLASS(Abstract)
class JUNO_API AJunoGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	/**
	 * This queue is the bridge between the "Simulation" and the "Visualization". It serves as input from the server.
	 */
	TQueue<TSharedPtr<FCommand>> Commands;

	TUniquePtr<FSimulation> Simulation;

	FTimerHandle FixedUpdateTimerHandle;

	UPROPERTY(EditDefaultsOnly)
	float TimeStepInSeconds = 0.1f; // 100 ms.

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
