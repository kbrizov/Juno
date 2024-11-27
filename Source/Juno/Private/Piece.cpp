// Christian Rizov's Juno.

#include "Piece.h"
#include "Tile.h"

FPiece::FPiece(const ETeam InTeam, const float InHealth, const float InDamage, const uint32 InMovementSpeed, const uint32 InAttackRange)
	: Team(InTeam), Health(InHealth), Damage(InDamage), MovementSpeed(InMovementSpeed), AttackRange(InAttackRange), Position(nullptr)
{
}

void FPiece::MoveTo(const FTile* InPosition)
{
	check(InPosition);
	// I forced myself into this const_cast because the pathfinding works with readonly collections.
	// TODO: Refactor.
	SetPosition(const_cast<FTile*>(InPosition));
}

void FPiece::Attack(FPiece* InEnemy)
{
	check(InEnemy);
	InEnemy->TakeDamage(GetDamage());
}

void FPiece::Die()
{
	// TODO: Generate death command.
}

inline void FPiece::SetPosition(FTile* InPosition)
{
	if (Position != nullptr)
	{
		Position->Clear();
	}

	Position = InPosition;
}

void FPiece::TakeDamage(const float InDamage)
{
	Health = FMath::Max(Health - InDamage, 0);

	if (FMath::IsNearlyZero(Health))
	{
		Die();
	}
}

bool FPiece::IsInAttackRange(const TArray<const FTile*>& InPathToEnemy) const
{
	ensure(!InPathToEnemy.IsEmpty());
	return static_cast<uint32>(InPathToEnemy.Num()) <= AttackRange;
}
