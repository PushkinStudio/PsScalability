// Copyright 2015-2020 Mail.Ru Group. All Rights Reserved.

using UnrealBuildTool;

public class PsScalability : ModuleRules
{
    public PsScalability(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateIncludePaths.AddRange(new string[] {
                "PsScalability/Private"
        });

        PrivateDependencyModuleNames.AddRange(new string[] {
                "Core",
                "CoreUObject",
                "Engine"
        });

    }
}
