// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UnrealTheMEMES/UnrealTheMEMESGameModeBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeUnrealTheMEMESGameModeBase() {}
// Cross Module References
	UNREALTHEMEMES_API UClass* Z_Construct_UClass_AUnrealTheMEMESGameModeBase_NoRegister();
	UNREALTHEMEMES_API UClass* Z_Construct_UClass_AUnrealTheMEMESGameModeBase();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_UnrealTheMEMES();
// End Cross Module References
	void AUnrealTheMEMESGameModeBase::StaticRegisterNativesAUnrealTheMEMESGameModeBase()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AUnrealTheMEMESGameModeBase);
	UClass* Z_Construct_UClass_AUnrealTheMEMESGameModeBase_NoRegister()
	{
		return AUnrealTheMEMESGameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_AUnrealTheMEMESGameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AUnrealTheMEMESGameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_UnrealTheMEMES,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AUnrealTheMEMESGameModeBase_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "UnrealTheMEMESGameModeBase.h" },
		{ "ModuleRelativePath", "UnrealTheMEMESGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AUnrealTheMEMESGameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AUnrealTheMEMESGameModeBase>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AUnrealTheMEMESGameModeBase_Statics::ClassParams = {
		&AUnrealTheMEMESGameModeBase::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_AUnrealTheMEMESGameModeBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AUnrealTheMEMESGameModeBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AUnrealTheMEMESGameModeBase()
	{
		if (!Z_Registration_Info_UClass_AUnrealTheMEMESGameModeBase.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AUnrealTheMEMESGameModeBase.OuterSingleton, Z_Construct_UClass_AUnrealTheMEMESGameModeBase_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AUnrealTheMEMESGameModeBase.OuterSingleton;
	}
	template<> UNREALTHEMEMES_API UClass* StaticClass<AUnrealTheMEMESGameModeBase>()
	{
		return AUnrealTheMEMESGameModeBase::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AUnrealTheMEMESGameModeBase);
	struct Z_CompiledInDeferFile_FID_UnrealTheMEMES_Source_UnrealTheMEMES_UnrealTheMEMESGameModeBase_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealTheMEMES_Source_UnrealTheMEMES_UnrealTheMEMESGameModeBase_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AUnrealTheMEMESGameModeBase, AUnrealTheMEMESGameModeBase::StaticClass, TEXT("AUnrealTheMEMESGameModeBase"), &Z_Registration_Info_UClass_AUnrealTheMEMESGameModeBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AUnrealTheMEMESGameModeBase), 2412336531U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealTheMEMES_Source_UnrealTheMEMES_UnrealTheMEMESGameModeBase_h_1661879808(TEXT("/Script/UnrealTheMEMES"),
		Z_CompiledInDeferFile_FID_UnrealTheMEMES_Source_UnrealTheMEMES_UnrealTheMEMESGameModeBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UnrealTheMEMES_Source_UnrealTheMEMES_UnrealTheMEMESGameModeBase_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
