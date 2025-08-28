// Christian Rizov's Juno.

#include "Visualization.h"
#include "GridVisual.h"
#include "Piece.h"
#include "PieceVisual.h"
#include "Tile.h"
#include "Commands/CommandData.h"
#include "Commands/AttackCommand.h"
#include "Commands/AttackCommandData.h"
#include "Commands/DeathCommand.h"
#include "Commands/DeathCommandData.h"
#include "Commands/MoveCommand.h"
#include "Commands/MoveCommandData.h"

FVisualization::FVisualization(TQueue<TUniquePtr<FCommandData>>* InCommandsData, AGridVisual* InGrid, APieceVisual* InPlayerPiece, APieceVisual* InEnemyPiece)
	: CommandsData(InCommandsData), Grid(InGrid), PlayerPiece(InPlayerPiece), EnemyPiece(InEnemyPiece)
{
	check(InCommandsData);
	check(InGrid);
	check(InPlayerPiece);
	check(InEnemyPiece);
}

FVisualization::~FVisualization()
{
	EnemyPiece.Reset();
	PlayerPiece.Reset();
	Grid.Reset();
	CommandsData = nullptr;
}

void FVisualization::Update(const float InDeltaTime)
{
	if (CurrentCommand && !CurrentCommand->IsCompleted())
	{
		CurrentCommand->Execute(InDeltaTime);
	}
	else
	{
		CurrentCommand = GetNextCommand();
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

	const float Duration = Piece->GetMovementSpeed();
	const FVector ZOffset = FVector(0.f, 0.f, 50.f);
	return MakeUnique<FMoveCommand>(PieceVisual, NewTileVisual, Duration, ZOffset);
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

TUniquePtr<FCommand> FVisualization::GetNextCommand() const
{
	TUniquePtr<FCommand> NextCommand = nullptr;
	TUniquePtr<FCommandData> NextCommandData = nullptr;

	if (CommandsData->Dequeue(NextCommandData))
	{
		const ECommandType CommandType = NextCommandData->GetType();

		if (CommandType == ECommandType::Move)
		{
			NextCommand = MakeMoveCommand(*NextCommandData);
		}
		else if (CommandType == ECommandType::Attack)
		{
			NextCommand = MakeAttackCommand(*NextCommandData);
		}
		else if (CommandType == ECommandType::Death)
		{
			NextCommand = MakeDeathCommand(*NextCommandData);
		}
	}

	return NextCommand;
}
