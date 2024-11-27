// Christian Rizov's Juno.

#include "Piece.h"
#include "Tile.h"

FPiece::FPiece(const ETeam InTeam, const float InHealth, const float InDamage, const uint32 InMovementSpeed)
	: Team(InTeam), Health(InHealth), Damage(InDamage), MovementSpeed(InMovementSpeed), Position(nullptr)
{
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
}
