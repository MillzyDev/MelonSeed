# MelonSeed
A MelonLoader plugin for loading C/C++ mods, for IL2CPP games.

# Making Mods
Read the wiki (TODO)

# Build Instructions
## Prerequisites
* [.NET Framework v4.7.2](https://dotnet.microsoft.com/en-us/download/dotnet-framework/net472)
* [CMake](https://cmake.org/download/)
* [Git](https://git-scm.com/)
* _MSVC*_
* _Windows 10/11 SDK*_
* [Unity](https://unity.com/releases/editor/archive)
  * Same version as the game being modded.
  * IL2CPP Build Support
* [MelonLoader installation](https://melonwiki.xyz/#/)

*Note: Both MSVC and the Windows 10/11 SDK can be installed under the "Universal Windows Platform Development" module in the Visual Studio installer.*

## Project Setup
Clone this repository with git, and open the cloned repository in File Explorer.

Navigate to the `MelonSeed.Plugin` folder and create a file called `MelonSeed.Plugin.csproj.user`. Open the file in a text editor of your choice and paste the following into it:
```xml
<Project>
    <PropertyGroup>
        <GameDir>PATH_TO_GAME</GameDir>
    </PropertyGroup>
</Project>
```
Replacing `PATH_TO_GAME` with the intended game's full path (the game should have MelonLoader installed).

Save and close the file.

Navigate to the `MelonSeed` folder thats in the same directory as `MelonSeed.Plugin` and create two (2) files, `unity_path.txt` and `game_path.txt`. In open both of these in a text editor of your choice.

In `unity_path.txt` paste the path to your Unity installation, it should look something like `C:/Program Files/Unity/Hub/Editor/2021.3.5f1`. **IMPORTANT: Make sure to replace any back-slashes `\` with forward-slashes `/`.**

In `game_path.txt` paste the path to your game installation, **again making sure all back-slashes `\` are replaced with forward-slashes `/`.**

Save and close both files.

## Building
TODO
