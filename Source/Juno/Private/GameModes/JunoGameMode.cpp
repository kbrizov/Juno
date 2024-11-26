// Christian Rizov's Juno.

#include "GameModes/JunoGameMode.h"
#include "Simulation.h"

void AJunoGameMode::BeginPlay()
{
	Super::BeginPlay();
	Simulation = FSimulation(&Commands, FGrid(GridRows, GridColumns));
	GetWorldTimerManager().SetTimer(FixedUpdateTimerHandle, this, &AJunoGameMode::FixedUpdate, TimeStepInSeconds, true);
}

void AJunoGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorldTimerManager().ClearTimer(FixedUpdateTimerHandle);
	Super::EndPlay(EndPlayReason);
}

void AJunoGameMode::FixedUpdate()
{
	Simulation.FixedUpdate(TimeStepInSeconds);
}
