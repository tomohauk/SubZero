//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.

#pragma once

#include "QuestSystemPrivatePCH.h"
#include "SlateExtras.h"
#include "QuestSystem.h"
#include "SQuestStageList.h"

struct FQuestStage
{
	int32 StageId;
	FString StageName;
	TArray<FString> StageWinConditions;
};

struct FQuest
{
	FString Id;
	FString Name;
	int32 StageCount;
	bool Completed;
	TArray<FString> WinConditions;
	TArray<TSharedPtr<FQuestStage>> QuestStages;
};

class SQuestList : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SQuestList)
	{}

	SLATE_END_ARGS()

	//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.Needed for every widget!!!!!
	void Construct(const FArguments& InArgs);

	//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.Creates single item widget for every list item
	TSharedRef<ITableRow> MakeListViewWidget(TSharedPtr<FQuest> Item, const TSharedRef<STableViewBase>& OwnerTable);

	//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.Double click on an item in the quest list.
	void OnItemDoubleClicked(TSharedPtr<FQuest> ClickItem);

protected:
	TArray<TSharedPtr<FQuest>> RowItems;

	TSharedPtr<STextBlock> testText;

	TSharedPtr< SListView< TSharedPtr<FQuest>>> RowWidget;

protected: //Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.All the quest editor raw data
	TSharedPtr<SEditableTextBox> qIdText;
	TSharedPtr<SEditableTextBox> qNameText;
	TSharedPtr<SCheckBox> qCompleteCheck;

	//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.Quest being edited
	TSharedPtr<FQuest> CurrentEditingQuest;

	//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.Quest Stages
	TSharedPtr<SQuestStageList> qStages;
};