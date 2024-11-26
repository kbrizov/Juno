// Christian Rizov's Juno.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "JunoGameMode.generated.h"

UCLASS(Abstract)
class JUNO_API AJunoGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	FTimerHandle FixedUpdateTimerHandle;

	UPROPERTY(EditDefaultsOnly, meta=(UIMin = 1))
	float TimeStepInSeconds = 0.1f; // 100 ms.

	void FixedUpdate();
};
