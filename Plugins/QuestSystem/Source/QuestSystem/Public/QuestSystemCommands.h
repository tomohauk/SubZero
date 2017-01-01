//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.

#pragma once

#include "SlateBasics.h"
#include "QuestSystemStyle.h"

class FQuestSystemCommands : public TCommands<FQuestSystemCommands>
{
public:

	FQuestSystemCommands()
		: TCommands<FQuestSystemCommands>(TEXT("QuestSystem"), NSLOCTEXT("Contexts", "QuestSystem", "QuestSystem Plugin"), NAME_None, FQuestSystemStyle::GetStyleSetName())
	{
	}

	//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved. TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};