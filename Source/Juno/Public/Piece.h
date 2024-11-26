// Christian Rizov's Juno.

#pragma once

#include "CoreMinimal.h"
#include "Tile.h"

class JUNO_API FPiece
{
public:
	FPiece(const float InHealth, const float InDamage, const uint32 InMovementRange, const FTile& InPosition);
	~FPiece() = default;

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
