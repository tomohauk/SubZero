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

	FString fileExtension = ".xml";

	//Normalize the / and \ 
	FPaths::NormalizeDirectoryName(QuestDirPath);

	//Get the file manager by reference
	IFileManager & fileManager = IFileManager::Get();

	FString FinalPath = QuestDirPath + "/" + fileExtension;

	//Generic file paths of every xml file in Quests folder
	TArray<FString> files;

	//Find all the files and store the path to the files
	fileManager.FindFiles(files, *FinalPath, true, false);

	for (FString strFile : files)//Iterate and read the xml files
	{
		if (!FPaths::FileExists(strFile))
			return;

		FXmlFile * xmlFile = new FXmlFile(strFile, EConstructMethod::ConstructFromFile);

		if (xmlFile->IsValid())
		{
			outFiles.Add(xmlFile);
		}
		else
		{
			return;
		}
	}
}


struct FQuestConditions
{
};

struct FQuestStages
{
};

struct FQuest
{
	FString QuestID;
	FString QuestName;
	TArray<FQuestConditions> QuestWinConditions;
	TArray<FQuestStages> QuestStages;
};

void UQuestBuilder::CreateQuests()
{
	for (FXmlFile * file : QuestXMLFiles)
	{
		// file->GetRootNode()->
	}
}

void UQuestBuilder::Internal_ReadQuestConditions()
{

}

void UQuestBuilder::Internal_ReadQuestStage()
{

}
