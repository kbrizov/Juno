// Christian Rizov's Juno.

#pragma once

#include "CoreMinimal.h"
#include "Command.h"

class JUNO_API FDeathCommand : public FCommand
{
public:
	explicit FDeathCommand(FPiece* InPiece);

	virtual void Execute(const float DeltaTime) override;
};
