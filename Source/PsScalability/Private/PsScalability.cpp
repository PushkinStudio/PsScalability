// Copyright 2015-2023 MY.GAMES. All Rights Reserved.

#include "PsScalability.h"

#include "Misc/ConfigCacheIni.h"
#include "Misc/CoreDelegates.h"
#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FPsScalabilityModule"

namespace ScalabilityModuleImpl
{
bool IsItScalabilityFile(const TCHAR* Filename)
{
	if (FCString::Strifind(Filename, TEXT("Scalability.ini")))
	{
		return true;
	}

	return false;
}

void ClearSection(const TCHAR* SectionName, const TCHAR* Filename)
{
	static const TSet<FString> WhitelistSections = std::initializer_list<FString>({TEXT("ScalabilitySettings")});

	if (!WhitelistSections.Contains(SectionName))
	{
		GConfig->EmptySection(SectionName, Filename);
	}
}

void ClearSections(const TCHAR* Filename)
{
	TArray<FString> SectionNames;
	GConfig->GetSectionNames(Filename, SectionNames);
	for (const auto& Section : SectionNames)
	{
		ClearSection(*Section, Filename);
	}
}

} // namespace ScalabilityModuleImpl

void FPsScalabilityModule::StartupModule()
{
	ScalabilityModuleImpl::ClearSections(*GScalabilityIni);

#if WITH_EDITOR
	// Feature level switching
	FCoreDelegates::OnConfigSectionRead.AddLambda([](const TCHAR* Filename, const TCHAR* SectionName) {
		if (ScalabilityModuleImpl::IsItScalabilityFile(Filename))
		{
			ScalabilityModuleImpl::ClearSections(Filename);
		}
	});
#endif // WITH_EDITOR
}

void FPsScalabilityModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FPsScalabilityModule, PsScalability)
