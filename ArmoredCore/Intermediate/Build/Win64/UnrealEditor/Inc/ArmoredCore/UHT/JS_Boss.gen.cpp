// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ArmoredCore/JS_Boss.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeJS_Boss() {}

// Begin Cross Module References
ARMOREDCORE_API UClass* Z_Construct_UClass_AJS_Boss();
ARMOREDCORE_API UClass* Z_Construct_UClass_AJS_Boss_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_ACharacter();
UPackage* Z_Construct_UPackage__Script_ArmoredCore();
// End Cross Module References

// Begin Class AJS_Boss
void AJS_Boss::StaticRegisterNativesAJS_Boss()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AJS_Boss);
UClass* Z_Construct_UClass_AJS_Boss_NoRegister()
{
	return AJS_Boss::StaticClass();
}
struct Z_Construct_UClass_AJS_Boss_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "JS_Boss.h" },
		{ "ModuleRelativePath", "JS_Boss.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AJS_Boss>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AJS_Boss_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_ACharacter,
	(UObject* (*)())Z_Construct_UPackage__Script_ArmoredCore,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AJS_Boss_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AJS_Boss_Statics::ClassParams = {
	&AJS_Boss::StaticClass,
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
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AJS_Boss_Statics::Class_MetaDataParams), Z_Construct_UClass_AJS_Boss_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AJS_Boss()
{
	if (!Z_Registration_Info_UClass_AJS_Boss.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AJS_Boss.OuterSingleton, Z_Construct_UClass_AJS_Boss_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AJS_Boss.OuterSingleton;
}
template<> ARMOREDCORE_API UClass* StaticClass<AJS_Boss>()
{
	return AJS_Boss::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AJS_Boss);
AJS_Boss::~AJS_Boss() {}
// End Class AJS_Boss

// Begin Registration
struct Z_CompiledInDeferFile_FID_Project_ARMOREDCORE_ArmoredCore_Source_ArmoredCore_JS_Boss_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AJS_Boss, AJS_Boss::StaticClass, TEXT("AJS_Boss"), &Z_Registration_Info_UClass_AJS_Boss, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AJS_Boss), 2116358782U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Project_ARMOREDCORE_ArmoredCore_Source_ArmoredCore_JS_Boss_h_2395674706(TEXT("/Script/ArmoredCore"),
	Z_CompiledInDeferFile_FID_Project_ARMOREDCORE_ArmoredCore_Source_ArmoredCore_JS_Boss_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Project_ARMOREDCORE_ArmoredCore_Source_ArmoredCore_JS_Boss_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
