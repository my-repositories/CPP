bool ProcessOnFocus(std::string processName)
{
    DWORD idActive;
    GetWindowThreadProcessId(GetForegroundWindow(), &idActive);
    return idActive == getProcessIdByName(processName);
}
