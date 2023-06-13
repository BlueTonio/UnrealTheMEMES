// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealTheMEMESpluginStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FUnrealTheMEMESpluginStyle::StyleInstance = nullptr;

void FUnrealTheMEMESpluginStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FUnrealTheMEMESpluginStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FUnrealTheMEMESpluginStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("UnrealTheMEMESpluginStyle"));
	return StyleSetName;
}

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FUnrealTheMEMESpluginStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("UnrealTheMEMESpluginStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("UnrealTheMEMESplugin")->GetBaseDir() / TEXT("Resources"));

	Style->Set("UnrealTheMEMESplugin.OpenPluginWindow", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));

	return Style;
}

void FUnrealTheMEMESpluginStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FUnrealTheMEMESpluginStyle::Get()
{
	return *StyleInstance;
}
