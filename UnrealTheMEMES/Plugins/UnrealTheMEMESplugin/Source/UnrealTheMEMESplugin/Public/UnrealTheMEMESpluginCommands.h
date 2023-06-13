// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "UnrealTheMEMESpluginStyle.h"

class FUnrealTheMEMESpluginCommands : public TCommands<FUnrealTheMEMESpluginCommands>
{
public:

	FUnrealTheMEMESpluginCommands()
		: TCommands<FUnrealTheMEMESpluginCommands>(TEXT("UnrealTheMEMESplugin"), NSLOCTEXT("Contexts", "UnrealTheMEMESplugin", "UnrealTheMEMESplugin Plugin"), NAME_None, FUnrealTheMEMESpluginStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};