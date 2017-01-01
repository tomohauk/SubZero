//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.

#pragma once

#include "SlateBasics.h"

/**  */
class FQuestSystemStyle
{
public:

	static void Initialize();

	static void Shutdown();

	/** reloads textures used by slate renderer */
	static void ReloadTextures();

	/** @return The Slate style set for the Shooter game */
	static const ISlateStyle& Get();

	static FName GetStyleSetName();

private:

	static TSharedRef< class FSlateStyleSet > Create();

private:

	static TSharedPtr< class FSlateStyleSet > StyleInstance;
};