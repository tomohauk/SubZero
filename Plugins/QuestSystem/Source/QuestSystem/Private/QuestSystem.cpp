//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.

#include "QuestSystemPrivatePCH.h"

#include "SlateBasics.h"
#include "SlateExtras.h"

#include "QuestSystemStyle.h"
#include "QuestSystemCommands.h"

#include "SQuestList.h"

#include "LevelEditor.h"

static const FName QuestSystemTabName("QuestSystem");

#define LOCTEXT_NAMESPACE "FQuestSystemModule"

void FQuestSystemModule::StartupModule()
{
	//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved. This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FQuestSystemStyle::Initialize();
	FQuestSystemStyle::ReloadTextures();

	FQuestSystemCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FQuestSystemCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FQuestSystemModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FQuestSystemModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FQuestSystemModule::AddToolbarExtension));
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(QuestSystemTabName, FOnSpawnTab::CreateRaw(this, &FQuestSystemModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FQuestSystemTabTitle", "QuestSystem"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FQuestSystemModule::ShutdownModule()
{
	//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved. This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved. we call this function before unloading the module.
	FQuestSystemStyle::Shutdown();

	FQuestSystemCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(QuestSystemTabName);
}

TSharedRef<SDockTab> FQuestSystemModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved. Put your tab content here!
			SNew(SOverlay)
			+ SOverlay::Slot()
//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.			.HAlign(HAlign_Center)
//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.			.VAlign(VAlign_Center)
			[
				SNew(SQuestList)
			]
		];
}

void FQuestSystemModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(QuestSystemTabName);
}

void FQuestSystemModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FQuestSystemCommands::Get().OpenPluginWindow);
}

void FQuestSystemModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FQuestSystemCommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FQuestSystemModule, QuestSystem)