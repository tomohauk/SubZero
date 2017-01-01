//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.

#include "QuestSystemPrivatePCH.h"
#include "QuestSystemCommands.h"

#define LOCTEXT_NAMESPACE "FQuestSystemModule"

void FQuestSystemCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "Quest Editor", "Open the Quest Editor window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
