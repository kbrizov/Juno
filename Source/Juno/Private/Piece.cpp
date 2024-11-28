// Christian Rizov's Juno.

#include "Piece.h"
#include "Tile.h"

FPiece::FPiece(const ETeam InTeam, const float InHealth, const float InDamage, const uint32 InMovementSpeed, const uint32 InAttackRange)
	: Team(InTeam), Health(InHealth), Damage(InDamage), MovementSpeed(InMovementSpeed), AttackRange(InAttackRange), Position(nullptr)
{
}

void FPiece::MoveTo(FTile* InPosition)
{
	check(InPosition);
	InPosition->SetPiece(this);
}

void FPiece::Attack(FPiece* InEnemy) const
{
	check(InEnemy)

	if (!ensure(IsEnemy(InEnemy)))
	{
		return;
	}

	InEnemy->TakeDamage(GetDamage());
}

void FPiece::SetPosition(FTile* InPosition)
{
	if (Position != nullptr)
	{
		Position->Clear();
	}

	Position = InPosition;
}

void FPiece::TakeDamage(const float InDamage)
{
	Health = FMath::Max(Health - InDamage, 0.f);
}

bool FPiece::IsInAttackRange(const TArray<const FTile*>& InPathToEnemy) const
{
	return static_cast<uint32>(InPathToEnemy.Num()) <= AttackRange;
}

bool FPiece::IsDead() const
{
	return FMath::IsNearlyZero(Health);
}

bool FPiece::IsEnemy(const FPiece* InOther) const
{
	check(InOther);
	return GetTeam() != InOther->GetTeam();
}
