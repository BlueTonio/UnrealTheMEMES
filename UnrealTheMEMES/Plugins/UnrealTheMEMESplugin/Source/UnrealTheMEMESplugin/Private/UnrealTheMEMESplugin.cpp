// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealTheMEMESplugin.h"
#include "UnrealTheMEMESpluginStyle.h"
#include "UnrealTheMEMESpluginCommands.h"
#include "Editor.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "PropertyCustomizationHelpers.h"
#include "Kismet/GameplayStatics.h"
//#include "Text3DActor.h"

static const FName UnrealTheMEMESpluginTabName("UnrealTheMEMESplugin");

#define LOCTEXT_NAMESPACE "FUnrealTheMEMESpluginModule"
#define COLOR_DARK_YELLOW 

void FUnrealTheMEMESpluginModule::StartupModule()
{
	TSharedRef<FExtender> Extender = MakeShared<FExtender>();
	Extender->AddToolBarExtension("Platforms", EExtensionHook::After, nullptr, FToolBarExtensionDelegate::CreateLambda([](FToolBarBuilder& Builder)
		{
			Builder.AddSeparator();
			Builder.AddToolBarButton(FUIAction(), NAME_None, FText::FromString("Ciao"));
		}));
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
	FMenuBarBuilder Builder( MakeShared<FUICommandList>());
	TSharedRef<SWidget> MenuSurvey = Builder.MakeWidget();
	

	const TSharedRef<FGlobalTabmanager>& TabManager = FGlobalTabmanager::Get();
	TabManager->RegisterNomadTabSpawner(UnrealTheMEMESpluginTabName, FOnSpawnTab::CreateLambda([MenuSurvey](const FSpawnTabArgs& SpawnTabArgs) -> TSharedRef<SDockTab> {
		FSlateFontInfo TextSizeInfo = FCoreStyle::Get().GetFontStyle("EmbossedText");
		FSlateFontInfo TextSizeButtonInfo = FCoreStyle::Get().GetFontStyle("EmbossedText");
		FTextBlockStyle TextBoxStyle = FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>("ButtonText"); //serve per settare la grandezza del testo dei bottoni
		
		TextSizeInfo.Size = 45.f;
		TextSizeButtonInfo.Size = 30.f;
		TextBoxStyle.SetFont(TextSizeButtonInfo);
		//FButtonStyle ButtonInfo;
		return SNew(SDockTab).TabRole(ETabRole::NomadTab)
			[
				SNew(SVerticalBox)      
				+ SVerticalBox::Slot().AutoHeight()               // slot rainbow scritta
			.HAlign(HAlign_Center)[
				SNew(STextBlock)
					.Text(LOCTEXT("Question", "Do you like UnrealEngine?"))
					.Font(TextSizeInfo)
					.ColorAndOpacity_Lambda([]() -> FSlateColor {
						float R = FMath::Sin(FPlatformTime::Seconds() + PI * 0.5f);
						float G = FMath::Sin(FPlatformTime::Seconds());
						float B = FMath::Sin(FPlatformTime::Seconds() + PI);
						return FSlateColor(FLinearColor(R, G, B, 1));               // rainbow effect semplicemente sono semplicemente 3 seni che hanno degli offset differenti
					})
			]
#pragma region Stuff to ask
			/*+SVerticalBox::Slot()
				.AutoHeight()
				.HAlign(HAlign_Center)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					[
						SNew(STextBlock)
						.Text(LOCTEXT("PropetiesToActivate", "Select an actor"))
					]
					+SHorizontalBox::Slot()
					.AutoWidth()
					[
						SNew(SObjectPropertyEntryBox)
						.DisplayBrowse(true)
						.DisplayThumbnail(true)
						.AllowedClass(UBlueprint::StaticClass())
						.OnObjectChanged(FOnSetObject::CreateStatic(&UnrealTheMEMESplugin::OnObjectChanged))
						.EnableContentPicker(true)
					]
				]*/
#pragma endregion Stuff to ask
			+SVerticalBox::Slot()
				.AutoHeight()
				.HAlign(HAlign_Center)
				[
				SNew(SHorizontalBox)   
				+SHorizontalBox::Slot()     // slot button yes
				.Padding(0,60,150,0)       // padding qui serve per spostare il bottone 
				.AutoWidth()
				[
					SNew(SButton)
					.Text(FText::FromString("Yes !"))
					.TextStyle(&TextBoxStyle)
					.ContentPadding(FMargin(60, 60, 60, 60))  // content padding serve per gestire la grandezza del bottone 
					.OnClicked_Lambda([]() -> FReply
					{
						FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Ok, Good for you")); // invia messaggio di dialogo
						return FReply::Handled();
					})
					
				]
				+SHorizontalBox::Slot()    // slot button no
				.AutoWidth()
				.Padding(0, 60, 0, 0)
				[
					SNew(SButton)
					.Text(FText::FromString("No !"))
					.TextStyle(&TextBoxStyle)
					.ContentPadding(FMargin(60, 60, 60, 60))
					.OnClicked_Lambda([]() -> FReply
					{
						// delirio mode
						UWorld* World = GEditor->GetEditorWorldContext().World();
						TArray<FAssetData> AssetsData;
						GEditor->GetContentBrowserSelections(AssetsData);
						for (const FAssetData& AssetData : AssetsData)
						{
							UObject* Instance = AssetData.GetAsset();
							UClass* AssetClass = Instance->GetClass();
							if (AssetClass->IsChildOf(UBlueprint::StaticClass()))
							{
								AssetClass = Cast<UBlueprint>(Instance)->GeneratedClass;
							}
							World->SpawnActor<AActor>(AssetClass, FVector(-400, 750, 300), FRotator(0,180,0));
							

						}
						TArray<AActor*> FoundActors;
						UGameplayStatics::GetAllActorsOfClass(World, AActor::StaticClass(), FoundActors);
						int number = 0;
						for (AActor* FoundActor : FoundActors)
						{
							if (FoundActor->GetOutermost()->IsDirty()) {
								FString string = FString::Printf(TEXT("UE_SUCKS_%d"), number);
								FoundActor->SetActorLabel(string);
								number++;
								//UE_LOG(LogTemp, Warning, TEXT("Useless: %s %s %s"), *FoundActor->GetName(), *FoundActor->GetPathName(), *FoundActor->GetFullName());

							}
							
						}
						return FReply::Handled();
					})
				]


			]
			];
		}));

	/*return SNew(SDockTab).TabRole(ETabRole::NomadTab)*/
	
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
	if (FParse::Command(&Cmd, TEXT("UnrealSurvey"))) {
		const TSharedRef<FGlobalTabmanager>& TabManager = FGlobalTabmanager::Get();
		TabManager->TryInvokeTab(UnrealTheMEMESpluginTabName);
		return true;
	}
	return false;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUnrealTheMEMESpluginModule, UnrealTheMEMESplugin)