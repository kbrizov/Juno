// Christian Rizov's Juno.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PieceVisual.generated.h"

UCLASS(Abstract)
class JUNO_API APieceVisual : public AActor
{
	GENERATED_BODY()

public:
	APieceVisual();

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> Mesh;
};
