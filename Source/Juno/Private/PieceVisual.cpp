// Christian Rizov's Juno.

#include "PieceVisual.h"

APieceVisual::APieceVisual()
{
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}
