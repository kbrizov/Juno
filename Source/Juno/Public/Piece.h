// Christian Rizov's Juno.

#pragma once

#include "CoreMinimal.h"

class FTile;

enum class ETeam
{
	Player,
	Enemy
};

/**
 * Used to simulate/mock pieces on the server.
 */
class JUNO_API FPiece
{
public:
	explicit FPiece(const ETeam InTeam, const float InHealth = 1.f, const float InDamage = 1.f, const uint32 InMovementSpeed = 1.f, const uint32 InAttackRange = 1);

	void MoveTo(FTile* InPosition);

	void Attack(FPiece* InEnemy) const;

	ETeam GetTeam() const;

	float GetHealth() const;

	float GetDamage() const;

	uint32 GetMovementSpeed() const;

	uint32 GetAttackRange() const;

	const FTile* GetPosition() const;
	void SetPosition(FTile* InPosition);

	void TakeDamage(const float InDamage);

	bool IsInAttackRange(const TArray<const FTile*>& InPathToEnemy) const;
	bool IsDead() const;

private:
	ETeam Team;
	float Health;
	float Damage;
	uint32 MovementSpeed;
	uint32 AttackRange;
	FTile* Position;

	bool IsEnemy(const FPiece* InOther) const;
};

inline ETeam FPiece::GetTeam() const
{
	return Team;
}

inline float FPiece::GetHealth() const
{
	return Health;
}

inline float FPiece::GetDamage() const
{
	return Damage;
}

inline uint32 FPiece::GetMovementSpeed() const
{
	return MovementSpeed;
}

inline uint32 FPiece::GetAttackRange() const
{
	return AttackRange;
}

inline const FTile* FPiece::GetPosition() const
{
	return Position;
}
