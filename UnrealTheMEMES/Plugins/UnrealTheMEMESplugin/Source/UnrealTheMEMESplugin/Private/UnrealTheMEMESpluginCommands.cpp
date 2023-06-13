// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealTheMEMESpluginCommands.h"

#define LOCTEXT_NAMESPACE "FUnrealTheMEMESpluginModule"

void FUnrealTheMEMESpluginCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "UnrealTheMEMESplugin", "Bring up UnrealTheMEMESplugin window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
