#pragma once

#include "QuestSystemPrivatePCH.h"

struct FQuest;
struct FQuestStage;

class SQuestStageList : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SQuestStageList)
	: _QuestStages( static_cast<const TArray<FQuestStage>*>(nullptr) )
	{ 	}

	SLATE_ARGUMENT(const TArray<FQuestStage>*, QuestStages)

	SLATE_END_ARGS()

	void Construct(const FArguments& args);

	TSharedRef<ITableRow> MakeListViewWidget(TSharedPtr<FQuestStage> Item, const TSharedRef<STableViewBase>& OwnerTable);

	void OnItemDoubleClicked(TSharedPtr<FQuestStage> ClickItem);

	//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.Pass in the current quest to get stages from
	void SetCurrentQuest(const TSharedPtr<FQuest> inQuest);

protected:

	TSharedPtr< SListView<TSharedPtr<FQuestStage> > > StageList;

	TArray<TSharedPtr<FQuestStage> > CurrentStages;
};
