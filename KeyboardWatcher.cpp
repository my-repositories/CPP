#include <iostream>
#include <map>
#include <vector>
#include <windows.h>

class KeyboardWatcher
{
public:
    explicit KeyboardWatcher(const std::vector<int>& keysToWatch)
    {
        for (const auto& key : keysToWatch)
        {
            this->states[key] = false;
        }
    }

    bool isKeyDown(const int key)
    {
        return (GetAsyncKeyState(key) & 0x8000) > 0;
    }

    bool isKeyPressed(const int key)
    {
        auto currentState = GetAsyncKeyState(key);

        if ((currentState & 0x8000) && !this->states[key])
        {
            this->states[key] = true;
            return true;
        }
        else if (!currentState)
        {
            this->states[key] = false;
        }

        return false;
    }

private:
    std::map<int, bool> states;
};

void keyboardStatePrinter(const int key, const bool shift, const bool ctrl, const bool alt);

int main()
{
    std::vector<int> keys =
    {
        VK_F7,
        VK_F8
    };
    KeyboardWatcher watcher(keys);


    while (true)
    {
        for (const auto& key : keys)
        {
            if (watcher.isKeyPressed(key))
            {
                keyboardStatePrinter(
                    key,
                    watcher.isKeyDown(VK_SHIFT),
                    watcher.isKeyDown(VK_CONTROL),
                    watcher.isKeyDown(VK_MENU)
                );
            }
        }

        if (GetAsyncKeyState(VK_F13))
        {
            break;
        }
    }

    return 0;
}


void keyboardStatePrinter(const int key, const bool shift, const bool ctrl, const bool alt)
{
    if (shift)
    {
        std::cout << "SHIFT+";
    }

    if (ctrl)
    {
        std::cout << "CTRL+";
    }

    if (alt)
    {
        std::cout << "ALT+";
    }

    std::cout << key << std::endl;
}
