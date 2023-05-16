// Copyright 2023 Gradess Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PythonBlueprintFixerSettings.generated.h"

/**
 * 
 */
UCLASS(Config = "PythonBlueprintFixer")
class PYTHONBLUEPRINTFIXER_API UPythonBlueprintFixerSettings : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(config, EditAnywhere, meta=(ConfigRestartRequired=true, MultiLine=true))
	TArray<FString> StartupScripts;
};
