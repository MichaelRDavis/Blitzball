// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Fortress : ModuleRules
{
	public Fortress(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "CoreUObject",
                "Engine",
                "InputCore",
                "OnlineSubsystem",
                "UMG",
                "AIModule",
                "GameplayTasks"
            }
        );

		PrivateDependencyModuleNames.AddRange(
            new string[] {
                "Slate",
                "SlateCore"
            }
        );
	}
}
