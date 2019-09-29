#include "processhacking.h"

ProcessHacking::ProcessHacking(LPCTSTR processName, LPCTSTR windowTitle, LPCTSTR dllName)
{
    runSetDebugPrivs();
    while (!FindProcessName(processName, &m_gameProcess)) Sleep(12);
    while (!(getThreadByProcess(m_gameProcess.th32ProcessID))) Sleep(12);

    m_handleProcess = OpenProcess(PROCESS_ALL_ACCESS, false, m_gameProcess.th32ProcessID);
    m_dwGameLogic = 0x0;
    while (m_dwGameLogic == 0x0) m_dwGameLogic = GetModuleNamePointer((LPTSTR)dllName, m_gameProcess.th32ProcessID);
    m_hWndWindow = FindWindow(NULL, windowTitle);
}

DWORD ProcessHacking::FindProcessName(const char* m_ProcessName, PROCESSENTRY32* pEntry)
{
    PROCESSENTRY32 m_ProcessEntry;
    m_ProcessEntry.dwSize = sizeof(PROCESSENTRY32);
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE)
        return 0;
    if (!Process32First(hSnapshot, &m_ProcessEntry))
    {
        CloseHandle(hSnapshot);
        return 0;
    }
    do
    {
        if (!_strcmpi(m_ProcessEntry.szExeFile, m_ProcessName))
        {
            memcpy((void*)pEntry, (void*)&m_ProcessEntry, sizeof(PROCESSENTRY32));
            CloseHandle(hSnapshot);
            return m_ProcessEntry.th32ProcessID;
        }
    } while (Process32Next(hSnapshot, &m_ProcessEntry));
    CloseHandle(hSnapshot);
    return 0;
}

DWORD ProcessHacking::getThreadByProcess(DWORD m_DwordProcess)
{
    THREADENTRY32 m_ThreadEntry;
    m_ThreadEntry.dwSize = sizeof(THREADENTRY32);
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE)
        return 0;

    if (!Thread32First(hSnapshot, &m_ThreadEntry))
    {
        CloseHandle(hSnapshot);
        return 0;
    }

    do
    {
        if (m_ThreadEntry.th32OwnerProcessID == m_DwordProcess)
        {
            CloseHandle(hSnapshot);
            return m_ThreadEntry.th32ThreadID;
        }
    } while (Thread32Next(hSnapshot, &m_ThreadEntry));
    CloseHandle(hSnapshot);
    return 0;
}

DWORD ProcessHacking::GetModuleNamePointer(LPTSTR ModuleName, DWORD m_DwordProcessId)
{
    MODULEENTRY32 lpModuleEntry;
    lpModuleEntry.dwSize = sizeof(lpModuleEntry);
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, m_DwordProcessId);
    if (!hSnapShot)
        return NULL;
    BOOL m_RunModule = Module32First(hSnapShot, &lpModuleEntry);
    while (m_RunModule)
    {
        if (!strcmp(lpModuleEntry.szModule, ModuleName))
        {
            CloseHandle(hSnapShot);
            return (DWORD)lpModuleEntry.modBaseAddr;
        }
        m_RunModule = Module32Next(hSnapShot, &lpModuleEntry);
    }
    CloseHandle(hSnapShot);
    return NULL;
}

void ProcessHacking::runSetDebugPrivs()
{
    HANDLE m_handleProcess = GetCurrentProcess(), m_HandleToken;
    TOKEN_PRIVILEGES priv;
    LUID m_LUID;
    OpenProcessToken(m_handleProcess, TOKEN_ADJUST_PRIVILEGES, &m_HandleToken);
    LookupPrivilegeValue(0, "seDebugPrivilege", &m_LUID);
    priv.PrivilegeCount = 1;
    priv.Privileges[0].Luid = m_LUID;
    priv.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    AdjustTokenPrivileges(m_HandleToken, false, &priv, 0, 0, 0);
    CloseHandle(m_HandleToken);
    CloseHandle(m_handleProcess);
}
