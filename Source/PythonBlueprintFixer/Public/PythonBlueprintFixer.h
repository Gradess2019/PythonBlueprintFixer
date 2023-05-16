// Copyright 2023 Gradess Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FPythonBlueprintFixerModule : public IModuleInterface
{
public:
	TArray<FString> StartupScripts;
	FTSTicker::FDelegateHandle ModuleDelayedHandle;

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	TObjectPtr<UObject> GetPythonSettings() const;
	FProperty* GetStratupScriptArrayProperty(TObjectPtr<UObject> PythonSettings) const;
	
	void CopyStartupScriptsFromPlugin();
	void RunStartupScripts() const;

	bool OnTick(float InDeltaTime);
	void SetStartupScriptsBack() const;
};
