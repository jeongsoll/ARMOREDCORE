// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ArmoredCore : ModuleRules
{
	public ArmoredCore(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
			{ "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" , "UMG"});

		PublicIncludePaths.AddRange(new string[]
		{
			"ArmoredCore/Public",
			"ArmoredCore/Public/Projectile",
			"ArmoredCore/Public/PlayerState",
			"ArmoredCore/Public/PlayerUI"
		});
	}
}