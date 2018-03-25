
int Key2code(std::string key)
{
    size_t len = key.length();
    switch (len)
    {
    case 1: return VkKeyScan(key[0]) & 0xff;
    case 2:
    case 3: return VK_F1 - 1 + atoi(key.substr(1).c_str());
    case 4:
    case 5: return VK_NUMPAD0 + atoi(key.substr(3).c_str());
    case 7:
    case 8: return VK_NUMPAD0 + atoi(key.substr(6).c_str());
    }
    return -1;
}
