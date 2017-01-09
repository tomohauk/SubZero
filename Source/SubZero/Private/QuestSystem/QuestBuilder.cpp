// Copyright 2017 (c) Dark Rising Studios. http://www.darkrisingstudios.com

#include "SubZero.h"
#include "Paths.h"
#include "Runtime/XmlParser/Public/XmlParser.h"
#include "Runtime/Core/Public/HAL/FileManagerGeneric.h"
#include "QuestBuilder.h"

UQuestBuilder::UQuestBuilder(const class FObjectInitializer & objectInitializer)
{
	QuestDirPath = "Quests/";
}

void UQuestBuilder::InitiateQuestBuilder()
{
	ReadQuestDir(QuestXMLFiles);
}

FString UQuestBuilder::GetQuestDirPath()
{
	//Formats and returns the absolute Quests Directory Path
	FString path = FPaths::GameContentDir() + QuestDirPath;

	return path;
}

void UQuestBuilder::ReadQuestDir(TArray<FXmlFile*> & outFiles)
{
	if (!FPaths::DirectoryExists(GetQuestDirPath()))
		return;

	FString QuestPath = GetQuestDirPath();

	FString fileExtension = ".xml";

	//Normalize the / and \ 
	FPaths::NormalizeDirectoryName(QuestPath);

	//Get the file manager by reference
	IFileManager & fileManager = IFileManager::Get();

	FString FinalPath = QuestPath + "/";

	//Generic file paths of every xml file in Quests folder
	TArray<FString> files;

	UE_LOG(LogTemp, Warning, TEXT("Path: %s"), *FinalPath);

	//Find all the files and store the path to the files
	fileManager.FindFiles(files, *FinalPath, TEXT(".xml"));
	for (FString strFile : files)//Iterate and read the xml files
	{
		if (!FPaths::FileExists(FinalPath + strFile))
			return;

		UE_LOG(LogTemp, Warning, TEXT("Path: %s"), *(FinalPath + strFile));

		FXmlFile * xmlFile = new FXmlFile(FinalPath + strFile, EConstructMethod::ConstructFromFile);

		if (xmlFile->IsValid() && xmlFile->GetRootNode()->GetTag().Equals("Quest"))
		{
			outFiles.Add(xmlFile);
			UE_LOG(LogTemp, Warning, TEXT("xmlFile is valid!"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("xmlFile is not valid!"));
			return;
		}
	}
}

struct FCommands
{
	FString CommandString;
	TArray<FString> Conditions;
};

struct FQuestStages
{
	int32 StageId;
	FString StageName;
	TArray<FString> Dialogue;
	TArray<FCommands> Commands;
};

struct FQuest
{
	FString QuestID;
	FString QuestName;
	TArray<FString> QuestConditions;
	TArray<FQuestStages> QuestStages;
};

void UQuestBuilder::CreateQuests()
{
	UE_LOG(LogTemp, Warning, TEXT("In Create Quests!"));
	UE_LOG(LogTemp, Warning, TEXT("Number of xml files: %s"), *FString::FromInt(QuestXMLFiles.Num()));
	for (FXmlFile * file : QuestXMLFiles)
	{
		//Make sure this is a quest file
		if (!file->GetRootNode()->GetTag().Equals("Quest"))
		{
			UE_LOG(LogTemp, Warning, TEXT("Not a quest file!"));
			return;
		}

		FQuest * tmpNewQuest = new FQuest;

		//Reads the quest nodes inside the <Quest> tag
		for (FXmlNode * node : file->GetRootNode()->GetChildrenNodes())
		{
			if (node->GetTag().Equals("Conditions"))
			{
				for (FXmlNode * conditionNodes : node->GetChildrenNodes())
				{
					UE_LOG(LogTemp, Warning, TEXT("In XML Conditions"));
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

					UE_LOG(LogTemp, Warning, TEXT("%s"), *conditionStr);
				}
			}
			else if (node->GetTag().Equals("Stage"))
			{

			}
			else
			{

			}
		}
	}
}

void UQuestBuilder::Internal_ReadQuestConditions()
{

}

void UQuestBuilder::Internal_ReadQuestStage()
{

}
