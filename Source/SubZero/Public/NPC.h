//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.

#pragma once

#include "GameFramework/Character.h"
#include "Dialogue_Database.h"
#include "Paths.h"
#include "Runtime/XmlParser/Public/XmlParser.h"
#include "NPC.generated.h"

UCLASS()
class SUBZERO_API ANPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPC();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	//Interaction called from the player
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "Interact", Category = "NPC")
	void Interact(ACharacter * callingPlayer);
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, DisplayName = "Dialogue Database", Category = "Dialogue")
	UDialogue_Database * dialogueDB;


	/*XML reading*/

	//The Dialogue XML file
	UPROPERTY(BlueprintReadWrite, EditAnywhere, DisplayName = "Dialogue XML File", Category = "Dialogue", meta = (xmlPath = "none"))
	FString xmlPath;

	//XML actual file
	FXmlFile * xmlFile;

	//Reads the XML file
	UFUNCTION(BlueprintCallable, DisplayName = "Read XML File", Category = "Dialogue|XML")
	TArray<UDialogue_Topic*> ReadXML(FString inXmlPath);

	//Is valid xml file
	UFUNCTION(BlueprintCallable, DisplayName = "Is Valid XML file", Category = "Dialogue|XML")
	bool IsValidXML(FString inPath);

	//Reads a topic from xml
	UDialogue_Topic * readTopic(FXmlNode * inNode);
};
