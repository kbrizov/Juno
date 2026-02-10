// Christian Rizov's Juno.

using UnrealBuildTool;

public class Juno : ModuleRules
{
	public Juno(ReadOnlyTargetRules Target)
		: base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(["Core", "CoreUObject", "Engine", "InputCore"]);

		PrivateDependencyModuleNames.AddRange([]);
	}
}