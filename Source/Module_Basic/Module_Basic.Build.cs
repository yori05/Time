// Property of Florian Hulin, shouldn't be used without my consent.

using UnrealBuildTool;

public class Module_Basic : ModuleRules
{
    public Module_Basic(ReadOnlyTargetRules Target) : base(Target)
    {
        PublicDependencyModuleNames.AddRange(new string[] { });

        PrivateDependencyModuleNames.AddRange(new string[] {"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

        PrivateDependencyModuleNames.AddRange(new string[] { "UMG", "Slate", "SlateCore" });

        PrivateDependencyModuleNames.AddRange(new string[] { "GameplayTasks" });
    }
}