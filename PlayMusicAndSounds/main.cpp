#include <iostream>
#include <Windows.h>
#include <string>
#include "resource.h"
#pragma comment(lib,"Winmm.lib")

#define HOTKEY_MONEY VK_F8
#define HOTKEY_MUSIC VK_F9
#define SND_MUSIC "MUSIC.mp3"

LPSTR GetResource(int resourceId);

int main(int argc, char* argv[])
{
    LPSTR sound = GetResource(SND_MONEY);
    bool muteMusic = false;
    std::string mci = "open ";
    mci.append(SND_MUSIC);
    mci.append(" alias SND_MUSIC");
    mciSendString(mci.c_str(), NULL, NULL, NULL);
    mciSendString("play SND_MUSIC repeat", NULL, NULL, NULL);
    // and dont forget to close opened file
    // mciSendString("close SND_MUSIC", NULL, 0, NULL);
    // https://stackoverflow.com/questions/22253074/how-to-play-or-open-mp3-or-wav-sound-file-in-c-program
    /*
        lstrcat(cmd, "play \"");
        lstrcat(cmd, sound); // sound = MUSIC.MP3
        lstrcat(cmd, "\"");
        mciSendString(cmd, nullptr, 0, nullptr);
    */

    while (true)
    {
        if (GetAsyncKeyState(HOTKEY_MONEY) & 0x8000)
        {
            #PlaySoundA((LPCSTR)snd, ...)
            #PlaySound(L"str", ...)
            sndPlaySound(sound, SND_MEMORY | SND_ASYNC | SND_NODEFAULT);
        }
        if (GetAsyncKeyState(HOTKEY_MUSIC) & 0x8000)
        {
            muteMusic = !muteMusic;
            if(muteMusic)
                mciSendString("pause SND_MUSIC", NULL, NULL, NULL);
            else
                mciSendString("resume SND_MUSIC", NULL, NULL, NULL);
        }
        Sleep(50);
    }

    return 0;
}

LPSTR GetResource(int resourseId)
{
    HMODULE hInst = GetModuleHandle(NULL);
    if (!hInst)
    {
        return FALSE;
    }
    LPSTR lpRes;
    HANDLE hResInfo, hRes;

    // Find the WAVE resource. 

    hResInfo = FindResource(hInst, MAKEINTRESOURCE(resourseId), "WAVE");
    if (hResInfo == NULL)
        return FALSE;

    // Load the WAVE resource. 

    hRes = LoadResource(hInst, (HRSRC)hResInfo);
    if (hRes == NULL)
        return FALSE;

    // Lock the WAVE resource and play it. 

    lpRes = (LPSTR)LockResource(hRes);
    if (lpRes != NULL)
    {
        UnlockResource(hRes);
    }

    // Free the WAVE resource and return success or failure. 

    FreeResource(hRes);
    return lpRes;
}
