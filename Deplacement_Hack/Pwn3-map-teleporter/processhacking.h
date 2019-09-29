#ifndef PROCESSHACKING_H
#define PROCESSHACKING_H

#include <windows.h>
#include <TlHelp32.h>

class ProcessHacking
{
public:
    PROCESSENTRY32 m_gameProcess;
    HANDLE m_handleProcess;
    HWND m_hWndWindow;
    DWORD m_dwGameLogic;
    ProcessHacking(LPCTSTR, LPCTSTR, LPCTSTR);

    DWORD FindProcessName(const char* m_ProcessName, PROCESSENTRY32* pEntry);
    DWORD getThreadByProcess(DWORD m_DwordProcess);
    DWORD GetModuleNamePointer(LPTSTR ModuleName, DWORD m_DwordProcessId);
    void runSetDebugPrivs();
};



#endif // PROCESSHACKING_H
