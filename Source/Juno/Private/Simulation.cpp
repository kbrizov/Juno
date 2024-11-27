// Christian Rizov's Juno.

#include "Simulation.h"
#include "Grid.h"
#include "Piece.h"
#include "Tile.h"

FSimulation::FSimulation(TQueue<FCommand*>* InCommands, const uint32 GridRows, const uint32 GridColumns)
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
	UpdatePiece(*PlayerPiece.Get(), *EnemyPiece.Get());
}

void FSimulation::UpdateEnemy()
{
	UpdatePiece(*EnemyPiece.Get(), *PlayerPiece.Get());
}

void FSimulation::UpdatePiece(const FPiece& InAttacker, const FPiece& InTarget)
{
	TArray<const FTile*> PathToTarget = Grid->FindPath(InAttacker.GetPosition(), InTarget.GetPosition());

	if (PathToTarget.IsEmpty())
	{
		return;
	}

	if (PlayerPiece->IsInAttackRange(PathToTarget))
	{
		PlayerPiece->Attack(EnemyPiece.Get());
	}
	else
	{
		const FTile* NewPosition = PathToTarget[0];
		PlayerPiece->MoveTo(NewPosition);
	}
}
