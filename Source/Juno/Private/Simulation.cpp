// Christian Rizov's Juno.

#include "Simulation.h"
#include "Grid.h"
#include "Piece.h"
#include "Tile.h"
#include "Commands/AttackCommandData.h"
#include "Commands/DeathCommandData.h"
#include "Commands/MoveCommandData.h"

FSimulation::FSimulation(TQueue<TUniquePtr<FCommandData>>* InCommandsData, const uint32 InGridRows, const uint32 InGridColumns, const int32 InRandomSeed)
	: RandomSeed(InRandomSeed)
{
	check(InCommandsData);
	CommandsData = InCommandsData;

	Grid = MakeUnique<FGrid>(InGridRows, InGridColumns);
	constexpr float PlayerHealth = 5.f;
	constexpr float PlayerDamage = 1.f;
	constexpr float PlayerMovementSpeed = 1.f;
	PlayerPiece = MakeUnique<FPiece>(ETeam::Player, PlayerHealth, PlayerDamage, PlayerMovementSpeed);
	FTile* PlayerPosition = GetRandomEmptyTile(InRandomSeed);
	check(PlayerPosition);
	PlayerPosition->SetPiece(PlayerPiece.Get());

	constexpr float EnemyHealth = 5.f;
	constexpr float EnemyDamage = 1.f;
	constexpr float EnemyMovementSpeed = 1.f;
	EnemyPiece = MakeUnique<FPiece>(ETeam::Enemy, EnemyHealth, EnemyDamage, EnemyMovementSpeed);
	FTile* EnemyPosition = GetRandomEmptyTile(InRandomSeed);
	check(EnemyPosition);
	EnemyPosition->SetPiece(EnemyPiece.Get());
}

FSimulation::~FSimulation()
{
	CommandsData = nullptr;
}

void FSimulation::FixedUpdate(const float InDeltaTime)
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
		CommandsData->Enqueue(MakeUnique<FAttackCommandData>(&InAttacker, &InTarget));

		if (InTarget.IsDead())
		{
			CommandsData->Enqueue(MakeUnique<FDeathCommandData>(&InTarget));
		}
	}
	else
	{
		FTile* NewPosition = const_cast<FTile*>(PathToTarget[0]); // TODO: Remove this const_cast.
		check(NewPosition);
		if (NewPosition->IsEmpty())
		{
			InAttacker.MoveTo(NewPosition);
			CommandsData->Enqueue(MakeUnique<FMoveCommandData>(&InAttacker, NewPosition));
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
