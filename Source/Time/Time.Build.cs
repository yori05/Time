// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Time : ModuleRules
{
	public Time(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

        PrivateDependencyModuleNames.AddRange(new string[] { "UMG", "Slate", "SlateCore" });

        PublicDependencyModuleNames.AddRange(new string[] { "Module_Basic" });

        PrivateDependencyModuleNames.AddRange(new string[] { "GameplayTasks" });
    }
}
