// Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.www.darkrisingstudios.com

#include "SubZero.h"
#include "QuestConditionSystem.h"

bool UQuestConditionSystem::Evaluate(FString ConditionString)
{
	/*
	Example strings
	"HasItem,321313"
	"IsTrue,e,playerHealth,10.0"
	"StageComplete,12"
	*/
	TArray<FString> ConditionBreakdown;

	ConditionString.ParseIntoArray(ConditionBreakdown, *FString(","));

	for (FString str : ConditionBreakdown)
	{
	}
	return true;
}

void UQuestConditionSystem::BuildConditionString(TArray<FString> & outConditions, FXmlNode * inNode)
{
	if (!inNode->GetTag().Equals("Conditions"))
	{
		return;
	}

	for (FXmlNode * conditionNodes : inNode->GetChildrenNodes())
	{
		FString conditionStr;

		if (conditionNodes->GetTag().Equals("HasItem"))
		{
			conditionStr += "HasItem,";
			conditionStr += conditionNodes->GetAttribute("itemId");
		}
		else if (conditionNodes->GetTag().Equals("IsTrue"))
		{
			conditionStr += "IsTrue,";
			conditionStr += conditionNodes->GetAttribute("condition") + ",";
			conditionStr += conditionNodes->GetAttribute("variable") + ",";
			conditionStr += conditionNodes->GetAttribute("value");
		}
		else if (conditionNodes->GetTag().Equals("IsFalse"))
		{
			conditionStr += "IsFalse,";
			conditionStr += conditionNodes->GetAttribute("condition") + ",";
			conditionStr += conditionNodes->GetAttribute("variable") + ",";
			conditionStr += conditionNodes->GetAttribute("value");
		}
		else if (conditionNodes->GetTag().Equals("StageComplete"))
		{
			conditionStr += "StageComplete,";
			conditionStr += conditionNodes->GetAttribute("id");
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Unknown Quest Condition!"));
		}

		outConditions.Add(conditionStr);
	}
}
