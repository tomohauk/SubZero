// Copyright 2017 (c) Dark Rising Studios. http://Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.www.darkrisingstudios.com

#include "SubZero.h"
#include "QuestObjectFactory.h"
#include "Quest.h"
#include "XmlParser.h"

#define LOCTEXT_NAMESPACE "QuestFactory"

UQuestObjectFactory::UQuestObjectFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bCreateNew = false;
	bText = true;
	bEditAfterNew = true;
	bEditorImport = true;

	Formats.Add("xml;XML Files");

	SupportedClass = UQuest::StaticClass();
}
UObject * UQuestObjectFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	UQuest * NewQuestObject = NewObject<UQuest>(InParent, InClass, InName, Flags);
	return NewQuestObject;
}

UObject * UQuestObjectFactory::FactoryCreateText(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const TCHAR*& Buffer, const TCHAR* BufferEnd, FFeedbackContext* Warn)
{
	FXmlFile * tmpFile = new FXmlFile();
		
	FString NewBuffer(BufferEnd - Buffer, Buffer);
	
	tmpFile->LoadFile(NewBuffer, EConstructMethod::ConstructFromBuffer);

	if (!tmpFile->IsValid())
	{
		LOG("InValid")
	}

	FString RootNode = tmpFile->GetRootNode()->GetTag();

	//If the root node is not 'Quest', it's not a quest files
	if (!RootNode.Equals("Quest"))
		return nullptr;

	//Get number of conditions;
	int32 ConditionCount;
	
	//Number of Stages
	int32 StageCount;

	TArray<FXmlNode*> nodes;

	for (FXmlNode * node : tmpFile->GetRootNode()->GetChildrenNodes())
	{
		if (node->GetTag().Equals("Conditions"))
		{
			ConditionCount = node->GetChildrenNodes().Num();
		}
		else if (node->GetTag().Equals("Stage"))
		{
			StageCount = node->GetChildrenNodes().Num();
		}
		else
		{

		}
	}

	UQuest * NewQuestObject = NewObject<UQuest>(InParent, InClass, InName, Flags);

	NewQuestObject->iConditionCount = ConditionCount;
	NewQuestObject->iStageCount = StageCount;

	return NewQuestObject;
}

bool UQuestObjectFactory::DoesSupportClass(UClass* Class)
{
	return false;
}

bool UQuestObjectFactory::FactoryCanImport(const FString& Filename)
{
	return false;
}

FText UQuestObjectFactory::GetDisplayName() const
{
	return FText::FromString("Quest");
}

#undef LOCTEXT_NAMESPACE
