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
