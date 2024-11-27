// Christian Rizov's Juno.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridVisual.generated.h"

class FGrid;
class ATileVisual;

UCLASS(Abstract)
class JUNO_API AGridVisual : public AActor
{
	GENERATED_BODY()

public:
	AGridVisual();

	void Initialize(const FGrid* InGrid);

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATileVisual> DarkTileClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATileVisual> LightTileClass;

	TArray<TObjectPtr<ATileVisual>> Tiles;
};
