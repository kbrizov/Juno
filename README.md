# Codename Juno
A small auto-battler.

# Unreal Engine Version
The project was created with Unreal Engine 5.4.4 (compiled from source). No additional dependencies.

# Documentation
The most important class is the JunoGameMode. It runs a custom FixedUpdate which does two important things:
- Simulation->FixedUpdate() - The "Simulation" plays the role of an authoritative server that updates the game state by following discrete steps. Each change is enqueued as a command.
- Visualization->FixedUpdate() - The "Visualization" plays the role of client. It reads the output from the simulation (command queue) and updates the visual game state.
That way the "simulation" and "visualization" are kept separate.
