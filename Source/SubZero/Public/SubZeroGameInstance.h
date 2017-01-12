// Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.www.darkrisingstudios.com

#pragma once

#include "Engine/GameInstance.h"
#include "SubZeroGameInstance.generated.h"

/**
 * This class is used to store data through things
 * like level transitioning.
 */
UCLASS()
class SUBZERO_API USubZeroGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

		//This retreives the current game instance for the active game session.
		static USubZeroGameInstance * GetInstance(UWorld * world);

private:
		//The actual instance
		static USubZeroGameInstance * _instance;
};
