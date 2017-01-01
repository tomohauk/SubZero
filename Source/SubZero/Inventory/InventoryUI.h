// Copyright 2017 (c) Dark Rising Studioshttp://www.darkrisingstudios.com

#pragma once

#include "Blueprint/UserWidget.h"
#include "InventoryUI.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class SUBZERO_API UInventoryUI : public UUserWidget
{
	GENERATED_BODY()

public:
		UInventoryUI(const class FObjectInitializer& ObjectInitializer);

		UFUNCTION(BlueprintImplementableEvent, Category = "Inventory", DisplayName = "Open Inventory")
		void ShowInventory(class UInventory * inventory);

		//If the inventory is open or not.
		bool bIsInventoryOpen;
	
		UFUNCTION(BlueprintCallable, Category = "Inventory", DisplayName = "Close Inventory")
		void CloseInventory(class ASubZeroCharacter * player);

		UFUNCTION(BlueprintCallable, Category = "Inventory", DisplayName = "Create Inventory List")
		void CreateInventoryList(TArray<class AItem*> itemList, APlayerController * inPlayerController, UClass * inClass, UScrollBox * inScrollbox, UCanvasPanel * inCanvasPanel);
	
		/* Inventory Commands to link inventory UI to call C++ functions
		0 = Close Inventory
		*/
};
