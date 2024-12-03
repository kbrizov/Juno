// Christian Rizov's Juno.

#pragma once

#include "CoreMinimal.h"

enum class ECommandStatus
{
	Pending,
	InProgress,
	Completed
};

class APieceVisual;

class JUNO_API FCommand
{
public:
	virtual ~FCommand() = default;

	virtual void Execute(float InDeltaTime) = 0;

	bool IsPending() const;
	bool IsInProgress() const;
	bool IsCompleted() const;

protected:
	APieceVisual* Piece;
	ECommandStatus Status;

	FCommand(APieceVisual* InPiece);
};

inline bool FCommand::IsPending() const
{
	return Status == ECommandStatus::Pending;
}

inline bool FCommand::IsInProgress() const
{
	return Status == ECommandStatus::InProgress;
}

inline bool FCommand::IsCompleted() const
{
	return Status == ECommandStatus::Completed;
}
