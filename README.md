# oot3d_practice_menu
This project is still a WIP, with many TODOs, and a number of bugs with what has already been implemented. If you have any questions about details or whatever, feel free to dm me on twitter or discord.

This is a project which opens an on-screen menu in OoT3D, which can be packed with whatever features are wanted. The current motivation is for speedrunners and glitch hunters to add features which allow them to practice and study the game.

There is nothing special about OoT3D in the methods used here, though the relevant addresses and size are currently hard-coded to work for OoT3D. Someday, these can all be generalized and automated, and this work for almost all, if not all, 3DS games.

Also, be sure to use this version of Luma3DS, which has critical game patching fixes https://github.com/leoetlino/Luma3DS/releases (NOTE: the necessary fixes have been merged upstream into the main Luma3DS repository, meaning you may now use a recent build of Luma3DS).

# Shoutouts
* Shoutouts to n3rdswithgame, who created the projects that this one descended from, teaching me how literally anything works, help with reverse engineering, and more.
* Shoutouts to Lioncache, who also just helps me a ton.
* Shoutouts to RicBent and his program Magikoopa, which gave rise to the memory repermissioning strategy used here. Some code is modified straight from his.
* Shoutouts to leoetlino, who has helped me out, and fixed bugs in Luma3DS which allow this project to work. His Project Restoration proved the unlimited scale at which 3DS game patching can operate.
* Shoutouts to the developers of libctru and Luma3DS, because I stole/modified a lot of their code.
* Shoutouts to glank and all of the developers of gz, for clearly inspiring this project. The gz repo gives me tons of documentation to work from, patterns to follow, and I'm also stealing your table of contents format.
* Shoutouts to the OoT decomp team, because that project has been incredibly useful for me for documentation and learning about how the game works. The z3D folder has headers largely copied from that project.
* Shoutouts to the OoT3D community, because you're the ones I want to make this for in the first place.

# Some Notes
* I can't just use all of libctru, because it conflicts with the base game.
* My previous OoT3D patches needed to fit all of their code in the leftover padding of the existing code section from unmodified OoT3D. Now, the bulk of the code is located on extra pages appended at the end of the program image. The custom "loader" is placed into the code section padding, which repermissions the new data pages to be executable. This means custom code and data can have an effectively unlimited size.
* In theory, I could do a lot more with the menu graphically (like a display on top of the gameplay on the top screen, that pops out in 3D?), but for know I'm just trying to get everything functional and ready for an eventual "release".
* I'm a noob and everything is hard.

# How to Use:
* Install a recent build of Luma3DS, or use the one linked above. If you already have Luma3DS, you can upgrade by simply replacing "boot.firm" at the root of your SD card.
* USA: Place "code.ips" and "exheader.bin" in the folder /luma/titles/0004000000033500 . You may new to create this folder.
* JP: Place "code_j.ips" and "exheader.bin" in the folder /luma/titles/0004000000033400 . Rename "code_j.ips" to "code.ips". 
* Hold Select while powering on the console to launch the Luma3DS menu. Turn on "Enable game patching". You should only need to do this once, unless if you disable game patching in the future.
* It should work now! If not, you likely need to use a different version of Luma3DS (try the one linked above).

# User manual


## 0 Table of contents
-   [0 Table of contents](#0-table-of-contents)
-   [1 Introduction](#1-introduction)
-   [2 Menus](#2-menus)
    -   [2.1 Warps](#21-warps)
    -   [2.2 Scene](#22-scene)
    -   [2.3 Cheats](#23-cheats)
    -   [2.4 Inventory](#24-inventory)
    -   [2.5 Equips](#25-equips)
    -   [2.6 File](#26-file)
    -   [2.7 Macro](#27-macro)
    -   [2.8 Watches](#28-watches)
    -   [2.9 Debug](#29-debug)
    -   [2.10 Settings](#210-settings)

## 1 Introduction
Below you may see the sorts of features which are already implemented, and an idea of some of the planned features to come. Note that selecting any option below which is labeled as "TODO" may have unintended consequences, often including a crash.

## 2 Menus

### 2.1 Warps
The **Places** menu allows you to warp to any location. After choosing a scene, a new menu will prompt you to select Link's age upon spawning, the cutscene number upon spawning, and the desired entrance to the chosen scene. (NOTE: As of now, it is unsafe to set the cutscene number to anything except None. Any other option will frequently crash).

The "Manually Enter Entrance Index" option is similar, but allows you to manually enter the desired entrance index.

The Clear CS Pointer option sets the cutscene pointer to point to a null cutscene. In the N64 version, this prevents many wrong warps from crashing. In this version, its usefullness has not been well-tested, but it can be used to escape from many cutscenes.

Please note that many combinations of entrance index and cutscene number will crash the game. This is intended behavior, as it reflects the reality of an unmodified version of the game. Please report any crashes or other behavior that do not seem to be intended or otherwise reflective of expected in-game behavior.

### 2.2 Scene
TODO

### 2.3 Cheats
This menu provides a number of built in quick cheats. These cheats include:
-   Refill Health, Magic, Items, Keys, Rupees
-   Change Quest Mode (Regular/Master Quest). Note: this only toggles the mirroring and double damage effects of Master Quest until reloading the save file. Double Note: This option will eventually move to the **File** menu.
-   Infinite Nayru's Love (TODO)
-   Freeze time of day (TODO)
-   No music (TODO)
-   Enable usable items (TODO)
-   Activate ISG

### 2.4 Inventory
The **Items** menu allows you to modify your X,Y,I,II, and Ocarina button items. Toggling an item on will place it into it's proper item slot. Toggling an item off will remove the item from it's proper item slot, as well as removing that slot from the Child and Adult Items grids. For bottle and trade items slots, a sub menu will appear which allows you to toggle specific items.

The **Right Side Gear** menu allows you to modify the right side of the Gear screen. This includes swords, shields, tunics, capacity upgrades, strength upgrades, and dive meter upgrades.

The **Left Side Gear** menu allows you to modify the left side of the Gear screen. This includes medallions, spiritual stones, pieces of heart, the Shard of Agony, the Gerudo Token, and Golden Skull Tokens. (NOTE: Currently, there is a bug in which the spiritual stones, Shard of Agony, and Gerudo Token do not correctly display their on/off status in the menu, despite their otherwise toggling working correctly.)

The **Amounts** menu allows you to modify directly the amount of various items. This includes the Items menu items, Double Defense, Heart Containers, Current Health, Magic meter size, Magic amount, the number of hits left on Giant's Knife, and rupee amount.

### 2.5 Equips
This menu allows you to change the item on your B,Y,X,I, and II button items. Note that changing the item on a button will not change the equipped item slot, or the visual item slot on that button. This means that that changes to the button items will not be reflected visually on the bottom screen, and that they will not persist through pausing or load zones. If requested, this can be changed in the future.

### 2.6 File
TODO

### 2.7 Macro
TODO

### 2.8 Watches
This menu allows you to set memory watches which will appear on the bottom screen. Watches can be named. Watches can be set to 8, 16, or 32 bit integers, displayed as signed decimal, unsigned decimal, or hexadecimal, or as 32 bit floats. (NOTE: As of now, printing floats is not supported. In the meantime, I suggest that you instead opt for X32.) A watch is considered to be "enabled" if its address is not 0x00000000, the null address. The **Draw** option can be used to toggle whether or not a watch is currently to be displayed.

### 2.9 Debug
The **Actors** menu displays a list of all allocations currently on the "Actor Heap". (Note that in reality, this actor heap is part of a larger game arena, which contains other allocations besides actors, though this is by-and-large unimportant information to know.) By scrolling with L/R, the actor list can be filtered by actor type. By pressing A on an actor, more details about that actor will be shown. (NOTE: As of now printing floats is not supported, so some actor values will be rendered as simply "%f".) By pressing X on an actor, that actor will be deleted on the next frame of gameplay.

### 2.10 Commands
This menu allows you to change the input combo for various commands. A command input combo may consist of up to 4 buttons. If a combo is "Relaxed", the command will execute whenever all of the buttons in its combo are held. If a combo is "Strict", the command will execute only if the buttons are held in the order that they are displayed, with no other simultaneous input. (NOTE: For the time being, please press buttons one at a time while editing menu combos, improving this feature is a WIP.) You can press X on the Edit Command page to clear/disable the command.
