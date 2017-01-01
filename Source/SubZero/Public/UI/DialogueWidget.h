//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.

#pragma once

#include "DialogueWidget.generated.h"

/**
 * 
 */

UCLASS()
class SUBZERO_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, Category = "User Interface", meta = (Keywords = "Begin Play"))
	void ConstructWithOwner(ASubZeroCharacter * OwningActor);	

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, DisplayName = "debugNPCName")
	FString debugNPCName;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, DisplayName = "debugTopicCount")
	int debugTopicCount;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, DisplayName = "dialogueTargetNPC")
	class ANPC * targetNPC;
};
