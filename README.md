# Misador's Testing Initiative.
W.I.P. Based on the TF:Grub fork.

## Info

[Discord](https://discord.gg/zJxQWjfC)

## Credits
- **Misador's Testing Initiative**
  - **Misador441** – Lead M.T.I. Dev  
    https://www.youtube.com/@Misador441
  
- **Grub Fortress**
  - **Grub** – Lead TF:Grub Dev  
    https://www.youtube.com/@GrubTheBadMapper
    
  - **Sargeant Death** - The Balance Journalist  
    https://steamcommunity.com/profiles/76561199026136810

- **Weapon Models**
  - **The Under Pressure** – Haau, Dim  
    https://gamebanana.com/mods/529270
    
  - **The Perforator** – Haau, kibbleknight  
    https://gamebanana.com/mods/516732
    
  - **The Big Owen** – Haau, kibbleknight  
    https://gamebanana.com/mods/603188
    
  - **The Pipebomb Launcher** – Haau, Extra Ram  
    https://gamebanana.com/mods/418217

  - **Der Erwecker** – Haau, Tabby  
  https://gamebanana.com/mods/543039

  - **Unfortunate Son** - Weapon Model: Open Fortress. TF2 port: smh2211. Custom animations: Mr. PurplePigeon. Custom sounds: Uncle Doe. Weapon Script: Fortress Connected.
  https://gamebanana.com/mods/633176


- **Community Help/Contributions**
  - **BetaM** – Custom Items, Credits menu, misc. fixes  
    https://www.youtube.com/BetaM

  - **Vvis** – Code assistance, provided some code from the FC (Fortress Connected).

  - **Better Fortress 2** – The mod Grub Fortress is a fork of  
    https://github.com/ALIEN31ITA/Better-Fortress-2
    
  - **Ultimate Visual Fix Pack** - agrastiOs, Nonhuman, Nonhuman, Whurr, PieSavvy, JarateKing, FlaminSarge  
    https://github.com/agrastiOs/Ultimate-TF2-Visual-Fix-Pack
    
  - **Team Fortress 2 Goldrush** – Removed MYM Hud, And V_Model Support  
    https://www.tf2goldrush.com/
    
  - **Toru the Red Fox** – Old TF2 Main menu  
    https://github.com/TorutheRedFox/source-sdk-2013
    
  - **Solo Fortress 2, Kepler** – Item schema delete attribute support  
    https://moddb.com/mods/solo-fortress-2
    
  - **Hactica** – Ultimate Weapon Animation Fixes  
    https://gamebanana.com/wips/86367
    
  - **NvC-DmN-CH** – HL2 Mirrored code  
    https://github.com/NvC-DmN-CH/Half-Life-2-Mirrored

  - **wgetjane** – Fix sniper laser dot position being calculated inaccurately  
    https://github.com/ValveSoftware/source-sdk-2013/pull/637

### Windows

Requirements:
 - Source SDK 2013 Multiplayer installed via Steam
 - Visual Studio 2022 with the following workload and components:
   - Desktop development with C++:
     - MSVC v143 - VS 2022 C++ x64/x86 build tools (Latest)
     - Windows 11 SDK (10.0.22621.0) or Windows 10 SDK (10.0.19041.1)
 - Python 3.13 or later

Inside the cloned directory, navigate to `src`, run:
```bat
creategameprojects.bat
```
This will generate the Visual Studio project `mti.sln` which will be used to build Grub Fortess.

Then, on the menu bar, go to `Build > Build Solution`, and wait for everything to build.

You can then select the `Client (Misador's Testing Initiative)` project you wish to run, right click and select `Set as Startup Project` and hit the big green `> Local Windows Debugger` button on the tool bar in order to launch your mod.

The default launch options should be already filled in for the `Release` configuration.

### Linux (Not Tested For MTI, pretty sure you will have to modify something to make it work)

Requirements:
 - Source SDK 2013 Multiplayer installed via Steam
 - podman

Inside the cloned directory, navigate to `src`, run:
```bash
./creategameprojects
```

This will build all the projects related to the SDK and your mods automatically against the Steam Runtime.

You can then, in the root of the cloned directory, you can navigate to `game` and run your mod by launching the build launcher for your mod project, eg:
```bash
./mod_tf
```
