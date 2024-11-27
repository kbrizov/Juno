// Christian Rizov's Juno.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridVisual.generated.h"

class ATileVisual;

UCLASS(Abstract)
class JUNO_API AGridVisual : public AActor
{
	GENERATED_BODY()

public:
	AGridVisual();

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATileVisual> TileVisualClass;
};
