// Copyright Druid Mechanics

using UnrealBuildTool;
using System.Collections.Generic;

public class AuraEditorTarget : TargetRules
{
	public AuraEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
        bOverrideBuildEnvironment = true;  // 使用此行
        ExtraModuleNames.AddRange( new string[] { "Aura" } );
        CppStandard = CppStandardVersion.Cpp20; // 设置为 C++20

    }
}
