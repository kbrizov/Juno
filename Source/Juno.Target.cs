// Christian Rizov's Juno.

using UnrealBuildTool;

public class JunoTarget : TargetRules
{
	public JunoTarget(TargetInfo Target)
		: base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V6;

		ExtraModuleNames.AddRange(["Juno"]);
	}
}