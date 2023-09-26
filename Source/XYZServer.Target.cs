// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class XYZServerTarget : TargetRules
{
	public XYZServerTarget(TargetInfo Target) : base(Target)
	{
        Type = TargetType.Server;
        DefaultBuildSettings = BuildSettingsVersion.V4;
        ExtraModuleNames.AddRange(new string[] { "XYZ" });
    }
}
