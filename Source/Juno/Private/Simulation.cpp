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

	// TODO: Randomize player values.
	constexpr float PlayerHealth = 5.f;
	constexpr float PlayerDamage = 1.f;
	constexpr float PlayerMovementSpeed = 1.f;
	PlayerPiece = MakeUnique<FPiece>(ETeam::Player, PlayerHealth, PlayerDamage, PlayerMovementSpeed);
	FTile& PlayerPosition = (*Grid)[0][0];
	PlayerPosition.SetPiece(PlayerPiece.Get());

	// TODO: Randomize enemy values.
	constexpr float EnemyHealth = 5.f;
	constexpr float EnemyDamage = 1.f;
	constexpr float EnemyMovementSpeed = 1.f;
	EnemyPiece = MakeUnique<FPiece>(ETeam::Enemy, EnemyHealth, EnemyDamage, EnemyMovementSpeed);
	FTile& EnemyPosition = (*Grid)[0][Grid->GetColumns() - 1];
	EnemyPosition.SetPiece(EnemyPiece.Get());
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
	if (PlayerPiece->IsInAttackRange(PathToTarget))
	{
		PlayerPiece->Attack(EnemyPiece.Get());
		Commands->Enqueue(MakeShared<FAttackCommand>(&InAttacker, &InTarget));

		if (InTarget.IsDead())
		{
			Commands->Enqueue(MakeShared<FDeathCommand>(&InTarget));
		}
	}
	else
	{
		const FTile* NewPosition = PathToTarget[0];
		check(NewPosition);
		if (NewPosition->IsEmpty())
		{
			PlayerPiece->MoveTo(NewPosition);
			Commands->Enqueue(MakeShared<FMoveCommand>(&InAttacker, const_cast<FTile*>(NewPosition))); // TODO: Remove this const_cast.
		}
	}
}
