// Christian Rizov's Juno.

#include "TileVisual.h"

ATileVisual::ATileVisual()
{
    PrimaryActorTick.bCanEverTick = false;
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;
}
