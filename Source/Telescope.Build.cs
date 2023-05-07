// Copyright 2017 Treasure Data, Inc. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class Telescope : ModuleRules
	{
		public Telescope(ReadOnlyTargetRules Target): base(Target)
		{
			PublicIncludePaths.AddRange(
				new string[] {
				}
				);

			PrivateIncludePaths.AddRange(
				new string[] {
					"Telescope/Private",
				}
				);

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
                    "CoreUObject",
                    "Engine",
				}
				);

			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
                    "Analytics",
                    "HTTP",
                    "Json",
				}
				);

			DynamicallyLoadedModuleNames.AddRange(
				new string[]
				{

				}
				);
		}
	}
}