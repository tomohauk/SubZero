// Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.www.darkrisingstudios.com

#include "SubZero.h"
#include "SubZeroGameInstance.h"

USubZeroGameInstance * USubZeroGameInstance::_instance = nullptr;

USubZeroGameInstance * USubZeroGameInstance::GetInstance(UWorld * world)
{
	UGameInstance * gameInstance = world->GetGameInstance();

	//Check if gameInstance is not valid
	if (!IsValid(gameInstance))
	{
		return nullptr;
	}

	//Checks if _instance has already been initialized from UGameInstance
	if (_instance != nullptr)
	{
		return _instance;
	}
	else
	{
		//Cast the gameInstance to USubZeroGameInstance
		USubZeroGameInstance * tmpInst = Cast<USubZeroGameInstance>(gameInstance);

		//Check if tmpInst is valid
		if (!IsValid(tmpInst))
		{
			return nullptr;
		}

		_instance = tmpInst;

		//garbage cleanup
		tmpInst->ConditionalBeginDestroy();
		tmpInst = nullptr;
	}

	return _instance;
}
