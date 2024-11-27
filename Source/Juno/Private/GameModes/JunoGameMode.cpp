// Christian Rizov's Juno.

#include "GameModes/JunoGameMode.h"
#include "GridVisual.h"
#include "Piece.h"
#include "PieceVisual.h"
#include "Simulation.h"
#include "Tile.h"
#include "TileVisual.h"
#include "Commands/AttackCommand.h"
#include "Commands/DeathCommand.h"
#include "Commands/MoveCommand.h"

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

	TSharedPtr<FCommand> Command = nullptr;
	Commands.Dequeue(Command);
}

void AJunoGameMode::ExecuteCommand(const FCommand* InCommand)
{
	check(InCommand);

	/**
	 * I'm forced to do this because I failed to predict that I will need RTTI for the commands.
	 * The initial idea was for them to have a virtual Execute method. However, now they are just a ledger.
	 * FCommand is not derived from UOBject so I cant use Cast<T> and dynamic_cast is disabled.
	 * Ideally I'd refactor the commands to be UObjects, but it's not a trivial thing to do at this point and I don't have time.
	 */

	const ECommandType CommandType = InCommand->GetType();

	if (CommandType == ECommandType::Move)
	{
		const FMoveCommand* MoveCommand = static_cast<const FMoveCommand*>(InCommand);
		const FPiece* Piece = MoveCommand->GetPiece();
		const FTile* NewPosition = MoveCommand->GetNewPosition();

		if (Piece->GetTeam() == ETeam::Player)
		{
			// TODO: Move PlayerVisual to NewPosition.
		}
		else
		{
			// TODO: Move EnemyVisual to NewPosition.
		}
	}
	else if (CommandType == ECommandType::Attack)
	{
		const FAttackCommand* AttackCommand = static_cast<const FAttackCommand*>(InCommand);

		// TODO: Implement visual attack.
	}
	else if (CommandType == ECommandType::Death)
	{
		const FDeathCommand* DeathCommand = static_cast<const FDeathCommand*>(InCommand);

		// TODO: Implement visual death.
	}
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
