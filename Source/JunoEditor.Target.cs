// Christian Rizov's Juno.

using UnrealBuildTool;

public class JunoEditorTarget : TargetRules
{
	public JunoEditorTarget(TargetInfo Target)
		: base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V6;

		ExtraModuleNames.AddRange(["Juno"]);
	}
}