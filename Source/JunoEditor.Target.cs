// Christian Rizov's Juno.

using UnrealBuildTool;
using System.Collections.Generic;

public class JunoEditorTarget : TargetRules
{
	public JunoEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "Juno" } );
	}
}
