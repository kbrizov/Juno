// Christian Rizov's Juno.

#include "Simulation.h"
#include "Grid.h"
#include "Piece.h"
#include "Tile.h"
#include "Commands/AttackCommand.h"
#include "Commands/DeathCommand.h"
#include "Commands/MoveCommand.h"

FSimulation::FSimulation(TQueue<TSharedPtr<FCommand>>* InCommands, const uint32 GridRows, const uint32 GridColumns)
{
	check(InCommands);
	Commands = InCommands;

	Grid = MakeUnique<FGrid>(GridRows, GridColumns);
	constexpr int32 Seed = 1024; // Imagine this comes from a server.

	constexpr float PlayerHealth = 5.f;
	constexpr float PlayerDamage = 1.f;
	constexpr float PlayerMovementSpeed = 1.f;
	PlayerPiece = MakeUnique<FPiece>(ETeam::Player, PlayerHealth, PlayerDamage, PlayerMovementSpeed);
	FTile* PlayerPosition = GetRandomEmptyTile(Seed);
	PlayerPosition->SetPiece(PlayerPiece.Get());

	constexpr float EnemyHealth = 5.f;
	constexpr float EnemyDamage = 1.f;
	constexpr float EnemyMovementSpeed = 1.f;
	EnemyPiece = MakeUnique<FPiece>(ETeam::Enemy, EnemyHealth, EnemyDamage, EnemyMovementSpeed);
	FTile* EnemyPosition = GetRandomEmptyTile(Seed);
	EnemyPosition->SetPiece(EnemyPiece.Get());
}

FSimulation::~FSimulation()
{
	Commands = nullptr;
}

void FSimulation::FixedUpdate(const float DeltaTime)
{
	UpdatePlayer();
	UpdateEnemy();
}

void FSimulation::UpdatePlayer()
{
	if (PlayerPiece->IsDead())
	{
		return;
	}

	UpdatePiece(*PlayerPiece.Get(), *EnemyPiece.Get());
}

void FSimulation::UpdateEnemy()
{
	if (EnemyPiece->IsDead())
	{
		return;
	}

	UpdatePiece(*EnemyPiece.Get(), *PlayerPiece.Get());
}

void FSimulation::UpdatePiece(FPiece& InAttacker, FPiece& InTarget)
{
	if (InTarget.IsDead())
	{
		return;
	}

	TArray<const FTile*> PathToTarget = Grid->FindPath(InAttacker.GetPosition(), InTarget.GetPosition(), InAttacker.GetAttackRange());
	if (InAttacker.IsInAttackRange(PathToTarget))
	{
		InAttacker.Attack(&InTarget);
		Commands->Enqueue(MakeShared<FAttackCommand>(&InAttacker, &InTarget));

		if (InTarget.IsDead())
		{
			Commands->Enqueue(MakeShared<FDeathCommand>(&InTarget));
		}
	}
	else
	{
		FTile* NewPosition = const_cast<FTile*>(PathToTarget[0]); // TODO: Remove this const_cast.
		check(NewPosition);
		if (NewPosition->IsEmpty())
		{
			InAttacker.MoveTo(NewPosition);
			Commands->Enqueue(MakeShared<FMoveCommand>(&InAttacker, NewPosition));
		}
	}
}

FTile* FSimulation::GetRandomEmptyTile(const int32 InSeed) const
{
	FRandomStream RandomStream;
	RandomStream.Initialize(InSeed);

	const uint32 Rows = Grid->GetRows();
	const uint32 Columns = Grid->GetColumns();

	FTile* RandomTile = nullptr;

	do
	{
		const uint32 RandomRow = RandomStream.RandRange(0, Rows - 1);
		const uint32 RandomColumn = RandomStream.RandRange(0, Columns - 1);

		RandomTile = &(*Grid)[RandomRow][RandomColumn];
	}
	while (RandomTile && !RandomTile->IsEmpty()); // Repeat until an empty tile is found

	return RandomTile;
}
