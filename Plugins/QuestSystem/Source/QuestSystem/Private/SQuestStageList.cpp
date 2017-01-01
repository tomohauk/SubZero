#include "QuestSystemPrivatePCH.h"
#include "SQuestList.h"
#include "SQuestStageList.h"

#define LOCTEXT_NAMESPACE "QuestStageList"

void SQuestStageList::Construct(const FArguments& args)
{
	ChildSlot
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SAssignNew(StageList, SListView< TSharedPtr<FQuestStage> >)
			.ItemHeight(30)
		.OnGenerateRow(this, &SQuestStageList::MakeListViewWidget)
		.OnMouseButtonDoubleClick(this, &SQuestStageList::OnItemDoubleClicked)
		.HeaderRow(
			SNew(SHeaderRow)
			+ SHeaderRow::Column("StageID").DefaultLabel(LOCTEXT("StageID", "ID"))
			+ SHeaderRow::Column("StageName").DefaultLabel(LOCTEXT("StageName", "Stage Name"))
			+ SHeaderRow::Column("StageConditions").DefaultLabel(LOCTEXT("StageConditions", "Stage Conditions"))
			)
		];
}

TSharedRef<ITableRow> SQuestStageList::MakeListViewWidget(TSharedPtr<FQuestStage> Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	class SStringRowWidget : public SMultiColumnTableRow< TSharedPtr<FQuestStage> >
	{
	public:
		SLATE_BEGIN_ARGS(SStringRowWidget) {}
		SLATE_END_ARGS()

			void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable, TSharedPtr<FQuestStage> InItem)
		{
			Item = InItem;
			SMultiColumnTableRow< TSharedPtr<FQuestStage>>::Construct(FSuperRowType::FArguments(), InOwnerTable);
		}

		TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName)
		{
			FText text = FText::GetEmpty();

			if (ColumnName == "ID")
				text = FText::FromString(FString::FromInt(Item->StageId));
			else if (ColumnName == "Name")
				text = FText::FromString(Item->StageName);
			//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.			else if (ColumnName == "StageCount")
			//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.				text = FText::FromString(FString::FromInt(Item->StageCount));

			return SNew(STextBlock)
				.Text(text);
		}
		TSharedPtr<FQuestStage> Item;
	};

	return SNew(SStringRowWidget, OwnerTable, Item);
}

void SQuestStageList::OnItemDoubleClicked(TSharedPtr<FQuestStage> ClickItem)
{
	
}

void SQuestStageList::SetCurrentQuest(const TSharedPtr<FQuest> inQuest)
{
	//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.If there are no stages, then return
	if (inQuest->StageCount <= 0)
		return;

	//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.Iterate through each quest stage
	for (TSharedPtr<FQuestStage> stage : inQuest->QuestStages)
	{
		CurrentStages.Add(stage);
	}
}

#undef LOCTEXT_NAMESPACE