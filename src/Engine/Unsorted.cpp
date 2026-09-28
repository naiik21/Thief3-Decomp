// Engine/Unsorted.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#define WM_QUIT     0x0012
#define PM_NOREMOVE 0x0000
#define PM_REMOVE   0x0001

// The Win32 declarations it uses (as in winuser.h; the compiler bundle has no
// Platform SDK).
typedef int BOOL;

typedef unsigned int UINT;

typedef unsigned long DWORD;

typedef long LONG;

typedef UINT WPARAM;

typedef LONG LPARAM;

typedef struct HWND__* HWND;

struct POINT
{
    LONG x;
    LONG y;
};

struct MSG
{
    HWND hwnd;
    UINT message;
    WPARAM wParam;
    LPARAM lParam;
    DWORD time;
    POINT pt;
};

extern "C" __declspec(dllimport) BOOL __stdcall PeekMessageA(MSG* lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);

extern "C" __declspec(dllimport) BOOL __stdcall GetMessageA(MSG* lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax);

extern "C" __declspec(dllimport) BOOL __stdcall TranslateMessage(const MSG* lpMsg);

extern "C" __declspec(dllimport) LONG __stdcall DispatchMessageA(const MSG* lpMsg);

extern bool GIsAppActive;

           // 0 while another program has the focus
extern int GIsRequestingExit;

// FUNCTION: 0x10AEB350 ?PumpMessages@@YA_NHHPAUHWND__@@@Z
bool PumpMessages(int Wait, int Active, HWND Window)
{
    MSG Msg = { 0 };
    bool bHandled = false;
    bool bActive = Active == 0 ? GIsAppActive : Active == 1;
    switch (Wait)
    {
    case 0:
        while (PeekMessageA(&Msg, Window, 0, 0, PM_REMOVE) && bActive)
        {
            if (Msg.message == WM_QUIT)
                GIsRequestingExit = 1;
            TranslateMessage(&Msg);
            DispatchMessageA(&Msg);
            bHandled = true;
            if (Active == 0)
                bActive = GIsAppActive;
            else if (!PeekMessageA(&Msg, Window, 0, 0, PM_NOREMOVE))
                bActive = false;
        }
        break;
    case 1:
        while (!bActive && GetMessageA(&Msg, Window, 0, 0))
        {
            TranslateMessage(&Msg);
            DispatchMessageA(&Msg);
            bActive = GIsAppActive;
            bHandled = true;
        }
        if (!bActive)
            GIsRequestingExit = 1;
        break;
    default:
        if (PeekMessageA(&Msg, Window, 0, 0, PM_REMOVE))
        {
            if (Msg.message == WM_QUIT)
                GIsRequestingExit = 1;
            TranslateMessage(&Msg);
            DispatchMessageA(&Msg);
            bHandled = true;
        }
        break;
    }
    return bHandled;
}
