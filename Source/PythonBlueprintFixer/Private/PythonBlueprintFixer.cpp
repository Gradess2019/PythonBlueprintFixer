// Copyright 2023 Gradess Games. All Rights Reserved.

#include "PythonBlueprintFixer.h"
#include "IPythonScriptPlugin.h"

#define LOCTEXT_NAMESPACE "FPythonBlueprintFixerModule"

void FPythonBlueprintFixerModule::StartupModule()
{
	CopyStartupScriptsFromPlugin();
	RunStartupScripts();
}

void FPythonBlueprintFixerModule::ShutdownModule()
{
}

TObjectPtr<UObject> FPythonBlueprintFixerModule::GetPythonSettings() const
{
	const auto CDOName = TEXT("/Script/PythonScriptPlugin.Default__PythonScriptPluginSettings");
	return StaticFindObject(UObject::StaticClass(), nullptr, CDOName);
}

FProperty* FPythonBlueprintFixerModule::GetStratupScriptArrayProperty(TObjectPtr<UObject> PythonSettings) const
{
	checkf(PythonSettings, TEXT("UPythonScriptPluginSettings default object not found"));
	return PythonSettings->GetClass()->FindPropertyByName(TEXT("StartupScripts"));
}

void FPythonBlueprintFixerModule::CopyStartupScriptsFromPlugin()
{
	const auto PythonSettings = GetPythonSettings();
	const auto StartupScriptsField = GetStratupScriptArrayProperty(PythonSettings);
	checkf(StartupScriptsField, TEXT("StartupScripts field not found in PythonSettings"));
	
	StartupScriptsField->GetValue_InContainer(PythonSettings, &StartupScripts);
	StartupScriptsField->ClearValue_InContainer(PythonSettings);

	constexpr auto Delay = 1.f;
	ModuleDelayedHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateRaw(this, &FPythonBlueprintFixerModule::OnTick), Delay);
}

void FPythonBlueprintFixerModule::SetStartupScriptsBack() const
{
	const auto PythonSettings = GetPythonSettings();
	const auto StartupScriptsField = GetStratupScriptArrayProperty(PythonSettings);
	checkf(StartupScriptsField, TEXT("StartupScripts field not found in PythonSettings"));

	StartupScriptsField->SetValue_InContainer(PythonSettings, &StartupScripts);
}

void FPythonBlueprintFixerModule::RunStartupScripts() const
{
	auto& PythonModule = FModuleManager::LoadModuleChecked<IPythonScriptPlugin>("PythonScriptPlugin");

	for (const auto& StartupScript : StartupScripts)
	{
		PythonModule.ExecPythonCommand(*StartupScript);
	}
}

bool FPythonBlueprintFixerModule::OnTick(float InDeltaTime)
{
	ModuleDelayedHandle.Reset();

	SetStartupScriptsBack();

	return false;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FPythonBlueprintFixerModule, PythonBlueprintFixer)
