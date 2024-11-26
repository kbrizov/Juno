#pragma once

#include "CoreMinimal.h"
#include "Commands/Command.h"

class FTile;

class FMoveCommand final : public FCommand
{
public:
	FMoveCommand(TSharedPtr<FPiece> InPiece, TSharedPtr<FTile> InNewPosition);

	virtual void Execute(const float DeltaTime) override;

private:
	TSharedPtr<FTile> NewPosition;
};
