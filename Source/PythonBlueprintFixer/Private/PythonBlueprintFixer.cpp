// Copyright Epic Games, Inc. All Rights Reserved.

#include "PythonBlueprintFixer.h"

#include "IPythonScriptPlugin.h"
#include "ISettingsModule.h"
#include "PythonBlueprintFixerSettings.h"

#define LOCTEXT_NAMESPACE "FPythonBlueprintFixerModule"

void FPythonBlueprintFixerModule::StartupModule()
{
	RegisterSettings();
	
	CleaStartupScriptsInPythonPlugin();
	RunStartupScripts();
}

void FPythonBlueprintFixerModule::ShutdownModule()
{
	UnregisterSettings();
}

void FPythonBlueprintFixerModule::RegisterSettings() const
{
	auto& SettingsModule = FModuleManager::GetModuleChecked<ISettingsModule>("Settings");
	SettingsModule.RegisterSettings(
		TEXT("Project"), TEXT("Plugins"), TEXT("Python Blueprint Fixer"),
		LOCTEXT("PythonBlueprintFixerSettingsName", "Python Blueprint Fixer"),
		LOCTEXT("PythonBlueprintFixerDescription", "Configure PythonBlueprintFixer plugin"),
		GetMutableDefault<UPythonBlueprintFixerSettings>()
	);
}

void FPythonBlueprintFixerModule::UnregisterSettings() const
{
	if (const auto SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings(TEXT("Project"), TEXT("Plugins"), TEXT("PythonBlueprintFixer"));
	}
}

void FPythonBlueprintFixerModule::CleaStartupScriptsInPythonPlugin() const
{
	const auto PythonSettings = StaticFindObject(UObject::StaticClass(), nullptr, TEXT("/Script/PythonScriptPlugin.Default__PythonScriptPluginSettings"));
	checkf(PythonSettings, TEXT("UPythonScriptPluginSettings default object not found"));

	const auto StartupScriptsField = PythonSettings->GetClass()->FindPropertyByName(TEXT("StartupScripts"));
	checkf(StartupScriptsField, TEXT("StartupScripts field not found in PythonSettings"));

	StartupScriptsField->ClearValue_InContainer(PythonSettings);
}

void FPythonBlueprintFixerModule::RunStartupScripts() const
{
	auto& PythonModule = FModuleManager::LoadModuleChecked<IPythonScriptPlugin>("PythonScriptPlugin");
	
	const auto Settings = GetDefault<UPythonBlueprintFixerSettings>();
	const auto StartupScripts = Settings->StartupScripts;

	for (const auto& StartupScript : StartupScripts)
	{
		PythonModule.ExecPythonCommand(*StartupScript);
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FPythonBlueprintFixerModule, PythonBlueprintFixer)