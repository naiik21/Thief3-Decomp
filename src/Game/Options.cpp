// Game/Options.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// The game's options (options.ini); docs/engine.md, "Options".
class Options
{
public:
    int Get(int Index);
    void GetResolution(int* Width, int* Height);
    void ApplyVideo();

    // 640x480 ... 1600x1200, indexed by the Resolution option (0..4).
    static const int ResolutionWidths[5];
    static const int ResolutionHeights[5];

    int Unknown00;
    int Values[21];          // +0x04, indexed by the names table
};

// The Direct3D 8 render device (docs/engine.md, "Display").
class UD3DRenderDevice
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
    virtual void SetRes(class UViewport* Viewport, int Width, int Height, int Fullscreen, int MultiSampling);  // +0x84

    // Whether the adapter can multisample with this many samples (0x10C82440).
    int SupportsMultiSample(int Fullscreen, int Samples);
    // Index of the mode in DisplayModes, or negative.
    int SupportsDisplayMode(int Width, int Height, int BitDepth);

    struct FDisplayMode
    {
        int Width;
        int Height;
        int Unknown08[2];
    };

    char Unknown04[0x40D8];
    int UseVSync;                   // +0x40DC: read by SetRes
    char Unknown40E0[0x520];
    FDisplayMode* DisplayModes;     // +0x4600 (array data)
};

class UViewport
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
    virtual void Vfunc84();
    virtual void Vfunc88();
    virtual int Vfunc8C();        // +0x8C

    char Unknown04[0x54];
    UD3DRenderDevice* RenDev;       // +0x58
};

class UClient
{
public:
    char Unknown00[0x30];
    UViewport** Viewports;          // +0x30 (array data)
};

class UEngine
{
public:
    char Unknown00[0x38];
    UClient* Client;                // +0x38
};

extern UEngine* GEngine;

// FUNCTION: 0x10AB5AB0 ?Get@Options@@QAEHH@Z
int Options::Get(int Index)
{
    return Values[Index];
}

// FUNCTION: 0x10AB5AC0 ?GetResolution@Options@@QAEXPAH0@Z
void Options::GetResolution(int* Width, int* Height)
{
    int Resolution = Values[11];
    *Width = ResolutionWidths[Resolution];
    *Height = ResolutionHeights[Resolution];
}

// FUNCTION: 0x10AB61A0 ?ApplyVideo@Options@@QAEXXZ
void Options::ApplyVideo()
{
    int VSynch = Values[9] != 0;
    int Resolution = Values[11];
    int MultiSampling = Values[15];

    if (!GEngine || !GEngine->Client)
        return;
    UViewport* Viewport = GEngine->Client->Viewports[0];
    if (!Viewport)
        return;
    UD3DRenderDevice* RenDev = Viewport->RenDev;
    if (!RenDev)
        return;

    // Fall back to the most samples the adapter supports.
    if (MultiSampling > 1 && !RenDev->SupportsMultiSample(1, MultiSampling))
    {
        bool bFound = false;
        for (int i = MultiSampling - 1; i > 0 && !bFound; i--)
        {
            if (RenDev->SupportsMultiSample(1, i) == 1)
            {
                MultiSampling = i;
                bFound = true;
            }
        }
        if (!bFound)
            MultiSampling = 1;
        Values[15] = MultiSampling;
    }
    RenDev->UseVSync = VSynch;

    // Fall back to the largest resolution the adapter has.
    if (Resolution < 0)
        Resolution = 0;
    else if (Resolution >= 5)
        Resolution = 4;
    int Mode;
    for (Mode = Resolution; Mode > 0; Mode--)
    {
        int Width = ResolutionWidths[Mode];
        int Height = ResolutionHeights[Mode];
        int Index = RenDev->SupportsDisplayMode(Width, Height, 32);
        if (Index >= 0 && Width == RenDev->DisplayModes[Index].Width && Height == RenDev->DisplayModes[Index].Height)
            break;
    }
    if (Mode < 0)
        Mode = 0;
    if (Resolution != Mode)
    {
        Resolution = Mode;
        Values[11] = Mode;
    }

    if (Viewport->Vfunc8C())
        Viewport->RenDev->SetRes(Viewport, ResolutionWidths[Resolution], ResolutionHeights[Resolution], 1, MultiSampling);
}
