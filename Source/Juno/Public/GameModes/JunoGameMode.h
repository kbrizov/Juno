// Christian Rizov's Juno.

#pragma once

#include "CoreMinimal.h"
#include "Simulation.h"
#include "Commands/Command.h"
#include "GameFramework/GameModeBase.h"
#include "JunoGameMode.generated.h"

UCLASS(Abstract)
class JUNO_API AJunoGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	/**
	 * This queue is the bridge between the "Simulation" and the "Visualization".
	 * The "Simulation" writes to it.
	 * The "Visualization" reads from it.
	 */
	TQueue<TSharedPtr<FCommand>> Commands;

	TUniquePtr<FSimulation> Simulation;

	FTimerHandle FixedUpdateTimerHandle;

	UPROPERTY(EditDefaultsOnly)
	float TimeStepInSeconds = 0.1f; // 100 ms.

	UPROPERTY(EditDefaultsOnly)
	uint32 GridRows = 8;

	UPROPERTY(EditDefaultsOnly)
	uint32 GridColumns = 8;

	void FixedUpdate();
};
