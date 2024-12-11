// Christian Rizov's Juno.

#include "Commands/MoveCommand.h"
#include "PieceVisual.h"
#include "TileVisual.h"

FMoveCommand::FMoveCommand(APieceVisual* InPiece, ATileVisual* InNewTile, const float InDuration, const FVector& InOffset)
	: FCommand(InPiece),
	NewTile(InNewTile),
	Duration(InDuration),
	Offset(InOffset),
	StartLocation(FVector::ZeroVector),
	EndLocation(FVector::ZeroVector),
	ElapsedTime(0.f)
{
	check(InNewTile);
}

void FMoveCommand::Execute(const float InDeltaTime)
{
	if (IsPending())
	{
		StartLocation = Piece->GetActorLocation();
		EndLocation = NewTile->GetActorLocation() + Offset;
		Status = ECommandStatus::InProgress;
	}

	ElapsedTime += InDeltaTime;
	const float Alpha = FMath::Clamp(ElapsedTime / Duration, 0.f, 1.f);

	const FVector NewLocation = FMath::Lerp(StartLocation, EndLocation, Alpha);
	Piece->SetActorLocation(NewLocation);

	const bool bIsCompleted = FMath::IsNearlyEqual(Alpha, 1.f);
	if (bIsCompleted)
	{
		Status = ECommandStatus::Completed;
	}
}
