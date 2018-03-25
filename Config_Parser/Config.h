#pragma once
#ifndef CONFIG_H
#define CONFIG_H

#include <fstream>
#include <windows.h>
#include <string>

class Config {
public:
    std::string processName;

    struct entrys
    {
        std::string type;
        short size = 0;
        std::string module;
        DWORD_PTR address;
        DWORD offsets[5];
        short count = 0;
    } health, armour, money, experience, magazine, ammo, gren;

    struct hot {
        struct keys { int code = -1; std::string name; } godMode, noReload, money, experience;
    } hotkey;

    struct amount
    {
        union
        {
            int i = 0;
            float f;
        } value;
        std::string type;
    } maxHealth, amountMoney, amountExperience;

    Config(std::string file);
    ~Config();
    static BOOL FileExists(LPCTSTR szPath);

private:
    size_t offset, size;
    std::string buff;
    std::ifstream ini, xml;

    void ParseIni(std::string fileName);
    void PeadKey(hot::keys& hotkey);
    int Key2code(std::string key);
    void ReadAmount(amount& data, std::string& type);

    void ParseXml(std::string& fileName);
    void ReadEntry(entrys& data);
    void ReadType(entrys& data);
    void ReadAddress(entrys& data);
    void ReadOffsets(entrys& data);
    void ReadValue(amount& amount);
    std::string ReadSettings();
};
#endif
