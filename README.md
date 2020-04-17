# oot3d_practice_menu
I'm uploading this project in its current form unfinished so that it's easier to ask for help and also because I was bored. Currently, the menu works, but I'm failing to get it to actually draw on the screen. If you wanna talk about details or to help out, dm me on twitter or discord or something.

This is a project whose goal is to open an on-screen menu in OoT3D, which can be packed with whatever features are wanted. The current motivation is for speedrunners and glitch hunters to add features which allow them to practice and study the game.

There is nothing special about OoT3D in the methods used here, though the relevant addresses and size are currently hard-coded to work for OoT3D. Someday, these can all be generalized and automated, and this work for almost all, if not all, 3DS games.

The required modified exheader.bin is not included here because it is technically original code from OoT3D, if you want to try and use this in its current state, you will need to modify the exheader on your own (Someday this will be automated).

Also, be sure to use this version of Luma3DS, which has critical game patching fixes https://github.com/leoetlino/Luma3DS/releases

# Shoutouts
* Shoutouts to n3rdswithgame, who created the projects that this one descended from, teaching me how literally anything works, help with reverse engineering, and more.
* Shoutouts to Lioncache, who also just helps me a ton.
* Shoutouts to RicBent and his program Magikoopa, which gave rise to the memory repermissioning strategy used here. Some code is modified straight from his.
* Shoutouts to leoetlino, who has helped me out, and fixed bugs in Luma3DS which allow this project to work.
* Shoutouts to the developers of libctru and Luma3DS, because I stole/modified a lot of their code.
* Shoutouts to the OoT3D community, because you're the ones I want to make this for in the first place.

# Challenges
* I can't just use libctru, because it conflicts with the base game. So, I copied whatever code I needed, and used muslarm instead.
* My previous OoT3D patches needed to fit all of their code in the leftover padding of the existing code section from unmodified OoT3D. Now, that padding is used for a a custom "loader" which repermissions data pages that the rest of the code is sitting on to be executable.
* I'm a noob and everything is hard.

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
TODO

## 2 Menus

### 2.1 Warps
TODO

### 2.2 Scene
TODO

### 2.3 Cheats
This menu provides a number of built in quick cheats, some of which are still TODO. These cheats include:
-   Refill Health, Magic, Items, Keys, Rupees
-   Infinite Nayru's Love
-   Freeze time of day
-   No music
-   Enable usable items
-   Activate ISG

### 2.4 Inventory
The **Items** menu allows you to modify your X,Y,I,II, and Ocarina button items. Toggling an item on will place it into it's proper item slot. Toggling an item off will remove the item from it's proper item slot, as well as removing that slot from the Child and Adult Items grids. For bottle and trade items slots, a sub menu will appear which allows you to toggle specific items.

The **Right Side Gear** menu allows you to modify the right side of the Gear screen. This includes swords, shields, tunics, capacity upgrades, strength upgrades, and dive meter upgrades.

The **Left Side Gear** menu allows you to modify the left side of the Gear screen. This includes medallions, spiritual stones, pieces of heart, the Shard of Agony, the Gerudo Token, and Golden Skull Tokens.

The **Amounts** menu allows you to modify directly the amount of various items. This includes the Items menu items, Double Defense, Heart Containers, Current Health, Magic meter size, Magic amount, the number of hits left on Giant's Knife, and rupee amount.

### 2.5 Equips
TODO

### 2.6 File
TODO

### 2.7 Macro
TODO

### 2.8 Watches
TODO

### 2.9 Debug
TODO

### 2.10 Settings
TODO
