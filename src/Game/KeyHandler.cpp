// Game/KeyHandler.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Provisional names: the class, its vtable (0x10E6C390, this function is
// slot 0) and the global are not identified yet. The event values look like
// Windows virtual-key codes (27 VK_ESCAPE, 38 VK_UP, 116 VK_F5, 117 VK_F6).

struct FIntList
{
    int Num;
    int Unknown04;
    int* Data;
};

class KeyHandlerChild
{
public:
    virtual void Vfunc00();
    virtual void Vfunc04();
    virtual void Vfunc08();
    virtual void Vfunc0C();
    virtual FIntList* GetList();    // +0x10
};

class KeyHandlerTarget
{
public:
    virtual void Vfunc00();
    virtual void Vfunc04();
    virtual void Vfunc08();
    virtual void Vfunc0C();
    virtual void Vfunc10();
    virtual void Vfunc14();
    virtual void Vfunc18();
    virtual void Vfunc1C();
    virtual void Vfunc20();
    virtual void Vfunc24();         // F5
    virtual void Vfunc28();         // F6
};

class KeyHandlerOwner
{
public:
    char Unknown00[0xBC];
    KeyHandlerTarget* Target;       // +0xBC
};

extern KeyHandlerOwner* GKeyHandlerOwner;

   // 0x10F35DEC

class KeyHandler
{
public:
    virtual void OnKey(int Key, int Param, int Unused1, int Unused2);  // +0x00
    virtual void Vfunc04();
    virtual void Vfunc08();
    virtual bool HasTarget();       // +0x0C: Unknown04 != 0
    virtual void Vfunc10();
    virtual void Vfunc14();
    virtual void Vfunc18();
    virtual void Vfunc1C();
    virtual void Activate();        // +0x20

    int Unknown04;
    char Unknown08[0x14];
    KeyHandlerChild* Child;         // +0x1C
    char Unknown20[0x14];
    bool bEscape;                   // +0x34
};

// FUNCTION: 0x10A85660 ?OnKey@KeyHandler@@UAEXHHHH@Z
void KeyHandler::OnKey(int Key, int Param, int Unused1, int Unused2)
{
    switch (Key)
    {
    case 38:
        if (Child)
        {
            FIntList* List = Child->GetList();
            for (int i = 0; i < List->Num; i++)
            {
                if (List->Data[i] == Param)
                {
                    Activate();
                    return;
                }
            }
        }
        break;
    case 27:
        bEscape = true;
        break;
    case 11:
        if (HasTarget())
            Activate();
        break;
    case 116:
        if (HasTarget())
            GKeyHandlerOwner->Target->Vfunc24();
        break;
    case 117:
        if (HasTarget())
            GKeyHandlerOwner->Target->Vfunc28();
        break;
    }
}
