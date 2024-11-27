// Christian Rizov's Juno.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridVisual.generated.h"

class APieceVisual;
class ATileVisual;
class FGrid;
class FTile;
class FPiece;

UCLASS(Abstract)
class JUNO_API AGridVisual : public AActor
{
	GENERATED_BODY()

public:
	AGridVisual();

	void Initialize(const FGrid& InGrid);

	TArray<TObjectPtr<ATileVisual>>& operator[](const uint32 Index);
	const TArray<TObjectPtr<ATileVisual>>& operator[](const uint32 Index) const;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATileVisual> DarkTileClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATileVisual> LightTileClass;

	TArray<TArray<TObjectPtr<ATileVisual>>> Tiles;

	ATileVisual* SpawnTileVisual(UWorld& InWorld, const FTile& InTile);
};
