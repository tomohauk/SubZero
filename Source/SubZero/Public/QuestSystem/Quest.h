// Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.www.darkrisingstudios.com

#pragma once

#include "Object.h"
#include "Quest.generated.h"

/**
 * 
 */
UCLASS()
class SUBZERO_API UQuest : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Completion Time")
	float fQuestCompletionTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Number of Conditions")
	int32 iConditionCount;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Number of Stages")
	int32 iStageCount;

	
};
