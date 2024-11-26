// Christian Rizov's Juno.

#include "GameModes/JunoGameMode.h"
#include "Kismet/KismetSystemLibrary.h"

void AJunoGameMode::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(FixedUpdateTimerHandle, this, &AJunoGameMode::FixedUpdate, TimeStepInSeconds, true);
}

void AJunoGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorldTimerManager().ClearTimer(FixedUpdateTimerHandle);
	Super::EndPlay(EndPlayReason);
}

void AJunoGameMode::FixedUpdate()
{
	UKismetSystemLibrary::PrintString(this, "FixedUpdate");
}
