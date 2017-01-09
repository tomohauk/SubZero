// Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.www.darkrisingstudios.com

#pragma once

#include "Object.h"
#include "QuestConditionSystem.generated.h"

/**
 * The QuestConditionSystem creates
 * the conditions for the quests.
 *	Example string
 *		 IsTrue condition="e" variable="playerHealth" value="10" <!--The Players health is a certain value-->
 * Where 'e' is ==(Equal To)
 */

UCLASS()
class SUBZERO_API UQuestConditionSystem : public UObject
{
	GENERATED_BODY()
	
public:

	static bool Evaluate(FString ConditionString);
	static void BuildConditionString(TArray<FString> & outConditions, FXmlNode * inNode);
	
};
