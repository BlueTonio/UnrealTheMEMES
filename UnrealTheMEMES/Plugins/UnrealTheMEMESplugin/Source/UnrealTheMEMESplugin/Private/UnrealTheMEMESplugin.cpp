// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealTheMEMESplugin.h"
#include "UnrealTheMEMESpluginStyle.h"
#include "UnrealTheMEMESpluginCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName UnrealTheMEMESpluginTabName("UnrealTheMEMESplugin");

#define LOCTEXT_NAMESPACE "FUnrealTheMEMESpluginModule"

void FUnrealTheMEMESpluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FUnrealTheMEMESpluginStyle::Initialize();
	FUnrealTheMEMESpluginStyle::ReloadTextures();

	FUnrealTheMEMESpluginCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FUnrealTheMEMESpluginCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FUnrealTheMEMESpluginModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FUnrealTheMEMESpluginModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(UnrealTheMEMESpluginTabName, FOnSpawnTab::CreateRaw(this, &FUnrealTheMEMESpluginModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FUnrealTheMEMESpluginTabTitle", "UnrealTheMEMESplugin"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FUnrealTheMEMESpluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FUnrealTheMEMESpluginStyle::Shutdown();

	FUnrealTheMEMESpluginCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(UnrealTheMEMESpluginTabName);
}

TSharedRef<SDockTab> FUnrealTheMEMESpluginModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FUnrealTheMEMESpluginModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("UnrealTheMEMESplugin.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FUnrealTheMEMESpluginModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(UnrealTheMEMESpluginTabName);
}

void FUnrealTheMEMESpluginModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FUnrealTheMEMESpluginCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FUnrealTheMEMESpluginCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

bool FUnrealTheMEMESpluginModule::Exec(UWorld* World, const TCHAR* Cmd, FOutputDevice& Ar)
{
	if (FParse::Command(&Cmd, TEXT("UnrealSurvery"))) {
		const TSharedRef<FGlobalTabmanager>& TabManager = FGlobalTabmanager::Get();
		TabManager->TryInvokeTab(UnrealTheMEMESpluginTabName);
		return true;
	}
	return false;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUnrealTheMEMESpluginModule, UnrealTheMEMESplugin)