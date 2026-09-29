// Game/Window.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

typedef int BOOL;

// Where a window sits in its parent: [Window] Placement_X/Y (ParsePlacement).
enum EPlacement
{
    PLACE_None   = 0,
    PLACE_Center = 1,
    PLACE_Top    = 2,
    PLACE_Bottom = 3,
    PLACE_Left   = 4,
    PLACE_Right  = 5,
};

// The UI window manager (GWindowManager); docs/engine.md, "UI windows".
class WindowManager
{
public:
    FVector* GetUIScreenSize(FVector* Out);
    // Layout units to normalised screen coordinates (-1..1, y up); 0x109E4290.
    FVector LayoutToNormalized(INT X, INT Y);

    char Unknown00[0x1E4];
    INT LayoutOrigin;               // +0x1E4: 1 = from the parent's top-left corner
};

extern WindowManager* GWindowManager;

// Something that drives a window's position (vtable +0x0C returns it).
class WindowMover
{
public:
    virtual void Vfunc00();
    virtual void Vfunc04();
    virtual void Vfunc08();
    virtual FVector GetPosition();
};

// A UI window (System/T3UI.ini); docs/engine.md, "UI windows".
class Window
{
public:
    virtual void Vfunc00();
    virtual void Vfunc04();
    virtual void Vfunc08();
    virtual void Vfunc0C();
    virtual void Vfunc10();
    virtual void SetPosition(const FVector& Position);
    virtual FVector* PlacedPosition(FVector* Out);
    virtual void Vfunc1C();
    virtual void Vfunc20();
    virtual void Vfunc24();
    virtual void Vfunc28();
    virtual void Vfunc2C();
    virtual void Vfunc30();
    virtual void Vfunc34();
    virtual void Vfunc38();
    virtual void Vfunc3C();
    virtual void Vfunc40();
    virtual void Vfunc44();
    virtual void Vfunc48();
    virtual void Vfunc4C();
    virtual void Vfunc50();
    virtual void Vfunc54();
    virtual void Vfunc58();
    virtual void Vfunc5C();
    virtual void Vfunc60();
    virtual void Vfunc64();
    virtual void Vfunc68();
    virtual void Vfunc6C();
    virtual void Vfunc70();
    virtual void Vfunc74();
    virtual void Vfunc78();
    virtual void Vfunc7C();
    virtual void Vfunc80();
    virtual const FVector& GetOwnSize();   // the window's own size
    virtual FVector GetSize();             // used on the parent
    virtual void Vfunc8C();
    virtual void Vfunc90();
    virtual void Vfunc94();
    virtual void Vfunc98();
    virtual void Vfunc9C();
    virtual void VfuncA0();
    virtual Window* GetParent();
    virtual void VfuncA8();
    virtual void VfuncAC();
    virtual void VfuncB0();
    virtual void VfuncB4();
    virtual void VfuncB8();
    virtual void VfuncBC();
    virtual void VfuncC0();
    virtual void VfuncC4();
    virtual void VfuncC8();
    virtual void VfuncCC();
    virtual void VfuncD0();
    virtual void VfuncD4();
    virtual void VfuncD8();
    virtual void VfuncDC();
    virtual void VfuncE0();
    virtual void VfuncE4();
    virtual void VfuncE8();
    virtual void VfuncEC();
    virtual void VfuncF0();
    virtual void VfuncF4();
    virtual void VfuncF8();
    virtual void VfuncFC();
    virtual BOOL HasFlag(DWORD Flag);
    virtual void SetFlag(DWORD Flag);
    virtual void ClearFlag(DWORD Flag);

    char Unknown04[0x18];
    FVector Pos;                    // +0x1C: Pos_X/Y/Z
    char Unknown28[0x8C];
    Window* Parent;                 // +0xB4
    char UnknownB8[0x18];
    INT PlacementX;                 // +0xD0 (EPlacement)
    INT PlacementY;                 // +0xD4
    char UnknownD8[0x10];
    DWORD Flags;                    // +0xE8: 0x800 ListenForMouseClicks, 0x1000 IsModal
    char UnknownEC[0x14];
    WindowMover* Mover;             // +0x100
};

// FUNCTION: 0x109E3820 ?HasFlag@Window@@UAEHK@Z
BOOL Window::HasFlag(DWORD Flag)
{
    return (Flags & Flag) != 0;
}

// FUNCTION: 0x109E3840 ?SetFlag@Window@@UAEXK@Z
void Window::SetFlag(DWORD Flag)
{
    Flags |= Flag;
}

// FUNCTION: 0x109E3860 ?ClearFlag@Window@@UAEXK@Z
void Window::ClearFlag(DWORD Flag)
{
    Flags &= ~Flag;
}

// FUNCTION: 0x109E38E0 ?GetParent@Window@@UAEPAV1@XZ
Window* Window::GetParent()
{
    return Parent;
}

// FUNCTION: 0x10A52530 ?PlacedPosition@Window@@UAEPAVFVector@@PAV2@@Z
FVector* Window::PlacedPosition(FVector* Out)
{
    bool bCentered = GWindowManager->LayoutOrigin == 0;
    if (Mover)
        SetPosition(Mover->GetPosition());

    // The room the parent gives, at most the layout size.
    FVector Result, Avail;
    Window* Parent = GetParent();
    if (Parent)
    {
        Avail = Parent->GetSize();
        GWindowManager->GetUIScreenSize(&Result);
        if (Avail.X > Result.X)
            Avail.X = Result.X;
        if (Avail.Y > Result.Y)
            Avail.Y = Result.Y;
    }
    else
    {
        GWindowManager->GetUIScreenSize(&Result);
        Avail = FVector(Result.X, Result.Y, 0.f);
        if (bCentered)
        {
            FVector Screen = GWindowManager->LayoutToNormalized((INT)Result.X, (INT)Result.Y);
            Avail.X = Screen.X;
            Avail.Y = Screen.Y;
        }
    }

    if (PlacementX == PLACE_None)
        Result.X = Pos.X;
    else switch (PlacementX)
    {
    case PLACE_Center:
        if (bCentered)
            Result.X = Pos.X - GetOwnSize().X * 0.5f;
        else
            Result.X = (Avail.X - GetOwnSize().X) * 0.5f + Pos.X;
        break;
    case PLACE_Left:
        if (bCentered)
            Result.X = Pos.X - Avail.X * 0.5f;
        else
            Result.X = Pos.X;
        break;
    case PLACE_Right:
        if (bCentered)
            Result.X = Avail.X * 0.5f + Pos.X;
        else
            Result.X = Avail.X - GetOwnSize().X + Pos.X;
        break;
    }

    // y grows upwards.
    if (PlacementY == PLACE_None)
        Result.Y = Pos.Y;
    else switch (PlacementY)
    {
    case PLACE_Center:
        if (bCentered)
            Result.Y = GetOwnSize().Y * 0.5f + Pos.Y;
        else
            Result.Y = (Avail.Y - GetOwnSize().Y) * 0.5f + Pos.Y;
        break;
    case PLACE_Top:
        if (bCentered)
            Result.Y = Avail.Y * 0.5f + Pos.Y;
        else
            Result.Y = Pos.Y;
        break;
    case PLACE_Bottom:
        if (bCentered)
            Result.Y = -(Avail.Y * 0.5f);   // Pos_Y is ignored here
        else
            Result.Y = Avail.Y - GetOwnSize().Y + Pos.Y;
        break;
    }

    Result.Z = Pos.Z;
    *Out = Result;
    return Out;
}
