// Christian Rizov's Juno.

#include "Piece.h"

FPiece::FPiece(const float InHealth, const float InDamage, const uint32 InMovementRange, const FTile& InPosition)
	: Health(InHealth), Damage(InDamage), MovementRange(InMovementRange), Position(InPosition)
{
}
