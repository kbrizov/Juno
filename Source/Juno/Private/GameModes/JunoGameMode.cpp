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
	InitializePlayerVisual(*Simulation->GetPlayerPiece());
	InitializeEnemyVisual(*Simulation->GetEnemyPiece());

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

void AJunoGameMode::InitializePlayerVisual(const FPiece& InPlayerPiece)
{
	if (!ensure(PlayerVisualClass))
	{
		return;
	}

	const FVector2D Position = InPlayerPiece.GetPosition()->ToVector2D();
	const ATileVisual* TileVisual = (*GridVisual)[Position.X][Position.Y];
	check(TileVisual);

	const FVector ZOffset = FVector(0.f, 0.f,50.f);
	const FVector PlayerVisualLocation = TileVisual->GetActorLocation() + ZOffset;
	const FRotator PlayerVisualRotation = TileVisual->GetActorRotation();

	PlayerVisual = GetWorld()->SpawnActor<APieceVisual>(PlayerVisualClass, PlayerVisualLocation, PlayerVisualRotation);
}

void AJunoGameMode::InitializeEnemyVisual(const FPiece& InEnemyPiece)
{
	if (!ensure(EnemyVisualClass))
	{
		return;
	}

	const FVector2D Position = InEnemyPiece.GetPosition()->ToVector2D();
	const ATileVisual* TileVisual = (*GridVisual)[Position.X][Position.Y];
	check(TileVisual);

	const FVector ZOffset = FVector(0.f, 0.f,50.f);
	const FVector EnemyVisualLocation = TileVisual->GetActorLocation() + ZOffset;
	const FRotator EnemyVisualRotation = TileVisual->GetActorRotation();

	EnemyVisual = GetWorld()->SpawnActor<APieceVisual>(EnemyVisualClass, EnemyVisualLocation, EnemyVisualRotation);
}
