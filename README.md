# Codename Juno
A small auto-battler.

# Unreal Engine Version
The project was created with Unreal Engine 5.4.4 (compiled from source). No additional dependencies.

# Documentation
The most important class is the JunoGameMode. It does two important things:
- Simulation->FixedUpdate() - Runs in a custom **JunoGameMode::FixedUpdate**. The "Simulation" plays the role of an authoritative server that updates the game state by following deterministic steps. Each change is enqueued as a command.
- Visualization->Update() - Runs in the **JunoGameMode::Tick**. The "Visualization" plays the role of a client. It reads the output from the simulation (command queue) and updates the visual game state.
