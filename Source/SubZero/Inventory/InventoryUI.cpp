// Copyright 2017 (c) Dark Rising Studios. http://www.darkrisingstudios.com

#include "SubZero.h"
#include "SubZeroCharacter.h"
#include "InventoryUI.h"




UInventoryUI::UInventoryUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bIsInventoryOpen = false;
}

void UInventoryUI::CloseInventory(ASubZeroCharacter * player)
{
	if (!bIsInventoryOpen)
		return;
	
	player->ToggleInventory();
}

void UInventoryUI::CreateInventoryList(TArray<AItem*> itemList, APlayerController * inPlayerController, UClass * inClass, UScrollBox * inScrollbox, UCanvasPanel * inCanvasPanel)
{
	if (itemList.Num() <= 0)
		return;

// 	for (AItem * item : itemList)
// 	{
// 		UUserWidget * tmpWidget = CreateWidget<UUserWidget>(inPlayerController, inClass::StaticClass());
// 	}
}
