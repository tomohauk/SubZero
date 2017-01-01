//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.

#pragma once

#include "Object.h"
#include "Dialogue_Topic.generated.h"

UENUM(BlueprintType)
enum class ETopicType : uint8
{
	TT_General UMETA(DisplayName = "General"),
	TT_Category UMETA(DisplayName = "Category"),
	TT_Greeting UMETA(DisplayName = "Greeting"),
	TT_Link UMETA(DisplayName = "Link")
};

UCLASS(Blueprintable)
class SUBZERO_API UDialogue_Topic : public UObject
{
	GENERATED_BODY()
	
public:

	//Topic ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Topic ID")
	int topicID;
	//Topic Name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Topic Name")
	FText topicName;
	//Topic Text
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Topic Text")
	FText topicText;
	//Topic Type
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Topic Type")
	ETopicType topicType;
	//Child Topics
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Topic Children")
	TArray<UDialogue_Topic *> children;
	//Parent Topic
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Parent Topic")
	UDialogue_Topic * parent;
	//Link URL String
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "URL String")
	FString urlString;

public:
	//Construct and return a new topic
	UFUNCTION(meta=(BlueprintInternalUseOnly))
	static UDialogue_Topic * CreateTopic(UObject * owner, int id, FText name, FText text, ETopicType type, TArray<UDialogue_Topic *> childTopics, UDialogue_Topic * TopicParent, FString url = "None");
	
	//Adds a Dialogue_Topic to the owners children array
	UFUNCTION(BlueprintCallable, Category = "Dialogue|Topic")
	void AddChild(UDialogue_Topic * childToAdd);
};
