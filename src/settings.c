#include "menus/settings.h"
#include "3ds/extdata.h"
#include "common.h"
#include <string.h>

ExtSaveData gExtSaveData;
u8 selectedProfile = 0;

Menu SettingsMenu = {
    "Settings",
    .nbItems = 3,
    {
        {"Profile: 0", METHOD, .method = Settings_CycleProfile},
        {"Save Settings", METHOD, .method = Settings_SaveExtSaveData},
        {"Load Settings", METHOD, .method = Settings_LoadExtSaveData},
    }
};

void Settings_CycleProfile(void) {
    selectedProfile++;
    selectedProfile %= 3;
    SettingsMenu.items[SETTINGS_PROFILE].title[9] = selectedProfile + '0';
}

void Settings_InitExtSaveData(void) {
    memset(&gExtSaveData, 0, sizeof(gExtSaveData));
    gExtSaveData.version = EXTSAVEDATA_VERSION; // Do not change this line
    memcpy(gExtSaveData.cheats, cheats, sizeof(cheats));
    gExtSaveData.cheatForcedUsableItems = forcedUsableItems;
    memcpy(gExtSaveData.commands, commandList, sizeof(commandList));
    memcpy(gExtSaveData.watches, watches, sizeof(watches));
}

// copies saved values to the menu structs
void Settings_ApplyExtSaveData(void) {
    memcpy(cheats, gExtSaveData.cheats, sizeof(cheats));
    forcedUsableItems = gExtSaveData.cheatForcedUsableItems;
    for (u32 i = 0; i < NUMBER_OF_COMMANDS; i++) {
        commandList[i].comboLen = gExtSaveData.commands[i].comboLen;
        memcpy(commandList[i].inputs, gExtSaveData.commands[i].inputs, sizeof(gExtSaveData.commands[i].inputs));
        commandList[i].strict = gExtSaveData.commands[i].strict;
    }
    commandInit = 1;
    memcpy(watches, gExtSaveData.watches, sizeof(watches));
}

void Settings_SaveExtSaveData(void) {
    Settings_InitExtSaveData();

    char path[] = "/gz3D_X.bin";

    Result res;
    FS_Archive fsa;

    if(!R_SUCCEEDED(res = extDataMount(&fsa))) {
        alertMessage = "Failed to save! ";
        alertFrames = 1;
        drawAlert();
        return;
    }

    path[6] = selectedProfile + '0';

    extDataWriteFileDirectly(fsa, path, &gExtSaveData, 0, sizeof(gExtSaveData));

    extDataUnmount(fsa);

    alertMessage = "Profile X saved ";
    alertMessage[8] = selectedProfile + '0';
    alertFrames = 1;
    drawAlert();
}

void Settings_LoadExtSaveData(void) {
    char path[] = "/gz3D_X.bin";
    u32 version;

    Result res;
    FS_Archive fsa;
    Handle fileHandle;

    if (R_FAILED(res = extDataMount(&fsa))) {
        alertMessage = "Failed to load! ";
        alertFrames = 1;
        drawAlert();
        return;
    }

    path[6] = selectedProfile + '0';

    if (R_FAILED(res = extDataOpen(&fileHandle, fsa, path))) {
        extDataUnmount(fsa);
        alertMessage = "Failed to load! ";
        alertFrames = 1;
        drawAlert();
        return;
    }

    extDataReadFile(fileHandle, &version, 0, sizeof(version));
    if (version != EXTSAVEDATA_VERSION) {
        extDataClose(fileHandle);
        extDataUnmount(fsa);
        alertMessage = "Failed to load! ";
        alertFrames = 1;
        drawAlert();
        return;
    }

    extDataReadFile(fileHandle, &gExtSaveData, 0, sizeof(gExtSaveData));

    extDataClose(fileHandle);
    extDataUnmount(fsa);

    Settings_ApplyExtSaveData();

    alertMessage = "Profile X loaded";
    alertMessage[8] = selectedProfile + '0';
    alertFrames = 1;
    drawAlert();
}

// This function is called when loading a save file.
// In order to save the settings, the extdata need to already be present. Normally the
// extDataMount function (used when saving/loading extdata) creates them if they don't exist,
// but for some reason it fails to do so when it's called from the menu loop. The data creation
// only seems to work when saving/loading a save file, so the purpose of this function is to
// make sure the data exist (if the user has played the Randomizer, they would already be present)
void Settings_LoadGame(void) {
    FS_Archive fsa;
    if (R_SUCCEEDED(extDataMount(&fsa))) {
        extDataUnmount(fsa);
    }
}
