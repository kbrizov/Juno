// Christian Rizov's Juno.

#include "Simulation.h"

FSimulation::FSimulation(TQueue<FCommand*>* InCommands, const FGrid& InGrid)
{
	check(InCommands);
	Commands = InCommands;
	Grid = InGrid;
}

FSimulation::~FSimulation()
{
	Commands = nullptr;
}

void FSimulation::FixedUpdate(const float DeltaTime)
{
}
