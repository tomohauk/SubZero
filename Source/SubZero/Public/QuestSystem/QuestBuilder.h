// Copyright 2017 (c) Dark Rising Studios. http://www.darkrisingstudios.com

#pragma once

#include "Object.h"
#include "QuestBuilder.generated.h"

/*
* The Quest Builder will read all of the quest xml files
* and construct them in the Quest Database and add dialogue
* to the npcs dialogue database and other quest data to
* various other systems.
*/
class UQuest;

UCLASS()
class SUBZERO_API UQuestBuilder : public UObject
{
	GENERATED_BODY()
	
public:

	//ctor
	UQuestBuilder(const class FObjectInitializer & objectInitializer);

	//Initiates the Quest Builder and reads all the Quest Files into memory.
	UFUNCTION(BlueprintCallable, Category = "Quest System | Quest Builder", DisplayName = "Initiate Quest Builder")
	void InitiateQuestBuilder();
	
public: /* XML Functions and vars*/

	//The path of the quest directory
	FString QuestDirPath;

	//Gets the formated quest directory path
	FString GetQuestDirPath();

	//Reads all the xml file in the Quest Directory
	void ReadQuestDir(TArray<class FXmlFile*> & outFiles );

	//All quest xml files in Quest Directory
	TArray<FXmlFile *> QuestXMLFiles;

	//Reads through all of the XML files in QuestXMLFiles array
	void CreateQuests();

	//Internal Read Quest Conditions
	void Internal_ReadQuestConditions();
	//Internal Read Quest Stage
	void Internal_ReadQuestStage();
};
