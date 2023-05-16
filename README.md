# Python Blueprint Fixer

## Description
Simple plugin that fixes Unreal Engine python scripts loading phase that causes blueprint compilation errors.

## How to install
1. Download [latest release](https://github.com/Gradess2019/PythonBlueprintFixer/releases/latest) for your Unreal Engine version
2. Unzip into: **\<ProjectDirectory\>/Plugins** (create Plugins directory if it doesn't exist)
3. If you are using C++: Right Mouse Button on your **.uproject** file -> Generate Visual Studio project files
4. Launch project
5. If it's not enabled: Go to Edit -> Plugins -> "Project" category -> Editor -> Enable "Python Blueprint Fixer" and restart the editor
7. Done

## How to use
Add your python scripts to Startup Scripts in project settings [as you usually do](https://docs.unrealengine.com/4.27/en-US/ProductionPipelines/ScriptingAndAutomation/Python/#startupscripts).
The plugin will start its work automatically. No additional steps required. Enjoy!