// Copyright 2015-2020 Mail.Ru Group. All Rights Reserved.

#include "PsScalability.h"

#define LOCTEXT_NAMESPACE "FPsScalabilityModule"

void FPsScalabilityModule::StartupModule()
{
	TSet<FString> WhitelistSections = std::initializer_list<FString>({TEXT("ScalabilitySettings")});

	TArray<FString> SectionNames;
	GConfig->GetSectionNames(GScalabilityIni, SectionNames);
	for (const auto& Section : SectionNames)
	{
		if (!WhitelistSections.Contains(Section))
		{
			GConfig->EmptySection(*Section, GScalabilityIni);
		}
	}
}

void FPsScalabilityModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FPsScalabilityModule, PsScalability)