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
	explicit FPiece(const ETeam InTeam, const float InHealth = 1.f, const float InDamage = 1.f, const uint32 InMovementSpeed = 1.f);

	float GetHealth() const;

	float GetDamage() const;

	uint32 GetMovementSpeed() const;

	const FTile* GetPosition() const;
	void SetPosition(FTile* InPosition);

	void TakeDamage(const float InDamage);

private:
	ETeam Team;
	float Health;
	float Damage;
	uint32 MovementSpeed;
	FTile* Position;
};

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

inline const FTile* FPiece::GetPosition() const
{
	return Position;
}
