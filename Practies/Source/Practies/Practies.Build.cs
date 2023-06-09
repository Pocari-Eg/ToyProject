// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Practies : ModuleRules
{
	public Practies(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "GameplayTasks", "NavigationSystem", "AIModule", "Niagara" });
		
    }
}
