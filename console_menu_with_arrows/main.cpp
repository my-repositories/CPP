#include <iostream>
#include <vector>
#include <windows.h>

#include "menu.hpp"

int main()
{
    std::vector<std::string> directories = {
        "bin", "boot", "cdrom", "dev", "devices",
        "etc", "home", "jack", "kernel", "lib",
        "lost+found", "media" , "mnt", "net",
        "opt", "platform", "proc", "root", "sbin",
        "srv", "system", "tmp", "usr", "var"
    };

    while (true)
    {
        Menu menu(directories, "Choose the directory");
        int index = menu.getSelectedIndex();

        system("cls");
        std::cout << "index______: " << index << std::endl;

        if (index != -1)
        {
            std::cout << "item: " << directories[index] << std::endl;
        }
        else
        {
            break;
        }
    }

    system("pause");
    return 0;
}