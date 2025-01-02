// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ArmoredCore/ArmoredCoreGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeArmoredCoreGameMode() {}

// Begin Cross Module References
ARMOREDCORE_API UClass* Z_Construct_UClass_AArmoredCoreGameMode();
ARMOREDCORE_API UClass* Z_Construct_UClass_AArmoredCoreGameMode_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
UPackage* Z_Construct_UPackage__Script_ArmoredCore();
// End Cross Module References

// Begin Class AArmoredCoreGameMode
void AArmoredCoreGameMode::StaticRegisterNativesAArmoredCoreGameMode()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AArmoredCoreGameMode);
UClass* Z_Construct_UClass_AArmoredCoreGameMode_NoRegister()
{
	return AArmoredCoreGameMode::StaticClass();
}
struct Z_Construct_UClass_AArmoredCoreGameMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "ArmoredCoreGameMode.h" },
		{ "ModuleRelativePath", "ArmoredCoreGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AArmoredCoreGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AArmoredCoreGameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_ArmoredCore,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AArmoredCoreGameMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AArmoredCoreGameMode_Statics::ClassParams = {
	&AArmoredCoreGameMode::StaticClass,
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
	0x008802ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AArmoredCoreGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_AArmoredCoreGameMode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AArmoredCoreGameMode()
{
	if (!Z_Registration_Info_UClass_AArmoredCoreGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AArmoredCoreGameMode.OuterSingleton, Z_Construct_UClass_AArmoredCoreGameMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AArmoredCoreGameMode.OuterSingleton;
}
template<> ARMOREDCORE_API UClass* StaticClass<AArmoredCoreGameMode>()
{
	return AArmoredCoreGameMode::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AArmoredCoreGameMode);
AArmoredCoreGameMode::~AArmoredCoreGameMode() {}
// End Class AArmoredCoreGameMode

// Begin Registration
struct Z_CompiledInDeferFile_FID_Project_ARMOREDCORE_ArmoredCore_Source_ArmoredCore_ArmoredCoreGameMode_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AArmoredCoreGameMode, AArmoredCoreGameMode::StaticClass, TEXT("AArmoredCoreGameMode"), &Z_Registration_Info_UClass_AArmoredCoreGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AArmoredCoreGameMode), 397971721U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Project_ARMOREDCORE_ArmoredCore_Source_ArmoredCore_ArmoredCoreGameMode_h_2564385773(TEXT("/Script/ArmoredCore"),
	Z_CompiledInDeferFile_FID_Project_ARMOREDCORE_ArmoredCore_Source_ArmoredCore_ArmoredCoreGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Project_ARMOREDCORE_ArmoredCore_Source_ArmoredCore_ArmoredCoreGameMode_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
