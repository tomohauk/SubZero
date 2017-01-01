//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.

#include "SubZero.h"
#include "Runtime/UMG/Public/Components/ComboBoxString.h"
#include "Dialogue_Database.h"

void UDialogue_Database::CreateTopic(FText name, FText text, ETopicType type, TArray<UDialogue_Topic *> childTopics, UDialogue_Topic * TopicParent, FString urlString)
{
	int id = this->topics.Num() + 1;

	UDialogue_Topic * tmpTopic = UDialogue_Topic::CreateTopic(this, id, name, text, type, childTopics, TopicParent, urlString);

	if (!tmpTopic)
		return;

	this->topics.Add(tmpTopic);

	tmpTopic = nullptr;
}

void UDialogue_Database::AddTopic(UDialogue_Topic * inTopic)
{
	topics.Add(inTopic);
}

UDialogue_Topic * UDialogue_Database::GetRandomGreeting()
{
	if (this->topics.Num() <= 0)
		return nullptr;

	TArray<UDialogue_Topic *> tmpGreetings;

	for (UDialogue_Topic * topic : this->topics)
	{
		if (topic->topicType == ETopicType::TT_Greeting)
		{
			tmpGreetings.Add(topic);
		}
	}

	int randomIndex = FMath::RandRange(0, tmpGreetings.Num()-1);

	return tmpGreetings.Num() <= 0 ? nullptr : tmpGreetings[randomIndex];
}

UDialogue_Topic * UDialogue_Database::GetTopicByID(int id)
{
	UDialogue_Topic * retTopic = nullptr;

	for (UDialogue_Topic * topic : topics)
	{
		if (topic->topicID == id)
		{
			retTopic = topic;
		}
		else//Search children
		{
			for (UDialogue_Topic * child : topic->children)
			{
				if (child->topicID == id)
				{
					retTopic = child;
				}
			}
		}
	}
	return retTopic;
}

TArray<UDialogue_Topic * > UDialogue_Database::GetTopics()
{
	if (topics.Num() <= 0)
	{
		TArray<UDialogue_Topic*> tmpChild;
		CreateTopic(FText::FromString("NULL"), FText::FromString("NULL"), ETopicType::TT_General, tmpChild , nullptr, "None");
	}

	return this->topics;
}

TArray<UDialogue_Topic*> UDialogue_Database::GetTopicsOfType(ETopicType topicType)
{
	TArray<UDialogue_Topic *> typeTopics;

	for (UDialogue_Topic * topic : topics)
	{
		if (topic->topicType == topicType)
		{
			typeTopics.Add(topic);
		}
	}

	return typeTopics;
}

TArray<FString> UDialogue_Database::GetTopicsOfTypeStr(ETopicType topicType)
{
	TArray<UDialogue_Topic*> topicArray = GetTopicsOfType(topicType);
	TArray<FString> topicsStr;

	for (UDialogue_Topic * t : topicArray)
	{
		topicsStr.Add(t->topicName.ToString());
	}

	return topicsStr;
}

UDialogue_Topic * UDialogue_Database::GetTopicByName(FText topicName)
{
	UDialogue_Topic * tmpTopic = nullptr;

	for (UDialogue_Topic * sTopic : topics)
	{
		if (sTopic->topicName.EqualTo(topicName))
		{
			tmpTopic = sTopic;
		}
		else if(sTopic->children.Num() > 0)
		{
			for (UDialogue_Topic * sCTopic : sTopic->children)
			{
				if (sCTopic->topicName.EqualTo(topicName))
				{
					tmpTopic = sCTopic;
				}
			}
		}
		else
		{
			tmpTopic = nullptr;
		}
	}

	return tmpTopic;
}

void UDialogue_Database::BreakTopic(UDialogue_Topic* InTopic, int& topicID, FText& topicName, FText& topicText, ETopicType& topicType, TArray<UDialogue_Topic*>& topicChildren, UDialogue_Topic*& parentTopic, FString& URLString)
{
	if (!IsValid(InTopic))
		return;

	topicID = InTopic->topicID;
	topicName = InTopic->topicName;
	topicText = InTopic->topicText;
	topicType = InTopic->topicType;
	topicChildren = InTopic->children;
	parentTopic = InTopic->parent;
	URLString = InTopic->urlString;
}

void UDialogue_Database::CreateMenu(UComboBoxString * inComboBox, TArray<FString> menuItems)
{
	if (IsValid(inComboBox))
	{
		inComboBox->ClearOptions();

		TArray<FString> items = GetTopicsOfTypeStr(ETopicType::TT_Category);

		for (auto item : items)
		{
			inComboBox->AddOption(item);
		}

		inComboBox->AddOption(GetGoodByeTopic());
	}
}

void UDialogue_Database::CreateMenuFromChild(class UComboBoxString * inComboBox, UDialogue_Topic * inTopic)
{
	if (IsValid(inComboBox) && IsValid(inTopic))
	{
		inComboBox->ClearOptions();
		
		if (inTopic->children.Num() <= 0)
		{
			inComboBox->AddOption(GetGoodByeTopic());
			return;
		}

		if (inTopic->topicType != ETopicType::TT_Category)
		{
			inComboBox->AddOption(GetGoodByeTopic());
			return;
		}
	
		for (UDialogue_Topic * t : inTopic->children)
		{
			inComboBox->AddOption(t->topicName.ToString());
		}

	}
}

UDialogue_Topic * UDialogue_Database::GetMenuSelection(FString inOptionName)
{
	TArray<UDialogue_Topic*> tmpTopics = GetAllTopics();
	UDialogue_Topic * tmpTopic = nullptr;

	for (UDialogue_Topic * t : tmpTopics)
	{
		if (t->topicName.EqualTo(FText::FromString(inOptionName)))
		{
			tmpTopic = t;
		}
	}

	return tmpTopic;
}

TArray<UDialogue_Topic*> UDialogue_Database::GetAllTopics()
{
	TArray<UDialogue_Topic*> allTopics;

	for (UDialogue_Topic * t : topics)
	{
		allTopics.Add(t);

		for (UDialogue_Topic * tC : t->children)
		{
			allTopics.Add(tC);

			if (tC->children.Num() > 0)
			{
				ReadTopic(tC, allTopics);
			}
		}
	}

	return allTopics;
}

void UDialogue_Database::ReadTopic( UDialogue_Topic * inTopic, TArray<UDialogue_Topic*> & inArray)
{
	for (UDialogue_Topic * t : inTopic->children)
	{
		inArray.Add(t);

		if (t->children.Num() > 0)
		{
			ReadTopic(t, inArray);
		}
	}
}
