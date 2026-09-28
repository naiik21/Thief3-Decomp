// Game/WindowManager.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

// The UI window manager (GWindowManager); docs/engine.md, "UI windows".
class WindowManager
{
public:
    FVector* GetUIScreenSize(FVector* Out);

    char Unknown00[0xCC];
    FLOAT LayoutWidth;       // +0xCC: [WindowManager] AssumedUIScreenWidth (640)
    FLOAT LayoutHeight;      // +0xD0: [WindowManager] AssumedUIScreenHeight (480)
};

// FUNCTION: 0x109E47E0 ?GetUIScreenSize@WindowManager@@QAEPAVFVector@@PAV2@@Z
FVector* WindowManager::GetUIScreenSize(FVector* Out)
{
    Out->X = LayoutWidth;
    Out->Y = LayoutHeight;
    return Out;
}
