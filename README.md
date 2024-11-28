# Codename Juno
A small auto-battler.

# Unreal Engine Version
The project was created with Unreal Engine 5.4.4 (compiled from source). No additional dependencies.

# Documentation
The most important class is the JunoGameMode. It runs a custom FixedUpdate which does two important things:
- Every TimeStep (configured in the JunoGameMode) a "Simulation" updates the state of the game by following deterministic rules. The output of the simulation is a queue of commands. Think of the simulation as an authoritative server.
- After each "simulation step" comes a "visualization step". The game mode dequeues a command and executes it. The output of a command is some sort of visual representation.
That way the "simulation" and "visualization" are kept separate.
