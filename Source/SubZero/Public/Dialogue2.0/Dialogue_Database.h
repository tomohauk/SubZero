//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.

#pragma once

#include "Object.h"
#include "Dialogue_Topic.h"
#include "Dialogue_Database.generated.h"

/**
 * Dialogue Database is a per NPC object, that stores
 * all the dialogue topics that this NPC has to offer to
 * the player.
 */

UCLASS(Blueprintable)
class SUBZERO_API UDialogue_Database : public UObject
{
	GENERATED_BODY()
	
private:
	//The array of topics for this database
	UPROPERTY(DisplayName = "Topics")
	TArray<UDialogue_Topic*> topics;

public:
	//Creates a new topic and adds it to the 'topics' array.
	UFUNCTION(BlueprintCallable, meta=(AutoCreateRefTerm = "childTopics"), DisplayName = "Create Topic", Category = "Dialogue")
	void CreateTopic(FText name, FText text, ETopicType type, TArray<UDialogue_Topic *> childTopics, UDialogue_Topic * TopicParent = nullptr, FString urlString = "None");
	
	//Adds in a topic into the topic database
	UFUNCTION(BlueprintCallable, DisplayName = "Add Topic", Category = "Dialogue|Topic")
	void AddTopic(UDialogue_Topic * inTopic);

	//Gets a random greeting from the topics array
	UFUNCTION(BlueprintPure, DisplayName = "Get Random Greeting", Category = "Dialogue|Topic")
	UDialogue_Topic * GetRandomGreeting();
	
	//Get topic by id
	UFUNCTION(BlueprintCallable, DisplayName = "Get Topic by ID", Category = "Dialogue|Topic")
	UDialogue_Topic * GetTopicByID(int id);

	//Get the topics in this Database
	UFUNCTION(BlueprintCallable, DisplayName = "Get Topics", Category = "Dialogue|Topic")
	TArray<UDialogue_Topic * > GetTopics();
	
	//Gets all the topics in this database of ETopicType. Does not search children
	UFUNCTION(BlueprintCallable, DisplayName = "Get Topics of Type", Category = "Dialogue|Topic")
	TArray<UDialogue_Topic * > GetTopicsOfType(ETopicType topicType);
	
	//Gets all topics in this database of ETopicTypes. Does not search children. Returns TArray<FString>
	UFUNCTION(BlueprintPure, DisplayName = "Get Topics of Type(String)", Category = "Dialogue|Topic")
	TArray<FString> GetTopicsOfTypeStr(ETopicType topicType);
	
	//Finds a topic by name, also searches child topics
	UFUNCTION(BlueprintCallable, DisplayName = "Get Topic By Name", Category = "Dialogue|Topic")
	UDialogue_Topic * GetTopicByName(FText topicName); 
	
	//Gets the number of topics in this database
	FORCEINLINE int Num() { return topics.Num(); }
	
	//Breaks the topic down
	UFUNCTION(BlueprintPure, Category = "Dialogue|Topic", meta = (NativeBreakFunc))
	static void BreakTopic(UDialogue_Topic* InTopic, int& topicID, FText& topicName, FText& topicText,ETopicType& topicType, TArray<UDialogue_Topic*>& topicChildren, UDialogue_Topic*& parentTopic, FString& URLString);
	
	//Creates a dialogue menu, using a select box widget item
	UFUNCTION(BlueprintCallable, DisplayName = "Create Menu", Category = "Dialogue", meta = (AutoCreateRefTerm = "menuItems"))
	void CreateMenu(class UComboBoxString * inComboBox, TArray<FString> menuItems);
	
	//Creates a dialogue menu, using a select box widget item
	UFUNCTION(BlueprintCallable, DisplayName = "Create Menu From Child", Category = "Dialogue")
	void CreateMenuFromChild(class UComboBoxString * inComboBox, UDialogue_Topic * inTopic);


	//Gets the topic from menu selection
	UFUNCTION(BlueprintPure, DisplayName = "Get Menu Selection", Category = "Dialogue")
	UDialogue_Topic * GetMenuSelection(FString inOptionName);

	//Gets all topics, including every child
	TArray<UDialogue_Topic*> GetAllTopics();

	//Read a topic
	void ReadTopic( UDialogue_Topic * inTopic, TArray<UDialogue_Topic*> & inArray );

	//Blueprint add Goodbye topic
	UFUNCTION(BlueprintPure, DisplayName = "Get GoodBye Topic", Category = "Dialogue")
	FORCEINLINE FString GetGoodByeTopic() { return "GoodBye!"; }
};
