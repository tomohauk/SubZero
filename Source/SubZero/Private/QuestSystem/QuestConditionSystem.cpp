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
