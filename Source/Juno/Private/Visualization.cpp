// Christian Rizov's Juno.

#include "Visualization.h"
#include "GridVisual.h"
#include "Piece.h"
#include "PieceVisual.h"
#include "Tile.h"
#include "Commands/AttackCommandData.h"
#include "Commands/CommandData.h"
#include "Commands/DeathCommandData.h"
#include "Commands/MoveCommandData.h"

FVisualization::FVisualization(TQueue<TSharedPtr<FCommandData>>* InCommandsData, AGridVisual* InGrid, APieceVisual* InPlayerPiece, APieceVisual* InEnemyPiece)
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
	TSharedPtr<FCommandData> Command = nullptr;
	if (CommandsData->Dequeue(Command))
	{
		ExecuteCommand(Command.Get());
	}
}

void FVisualization::ExecuteCommand(const FCommandData* InCommand)
{
	check(InCommand);

	/**
	 * I'm forced to do these static_casts because I failed to predict that I will need RTTI for the commands.
	 * The initial idea was for them to have a virtual Execute method. However, now they are just a ledger.
	 * FCommand is not derived from UOBject so I cant use Cast<T> and dynamic_cast is disabled.
	 * Ideally I'd refactor the commands to be UObjects, but it's not a trivial thing to do at this point and I don't have time.
	 */

	const ECommandType CommandType = InCommand->GetType();

	if (CommandType == ECommandType::Move)
	{
		const FMoveCommandData* MoveCommand = static_cast<const FMoveCommandData*>(InCommand);
		const FPiece* Piece = MoveCommand->GetPiece();
		const FTile* Tile = MoveCommand->GetNewPosition();

		APieceVisual* PieceVisual = GetPieceVisualFrom(Piece);
		ATileVisual* TileVisual = GetTileVisualFrom(Tile);

		check(PieceVisual);
		const FVector ZOffset = FVector(0.0f, 0.0f, 50.0f);
		PieceVisual->MoveTo(TileVisual, ZOffset);
	}
	else if (CommandType == ECommandType::Attack)
	{
		const FAttackCommandData* AttackCommand = static_cast<const FAttackCommandData*>(InCommand);
		const FPiece* Attacker = AttackCommand->GetPiece();
		const FPiece* Target = AttackCommand->GetTarget();

		APieceVisual* AttackerVisual = GetPieceVisualFrom(Attacker);
		APieceVisual* TargetVisual = GetPieceVisualFrom(Target);

		check(AttackerVisual);
		AttackerVisual->Attack(TargetVisual);
	}
	else if (CommandType == ECommandType::Death)
	{
		const FDeathCommandData* DeathCommand = static_cast<const FDeathCommandData*>(InCommand);
		const FPiece* Piece = DeathCommand->GetPiece();
		APieceVisual* PieceVisual = GetPieceVisualFrom(Piece);
		check(PieceVisual);
		PieceVisual->Die();
	}
}

APieceVisual* FVisualization::GetPieceVisualFrom(const FPiece* InPiece) const
{
	if (!ensure(InPiece))
	{
		return nullptr;
	}

	return InPiece->GetTeam() == ETeam::Player? PlayerPiece.Get() : EnemyPiece.Get();
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
