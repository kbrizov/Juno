// Christian Rizov's Juno.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PieceVisual.generated.h"

class ATileVisual;

UCLASS(Abstract)
class JUNO_API APieceVisual : public AActor
{
	GENERATED_BODY()

public:
	APieceVisual();

	UFUNCTION(BlueprintNativeEvent)
	void MoveTo(const ATileVisual* InNewLocation, const FVector& InOffset = FVector::ZeroVector);

	UFUNCTION(BlueprintNativeEvent)
	void Attack(const APieceVisual* InOther);

	UFUNCTION(BlueprintNativeEvent)
	void Die();

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> Mesh;
};
