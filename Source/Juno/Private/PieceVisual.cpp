// Christian Rizov's Juno.

#include "PieceVisual.h"

#include "TileVisual.h"

APieceVisual::APieceVisual()
{
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}

void APieceVisual::MoveTo(const ATileVisual* InNewLocation, const FVector& InOffset)
{
	// TODO: Lerp to new location.
	check(InNewLocation);
	const FVector NewLocation = InNewLocation->GetActorLocation() + InOffset;
	const FRotator NewRotation = InNewLocation->GetActorRotation();
	SetActorLocationAndRotation(NewLocation, NewRotation);
}

void APieceVisual::Attack(const APieceVisual* InOther)
{
	// TODO: Spawn particles, change colors, etc.
}

void APieceVisual::Die()
{
	// TODO: Spawn death particle.
	Destroy();
}
