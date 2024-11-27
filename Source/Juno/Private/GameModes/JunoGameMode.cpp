// Christian Rizov's Juno.

#include "GameModes/JunoGameMode.h"
#include "GridVisual.h"
#include "Simulation.h"
#include "Kismet/GameplayStatics.h"

void AJunoGameMode::BeginPlay()
{
	Super::BeginPlay();
	Simulation = MakeUnique<FSimulation>(&Commands, GridRows, GridColumns);

	InitializeGrid(Simulation->GetGrid());

	GetWorldTimerManager().SetTimer(FixedUpdateTimerHandle, this, &AJunoGameMode::FixedUpdate, TimeStepInSeconds, true);
}

void AJunoGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorldTimerManager().ClearTimer(FixedUpdateTimerHandle);
	Super::EndPlay(EndPlayReason);
}

void AJunoGameMode::FixedUpdate()
{
	Simulation->FixedUpdate(TimeStepInSeconds);
}

void AJunoGameMode::InitializeGrid(const FGrid* InGrid)
{
	check(InGrid);

	if (!ensure(GridClass))
	{
		return;
	}

	AGridVisual* GridVisual = Cast<AGridVisual>(UGameplayStatics::GetActorOfClass(GetWorld(), GridClass));
	if (!ensure(GridVisual))
	{
		return;
	}

	GridVisual->Initialize(InGrid);
}
