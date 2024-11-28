// Christian Rizov's Juno.

#include "Visualization.h"
#include "GridVisual.h"
#include "Piece.h"
#include "PieceVisual.h"
#include "Tile.h"
#include "Commands/AttackCommand.h"
#include "Commands/AttackCommandData.h"
#include "Commands/CommandData.h"
#include "Commands/DeathCommand.h"
#include "Commands/DeathCommandData.h"
#include "Commands/MoveCommand.h"
#include "Commands/MoveCommandData.h"

FVisualization::FVisualization(TQueue<TUniquePtr<FCommandData>>* InCommandsData, AGridVisual* InGrid, APieceVisual* InPlayerPiece, APieceVisual* InEnemyPiece)
{
	check(InCommandsData);
	CommandsData = InCommandsData;

	check(InGrid);
	Grid = InGrid;

	check(InPlayerPiece);
	PlayerPiece = InPlayerPiece;

	check(InEnemyPiece);
	EnemyPiece = InEnemyPiece;
}

FVisualization::~FVisualization()
{
	CommandsData = nullptr;
}

void FVisualization::FixedUpdate(const float InDeltaTime)
{
	TUniquePtr<FCommandData> CommandData = nullptr;
	if (CommandsData->Dequeue(CommandData))
	{
		TUniquePtr<FCommand> CommandToExecute = nullptr;
		const ECommandType CommandType = CommandData->GetType();

		if (CommandType == ECommandType::Move)
		{
			CommandToExecute = MakeMoveCommand(*CommandData);
		}
		else if (CommandType == ECommandType::Attack)
		{
			CommandToExecute = MakeAttackCommand(*CommandData);
		}
		else if (CommandType == ECommandType::Death)
		{
			CommandToExecute = MakeDeathCommand(*CommandData);
		}

		CommandToExecute->Execute(InDeltaTime);
	}
}

TUniquePtr<FMoveCommand> FVisualization::MakeMoveCommand(const FCommandData& InData) const
{
	check(InData.GetType() == ECommandType::Move);

	const FMoveCommandData& MoveCommandData = static_cast<const FMoveCommandData&>(InData);

	const FPiece* Piece = MoveCommandData.GetPiece();
	const FTile* NewTile = MoveCommandData.GetNewTile();

	APieceVisual* PieceVisual = GetPieceVisualFrom(Piece);
	ATileVisual* NewTileVisual = GetTileVisualFrom(NewTile);

	const FVector ZOffset = FVector(0.f, 0.f, 50.f);
	return MakeUnique<FMoveCommand>(PieceVisual, NewTileVisual, ZOffset);
}

TUniquePtr<FAttackCommand> FVisualization::MakeAttackCommand(const FCommandData& InData) const
{
	check(InData.GetType() == ECommandType::Attack);

	const FAttackCommandData& AttackCommandData = static_cast<const FAttackCommandData&>(InData);

	const FPiece* Attacker = AttackCommandData.GetPiece();
	const FPiece* Target = AttackCommandData.GetTarget();

	APieceVisual* AttackerVisual = GetPieceVisualFrom(Attacker);
	APieceVisual* TargetVisual = GetPieceVisualFrom(Target);

	return MakeUnique<FAttackCommand>(AttackerVisual, TargetVisual);
}

TUniquePtr<FDeathCommand> FVisualization::MakeDeathCommand(const FCommandData& InData) const
{
	check(InData.GetType() == ECommandType::Death);

	const FDeathCommandData& DeathCommandData = static_cast<const FDeathCommandData&>(InData);
	const FPiece* Piece = DeathCommandData.GetPiece();
	APieceVisual* PieceVisual = GetPieceVisualFrom(Piece);

	return MakeUnique<FDeathCommand>(PieceVisual);
}

APieceVisual* FVisualization::GetPieceVisualFrom(const FPiece* InPiece) const
{
	if (!ensure(InPiece))
	{
		return nullptr;
	}

	return InPiece->GetTeam() == ETeam::Player ? PlayerPiece.Get() : EnemyPiece.Get();
}

ATileVisual* FVisualization::GetTileVisualFrom(const FTile* InTile) const
{
	if (!ensure(InTile))
	{
		return nullptr;
	}

	const uint32 Row = InTile->GetRow();
	const uint32 Column = InTile->GetColumn();
	return (*Grid)[Row][Column];
}
