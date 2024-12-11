# Codename Juno
A small auto-battler.

# Unreal Engine Version
Unreal Engine 5.5.1.

# Documentation
The most important class is the JunoGameMode. It does two important things:
- Simulation->FixedUpdate() - Runs in a custom **JunoGameMode::FixedUpdate**. The "Simulation" plays the role of an authoritative server that updates the game state by following deterministic steps. Each change is enqueued as a command.
- Visualization->Update() - Runs in the **JunoGameMode::Tick**. The "Visualization" plays the role of a client. It reads the output from the simulation (command queue) and updates the visual game state.
