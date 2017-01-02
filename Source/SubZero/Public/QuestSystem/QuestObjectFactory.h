// opyright 2017 (c) Dark Rising Studios. http://Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.www.darkrisingstudios.com

#pragma once

#include "UnrealEd.h"
#include "Factories/Factory.h"
#include "QuestObjectFactory.generated.h"

#define LOG(msg, ...) UE_LOG(LogTemp, Warning, TEXT(msg), __VA_ARGS__)

/**
 * This factory creates the quest asset type 
 * From .xml files in the Quest directory
 */
UCLASS()
class SUBZERO_API UQuestObjectFactory : public UFactory
{
	GENERATED_UCLASS_BODY()
	
public:

	//UFactory interface
	virtual UObject * FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;	
	
	virtual UObject * FactoryCreateText(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const TCHAR*& Buffer, const TCHAR* BufferEnd, FFeedbackContext* Warn) override;

	virtual bool DoesSupportClass(UClass* Class) override;

	virtual bool FactoryCanImport(const FString& Filename) override;

	virtual FText GetDisplayName() const override;

};
