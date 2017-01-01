//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.

#include "SubZero.h"
#include "NPC.h"


// Sets default values
ANPC::ANPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	
	UDialogue_Database * tmp = NewObject<UDialogue_Database>();

	if (IsValid(tmp))
	{
		dialogueDB = tmp;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Black, "Not Valid!");
	}

	TArray<UDialogue_Topic*> dialogueTopics = ReadXML(xmlPath);
	
	for (auto topic : dialogueTopics)
	{
		dialogueDB->AddTopic(topic);
	}
	
}

// Called every frame
void ANPC::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

TArray<UDialogue_Topic*> ANPC::ReadXML(FString inXmlPath)
{
	TArray<UDialogue_Topic*> topicFromFileArray;

	if (!IsValidXML(inXmlPath))
		return topicFromFileArray;

	xmlFile = new FXmlFile();
	xmlFile->LoadFile(FPaths::GameContentDir() + inXmlPath);


	if (xmlFile->IsValid())
	{
		FXmlNode * rootDatabaseNode = xmlFile->GetRootNode();
		TArray<FXmlNode*> topicNodes = rootDatabaseNode->GetChildrenNodes();

		for (FXmlNode * topics : topicNodes)
		{
			topicFromFileArray.Add(readTopic(topics));
		}
	}

	return topicFromFileArray;
}

bool ANPC::IsValidXML(FString inPath)
{
	FString path = FPaths::GameContentDir() + inPath;

	if (FPaths::FileExists(path) && FPaths::GetExtension(path).Equals("xml"))
		return true;
	else
		return false;
}

UDialogue_Topic * ANPC::readTopic(FXmlNode * inNode)
{
	int tId = FCString::Atoi(*inNode->GetAttribute("id"));
	FText tName = FText::FromString(inNode->GetChildrenNodes()[0]->GetAttribute("str"));
	FText tText = FText::FromString(inNode->GetChildrenNodes()[1]->GetContent());

	const FString & enumName = "ETopicType";

	UEnum * eType = FindObject<UEnum>(ANY_PACKAGE, *enumName, true);
	ETopicType tType = (ETopicType)eType->FindEnumIndex(FName(*inNode->GetAttribute("Type")));

	TArray<UDialogue_Topic*> tChildren;

	int numChildren = FCString::Atoi(*inNode->GetChildrenNodes()[2]->GetAttribute("num"));
	if (numChildren > 0)
	{

		TArray<FXmlNode*> childTopicsFile = inNode->GetChildrenNodes()[2]->GetChildrenNodes();

		for (FXmlNode * node : childTopicsFile)
		{
			tChildren.Add(readTopic(node));
		}
	}

	UDialogue_Topic * tParent = nullptr;

	FString tUrl = inNode->GetChildrenNodes()[4]->GetAttribute("str");

	return UDialogue_Topic::CreateTopic(this, tId, tName, tText, tType, tChildren, tParent, tUrl);
}

