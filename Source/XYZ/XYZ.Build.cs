// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class XYZ : ModuleRules
{
	public XYZ(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"HeadMountedDisplay", 
			"NavigationSystem", 
			"AIModule", 
			"HTTP",
			"Json",
			"WebSockets",
			"Niagara", 
			"EnhancedInput", 
			"UMG", 
			"CableComponent",
			"OnlineSubsystem", 
			"OnlineSubsystemUtils" });
    }
}
