//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.

using UnrealBuildTool;

public class QuestSystem : ModuleRules
{
	public QuestSystem(TargetInfo Target)
	{
		
		PublicIncludePaths.AddRange(
			new string[] {
				"QuestSystem/Public"
				//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved. ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"QuestSystem/Private",
				//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved. ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved. ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Projects",
				"InputCore",
				"UnrealEd",
				"LevelEditor",
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved. ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved. ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
