//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.

#include "SubZero.h"
#include "Dialogue_Topic.h"

UDialogue_Topic * UDialogue_Topic::CreateTopic(UObject * owner, int id, FText name, FText text, ETopicType type, TArray<UDialogue_Topic*> childTopics, UDialogue_Topic * TopicParent, FString url)
{
	UDialogue_Topic * tmpTopic = NewObject<UDialogue_Topic>(owner);

	tmpTopic->topicID = id;
	tmpTopic->topicName = name;
	tmpTopic->topicText = text;
	tmpTopic->topicType = type;
	tmpTopic->children = childTopics;
	tmpTopic->parent = TopicParent;
	tmpTopic->urlString = url;

	return tmpTopic;
}

void UDialogue_Topic::AddChild(UDialogue_Topic * childToAdd)
{
	if (!childToAdd)
		return;

	this->children.Add(childToAdd);

	return;
}
