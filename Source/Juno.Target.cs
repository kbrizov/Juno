// Christian Rizov's Juno.

using UnrealBuildTool;
using System.Collections.Generic;

public class JunoTarget : TargetRules
{
	public JunoTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "Juno" } );
	}
}
