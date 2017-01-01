//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.

#include "SubZero.h"
#include "SubZeroCharacter.h"
#include "Inventory.h"

void UInventory::initFuncs()
{
	funcs[0] = &UInventory::testFunc;
}

void UInventory::testFunc()
{
	PRINTSTRING("In testFunc");
}

void UInventory::runFuncs()
{
	for (FunctionPtrType func : funcs)
	{
		(this->*(funcs[0]))();
	}
}

void UInventory::AddItem(AItem * itemToAdd)
{
	if (!IsValid(itemToAdd))
	{
		PRINTSTRING("Is Not Valid!");
		return;
	}

	inventoryItems.Add(itemToAdd);
}

void UInventory::PickupItem(AItem * itemToPickup)
{
	FActorSpawnParameters spawnParams;
	spawnParams.Template = itemToPickup;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	//spawnParams.Name = itemToPickup->itemName;

	AItem * newItem = NewObject<AItem>(this, FName(*itemToPickup->itemName), RF_NoFlags, itemToPickup);

	AddItem(newItem);

	itemToPickup->Destroy();
}

void UInventory::DropItem(class ASubZeroCharacter * owningPlayer, AItem * itemToDrop)
{
	if (!IsValid(itemToDrop))
		return;

	FVector itemLoc = owningPlayer->GetActorLocation() + (owningPlayer->GetActorForwardVector() * 200);
	FRotator itemRot = itemToDrop->GetActorRotation();
	FActorSpawnParameters spawnP;
	spawnP.Instigator = owningPlayer;
	spawnP.Template = itemToDrop;
	spawnP.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AItem * spawnedItem = owningPlayer->GetWorld()->SpawnActor<AItem>(AItem::StaticClass(), itemLoc, itemRot, spawnP);

	if (IsValid(spawnedItem))
	{
		spawnedItem->SetActorLocation(itemLoc);
		PRINTSTRING("spawnedItem Valid!");
		//spawnedItem->StaticMesh->Com
		inventoryItems.Remove(itemToDrop);
	}
}

void UInventory::GetItemsOfType(EItemType type, TArray<class AItem*>& outItems)
{
	if (inventoryItems.Num() <= 0)
		return;

	for (AItem * invItem : inventoryItems)
	{
		if (invItem->itemType == type)
		{
			outItems.Add(invItem);
		}
	}
}

AItem * UInventory::FindItemByName(FString itemName)
{
	for (AItem * item : inventoryItems)
	{
		if (item->itemName == itemName)
		{
			return item;
		}
	}

	return nullptr;
}


