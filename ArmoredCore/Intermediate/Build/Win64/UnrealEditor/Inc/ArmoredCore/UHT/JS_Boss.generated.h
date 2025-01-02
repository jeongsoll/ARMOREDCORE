// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "JS_Boss.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef ARMOREDCORE_JS_Boss_generated_h
#error "JS_Boss.generated.h already included, missing '#pragma once' in JS_Boss.h"
#endif
#define ARMOREDCORE_JS_Boss_generated_h

#define FID_Project_ARMOREDCORE_ArmoredCore_Source_ArmoredCore_JS_Boss_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAJS_Boss(); \
	friend struct Z_Construct_UClass_AJS_Boss_Statics; \
public: \
	DECLARE_CLASS(AJS_Boss, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/ArmoredCore"), NO_API) \
	DECLARE_SERIALIZER(AJS_Boss)


#define FID_Project_ARMOREDCORE_ArmoredCore_Source_ArmoredCore_JS_Boss_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	AJS_Boss(AJS_Boss&&); \
	AJS_Boss(const AJS_Boss&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AJS_Boss); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AJS_Boss); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AJS_Boss) \
	NO_API virtual ~AJS_Boss();


#define FID_Project_ARMOREDCORE_ArmoredCore_Source_ArmoredCore_JS_Boss_h_9_PROLOG
#define FID_Project_ARMOREDCORE_ArmoredCore_Source_ArmoredCore_JS_Boss_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Project_ARMOREDCORE_ArmoredCore_Source_ArmoredCore_JS_Boss_h_12_INCLASS_NO_PURE_DECLS \
	FID_Project_ARMOREDCORE_ArmoredCore_Source_ArmoredCore_JS_Boss_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> ARMOREDCORE_API UClass* StaticClass<class AJS_Boss>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Project_ARMOREDCORE_ArmoredCore_Source_ArmoredCore_JS_Boss_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
