// Christian Rizov's Juno.

#pragma once

#include "CoreMinimal.h"
#include "Tile.h"

/**
 * Used to simulate/mock pieces on the server.
 */
class JUNO_API FPiece
{
public:
	FPiece(const float InHealth = 1.f, const float InDamage = 1.f, const uint32 InMovementRange = 1.f, const FTile& InPosition = FTile(0,0));

	float GetHealth() const;

	float GetDamage() const;

	uint32 GetMovementRange() const;

	const FTile& GetPosition() const;
	void SetPosition(const FTile& InPosition);

private:
	float Health;
	float Damage;
	uint32 MovementRange;
	FTile Position;
};

inline float FPiece::GetHealth() const
{
	return Health;
}

inline float FPiece::GetDamage() const
{
	return Damage;
}

inline uint32 FPiece::GetMovementRange() const
{
	return MovementRange;
}

inline const FTile& FPiece::GetPosition() const
{
	return Position;
}

inline void FPiece::SetPosition(const FTile& InPosition)
{
	Position = InPosition;
}
