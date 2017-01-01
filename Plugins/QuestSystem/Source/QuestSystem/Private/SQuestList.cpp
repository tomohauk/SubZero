#include "QuestSystemPrivatePCH.h"
#include "SQuestList.h"

#define LOCTEXT_NAMESPACE "QuestSystemQuestList"

void SQuestList::Construct(const FArguments& InArgs)
{
	//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.Temp Test Quests
	FQuest * q1 = new FQuest;
	q1->Id = "TQ001";
	q1->Name = "Test Quest 1";
	q1->StageCount = 1;
	q1->Completed = true;

	FQuest * q2 = new FQuest;
	q2->Id = "TQ002";
	q2->Name = "Dinner Plates";
	q2->StageCount = 4;
	q2->Completed = false;

	FQuest * q3 = new FQuest;
	q3->Id = "MainQuest001";
	q3->Name = "Find the Missing child";
	q3->StageCount = 3;
	q3->Completed = false;

	FQuest * q4 = new FQuest;
	q4->Id = "AssasinationBill";
	q4->Name = "Bill Kill";
	q4->StageCount = 1;
	q4->Completed = false;

	TSharedPtr<FQuest> t1 = MakeShareable(q1); 	RowItems.Add(t1);
	TSharedPtr<FQuest> t2 = MakeShareable(q2); 	RowItems.Add(t2);
	TSharedPtr<FQuest> t3 = MakeShareable(q3); 	RowItems.Add(t3);
	TSharedPtr<FQuest> t4 = MakeShareable(q4); 	RowItems.Add(t4);

	ChildSlot
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		[

			SNew(SSplitter)
			.Orientation(EOrientation::Orient_Horizontal)
			+ SSplitter::Slot()
			.Value(0.25f)
			[
				SNew(SOverlay)
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
						SAssignNew(RowWidget, SListView< TSharedPtr<FQuest> >)
						.ItemHeight(30)
						.ListItemsSource(&RowItems)
						.OnGenerateRow(this, &SQuestList::MakeListViewWidget)
						.OnMouseButtonDoubleClick(this, &SQuestList::OnItemDoubleClicked)
						.HeaderRow(
									SNew(SHeaderRow)
									+ SHeaderRow::Column("ID").DefaultLabel(LOCTEXT("ID", "ID"))
									+ SHeaderRow::Column("Name").DefaultLabel(LOCTEXT("Name", "Name"))
									+ SHeaderRow::Column("StageCount").DefaultLabel(LOCTEXT("StageCount", "Stage Count"))
								  )
				]
			]
			+ SSplitter::Slot()
			.Value(0.75f)
			[
				SNew(SBorder)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[

					SNew(SOverlay)				
					+ SOverlay::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Fill)
					[
						SNew(SVerticalBox)
						+ SVerticalBox::Slot()
						.HAlign(HAlign_Fill)
						[
							SNew(SHorizontalBox) //Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.Quest ID
							+ SHorizontalBox::Slot()
							.HAlign(HAlign_Left)
							.VAlign(VAlign_Top)
							.FillWidth(0.5f)
							[
									SNew(SHorizontalBox)
									+ SHorizontalBox::Slot()
									.HAlign(HAlign_Left)
									.VAlign(VAlign_Top)
									.FillWidth(0.2f)
									.Padding(FMargin(10.0f, 10.0f, 10.0f, 10.0f))
									[
										//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.Quest ID
										SNew(STextBlock)
										.Text(LOCTEXT("QuestID", "Quest ID: "))
									]
									+ SHorizontalBox::Slot()
									.HAlign(HAlign_Left)
									.VAlign(VAlign_Top)
									.Padding(FMargin(10.0f, 10.0f, 10.0f, 10.0f))
									.FillWidth(0.4f)
									.MaxWidth(120.0f)
									[
										//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.Quest ID Edit
										SAssignNew(qIdText, SEditableTextBox)
										.ToolTipText(LOCTEXT("QuestIDTooolTip", "Quest ID(string)"))
										.MinDesiredWidth(120.0f)
									]
							]
							+ SHorizontalBox::Slot() //Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.Quest Name
							.HAlign(HAlign_Left)
							.VAlign(VAlign_Top)
							.AutoWidth()
							[
									SNew(SHorizontalBox)
									+ SHorizontalBox::Slot()
									.HAlign(HAlign_Left)
									.VAlign(VAlign_Top)
									.AutoWidth()
									.Padding(FMargin(10.0f, 10.0f, 10.0f, 10.0f))
									[
										//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.Quest Name
										SNew(STextBlock)
										.Text(LOCTEXT("QuestName", "Quest Name: "))
									]
									+ SHorizontalBox::Slot()
									.HAlign(HAlign_Left)
									.VAlign(VAlign_Top)
									.Padding(FMargin(10.0f, 10.0f, 10.0f, 10.0f))
									.AutoWidth()
									.MaxWidth(120.0f)
									[
										//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.Quest Name Edit
										SAssignNew(qNameText, SEditableTextBox)
										.ToolTipText(LOCTEXT("QuestNameTooolTip", "Quest Name(string)"))
										.MinDesiredWidth(120.0f)
									]
							]
							+ SHorizontalBox::Slot()
							.AutoWidth()
							.HAlign(HAlign_Left)
							.VAlign(VAlign_Top)
							[
									SNew(SHorizontalBox)
									+ SHorizontalBox::Slot()
									.HAlign(HAlign_Left)
									.VAlign(VAlign_Top)
									.AutoWidth()
									.Padding(FMargin(10.0f, 10.0f, 10.0f, 10.0f))
									[
										//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.Quest Completed
										SNew(STextBlock)
										.Text(LOCTEXT("QuestCompleted", "Quest Completed: "))
									]
									+ SHorizontalBox::Slot()
									.HAlign(HAlign_Left)
									.VAlign(VAlign_Top)
									.Padding(FMargin(10.0f, 10.0f, 10.0f, 10.0f))
									.AutoWidth()
									[
										//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.Quest Completed Check
										SAssignNew(qCompleteCheck, SCheckBox)
										.IsChecked(ECheckBoxState::Unchecked)
									]
							]
						]
						+ SVerticalBox::Slot()
						.AutoHeight()
						.HAlign(HAlign_Fill)
						[
							SAssignNew(qStages, SQuestStageList)
						]
					]
					+ SOverlay::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					[
						SAssignNew(testText, STextBlock)
						.Text(LOCTEXT("TextBlockText", "The Quest Editor shall go here."))
					.ToolTipText(LOCTEXT("TextBlockToolTop", "Testing my cool tool tip"))
					]
				]
			]
		];
}

TSharedRef<ITableRow> SQuestList::MakeListViewWidget(TSharedPtr<FQuest> Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	class SStringRowWidget : public SMultiColumnTableRow< TSharedPtr<FQuest> >
	{
	public:
		SLATE_BEGIN_ARGS(SStringRowWidget) {}
		SLATE_END_ARGS()

		void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable, TSharedPtr<FQuest> InItem)
		{
			Item = InItem;
			SMultiColumnTableRow< TSharedPtr<FQuest>>::Construct(FSuperRowType::FArguments(), InOwnerTable);
		}

		TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName)
		{
			FText text = FText::GetEmpty();

			if (ColumnName == "ID")
				text = FText::FromString(Item->Id);
			else if (ColumnName == "Name")
				text = FText::FromString(Item->Name);
			else if (ColumnName == "StageCount")
				text = FText::FromString(FString::FromInt(Item->StageCount));

			return SNew(STextBlock)
		           .Text(text);
		}
		TSharedPtr<FQuest> Item;
	};

	return SNew(SStringRowWidget, OwnerTable, Item);
}

void SQuestList::OnItemDoubleClicked(TSharedPtr<FQuest> ClickItem)
{
	qIdText->SetText(FText::FromString(ClickItem->Id));

	qNameText->SetText(FText::FromString(ClickItem->Name));

	ClickItem->Completed ? qCompleteCheck->SetIsChecked(ECheckBoxState::Checked) : qCompleteCheck->SetIsChecked(ECheckBoxState::Unchecked);

	CurrentEditingQuest = ClickItem;
	
}

#undef LOCTEXT_NAMESPACE