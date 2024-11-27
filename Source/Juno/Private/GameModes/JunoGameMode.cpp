// Christian Rizov's Juno.

#include "GameModes/JunoGameMode.h"
#include "GridVisual.h"
#include "Piece.h"
#include "PieceVisual.h"
#include "Simulation.h"
#include "Tile.h"
#include "TileVisual.h"

void AJunoGameMode::BeginPlay()
{
	Super::BeginPlay();
	Simulation = MakeUnique<FSimulation>(&Commands, GridRows, GridColumns);

	InitializeGridVisual(*Simulation->GetGrid());
	InitializePieceVisual(*Simulation->GetPlayerPiece(), PlayerVisualClass);
	InitializePieceVisual(*Simulation->GetEnemyPiece(), EnemyVisualClass);

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

void AJunoGameMode::InitializeGridVisual(const FGrid& InGrid)
{
	if (!ensure(GridVisualClass))
	{
		return;
	}

	GridVisual = GetWorld()->SpawnActor<AGridVisual>(GridVisualClass, FVector::Zero(), FRotator::ZeroRotator);
	check(GridVisual);
	GridVisual->Initialize(InGrid);
}

void AJunoGameMode::InitializePieceVisual(const FPiece& InPiece, const TSubclassOf<APieceVisual>& InPieceVisualClass)
{
	if (!ensure(InPieceVisualClass))
	{
		return;
	}

	const FVector2D Position = InPiece.GetPosition()->ToVector2D();
	const ATileVisual* TileVisual = (*GridVisual)[Position.X][Position.Y];
	check(TileVisual);

	const FVector ZOffset = FVector(0.f, 0.f,50.f);
	const FVector PieceVisualLocation = TileVisual->GetActorLocation() + ZOffset;
	const FRotator PieceVisualRotation = TileVisual->GetActorRotation();

	PlayerVisual = GetWorld()->SpawnActor<APieceVisual>(InPieceVisualClass, PieceVisualLocation, PieceVisualRotation);
}
