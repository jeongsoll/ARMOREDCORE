// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ArmoredCore : ModuleRules
{
	public ArmoredCore(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
			{ "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

		PublicIncludePaths.AddRange(new string[]
		{
			"ArmoredCore/Public",
			"ArmoredCore/Public/Projectile"
		});
	}
}