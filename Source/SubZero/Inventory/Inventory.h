//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.

#pragma once

#include "Object.h"
#include "../Item.h"
#include "Inventory.generated.h"

/**
 * 
 */
UCLASS()
class SUBZERO_API UInventory : public UObject
{
	GENERATED_BODY()
	
public:

	typedef void (UInventory::*FunctionPtrType)(void);

	FunctionPtrType funcs[1];

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void initFuncs();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void testFunc();

	UFUNCTION(BlueprintCallable, DisplayName = "Run Funcs", Category = "Inventory")
	void runFuncs();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Inventory Items", Category = "Inventory")
	TArray<AItem*> inventoryItems;

	UFUNCTION(BlueprintCallable, DisplayName = "Add Inventory Itme", Category = "Inventory")
	void AddItem(AItem * itemToAdd);	

	UFUNCTION(BlueprintCallable, DisplayName = "Pickup Item", Category = "Inventory")
	void PickupItem(AItem * itemToPickup);

	UFUNCTION(BlueprintCallable, DisplayName = "Drop Item", Category = "Inventory")
	void DropItem(class ASubZeroCharacter * owningPlayer,  AItem * itemToDrop);

	//Get all items of EItemType
	UFUNCTION(BlueprintPure, Category = "Inventory", DisplayName = "Get Items of Type")
	void GetItemsOfType(EItemType type, TArray<class AItem*>& outItems);

	//Finds an item in the inventory by name
	UFUNCTION(BlueprintPure, Category = "Inventory", DisplayName = "Get Item by Name")
	AItem * FindItemByName(FString itemName);
};
