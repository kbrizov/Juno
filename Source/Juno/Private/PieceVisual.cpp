// Christian Rizov's Juno.

#include "PieceVisual.h"

APieceVisual::APieceVisual()
{
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}

void APieceVisual::Attack_Implementation(const APieceVisual* InOther)
{
	// TODO: Spawn particles, change colors, etc.
}

void APieceVisual::Die_Implementation()
{
	// TODO: Spawn death particle.
	Destroy();
}
