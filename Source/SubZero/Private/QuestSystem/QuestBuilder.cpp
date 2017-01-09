// Copyright 2017 (c) Dark Rising Studios. http://www.darkrisingstudios.com

#include "SubZero.h"
#include "Paths.h"
#include "Runtime/XmlParser/Public/XmlParser.h"
#include "Runtime/Core/Public/HAL/FileManagerGeneric.h"
#include "QuestBuilder.h"
#include "QuestConditionSystem.h"

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
	TArray<FCommands*> Commands;
};

struct FQuest
{
	FString QuestID;
	FString QuestName;
	TArray<FString> QuestConditions;
	TArray<FQuestStages*> QuestStages;
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

		tmpNewQuest->QuestID = file->GetRootNode()->GetAttribute("id");
		tmpNewQuest->QuestName = file->GetRootNode()->GetAttribute("name");

		//Reads the quest nodes inside the <Quest> tag
		for (FXmlNode * node : file->GetRootNode()->GetChildrenNodes())
		{
			
			if (node->GetTag().Equals("Conditions"))
			{
				//Read 'Conditions' nodes
				UQuestConditionSystem::BuildConditionString(tmpNewQuest->QuestConditions, node);
			}
			else if (node->GetTag().Equals("Stage"))
			{
				Internal_ReadQuestStage(tmpNewQuest->QuestStages, node);
			}
			else
			{

			}
		}

		//Add new quest to quest db

		/* BEGINE TESTING READING QUEST - REMOVE AFTER TESTING */
		UE_LOG(LogTemp, Warning, TEXT("Quest Id: %s \n Quest Name: %s"), *tmpNewQuest->QuestID, *tmpNewQuest->QuestName);
		
		for (FString con : tmpNewQuest->QuestConditions)
		{
			UE_LOG(LogTemp, Warning, TEXT("Condition: %s"), *con);
		}

		for (FQuestStages * qs : tmpNewQuest->QuestStages)
		{
			UE_LOG(LogTemp, Warning, TEXT("Stage Id: %i \n Stage Name: %s"), qs->StageId, *qs->StageName);
		}
		/* END TESTING */
	}
}

void UQuestBuilder::Internal_ReadQuestStage(TArray<struct FQuestStages*> & outStages, FXmlNode * inNode)
{
	if (!inNode->GetTag().Equals("Stage"))
	{
		//Not a quest stage
		return;
	}

	FQuestStages * tmpQuestStage = new FQuestStages;

	tmpQuestStage->StageId = FCString::Atoi(*inNode->GetAttribute("id"));
	tmpQuestStage->StageName = inNode->GetAttribute("name");

	for (FXmlNode * children : inNode->GetChildrenNodes())
	{
		if (children->GetTag().Equals("Dialogue"))
		{
			for (FXmlNode * dialogueNode : children->GetChildrenNodes())
			{
				//read dialogue nodes
			}
		}
		else if (children->GetTag().Equals("Commands"))
		{
			for (FXmlNode * cmdNode : children->GetChildrenNodes())
			{
				FCommands * newCmd = new FCommands;
				newCmd->CommandString = cmdNode->GetAttribute("cmdString");

				for (FXmlNode * cmdConditions : cmdNode->GetChildrenNodes())
				{
					UQuestConditionSystem::BuildConditionString(newCmd->Conditions, cmdConditions);
				}

				tmpQuestStage->Commands.Add(newCmd);
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Unknown Quest Stage Node"));
		}
	}

	outStages.Add(tmpQuestStage);

	return;
}
