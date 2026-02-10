// Christian Rizov's Juno.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileVisual.generated.h"

class UStaticMeshComponent;

UCLASS(Abstract)
class JUNO_API ATileVisual : public AActor
{
    GENERATED_BODY()

public:
    ATileVisual();

private:
    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<UStaticMeshComponent> Mesh;
};
