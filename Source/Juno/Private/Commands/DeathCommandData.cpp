// Christian Rizov's Juno.

#include "Commands/DeathCommandData.h"

FDeathCommandData::FDeathCommandData(FPiece* InPiece)
	: FCommandData(InPiece, ECommandType::Death)
{
}
