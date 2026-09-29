// Core/Core.h: the engine core's types, as far as matched functions need them.
// Layouts are from docs/engine.md ("Names", "Objects"); what nothing has
// shown yet is left out or named by offset.
#ifndef T3_CORE_CORE_H
#define T3_CORE_CORE_H

// --- Basic types (Unreal's names) ---------------------------------------------------

typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef unsigned long DWORD;
typedef signed char SBYTE;
typedef signed short SWORD;
typedef signed int INT;
typedef INT UBOOL;
typedef float FLOAT;
typedef double DOUBLE;
typedef char ANSICHAR;

#ifndef NULL
#define NULL 0
#endif

class FFrame;
class UObject;
class UField;
class UStruct;
class UFunction;
class UProperty;
class UState;
class UClass;

// --- Names --------------------------------------------------------------------------

enum EName
{
    NAME_None = 0,
};

// One 32-bit value: the low 16 bits index FName::Names, the high 16 bits are
// an instance number (not stock Unreal Engine 2, where it is a plain index).
class FName
{
public:
    FName() {}
    FName(EName N) : Value(N) {}

    UBOOL operator==(const FName& Other) const { return Value == Other.Value; }
    UBOOL operator!=(const FName& Other) const { return Value != Other.Value; }

    DWORD Value;
};

// --- Strings and math ---------------------------------------------------------------

// A dynamic array's header; the elements live at Data.
class FArray
{
public:
    INT Num() const { return ArrayNum; }

    void AddZeroed(INT ElementSize, INT Count);           // 0x10AF4CC0
    void Insert(INT Index, INT Count, INT ElementSize);    // 0x10AF4E80
    void Remove(INT Index, INT Count, INT ElementSize);    // 0x10AF3BD0

    void* Data;
    INT ArrayNum;
    INT ArrayMax;
};

// A typed view of the same header.
template<class T> class TArray : public FArray
{
public:
    T& operator()(INT i) { return ((T*)Data)[i]; }
    const T& operator()(INT i) const { return ((T*)Data)[i]; }
};

// A string: its characters and terminator in an array (TArray<ANSICHAR> in
// stock Unreal Engine 2), with these members out of line in this build.
class FString : public FArray
{
public:
    FString();                                  // 0x10AF8230
    ~FString();                                 // 0x10AF83B0

    FString& operator=(const ANSICHAR* Other);  // 0x10AF81C0
    FString& operator=(const FString& Other);   // 0x10AF8340
    const ANSICHAR* operator*() const;          // 0x10AF7F80
    static FString Printf(const ANSICHAR* Fmt, ...);   // 0x10AF8800

    INT Len() const;                            // 0x10AF7F70
};

// Ion Storm's memory allocator: the object GetAllocator (0x10905AA0) returns.
class Allocator
{
public:
    virtual void Unknown00();
    virtual void Unknown04();
    virtual void* Malloc(INT Size, INT Unknown1, INT Unknown2, INT Unknown3, INT Unknown4);                 // +0x08
    virtual void* Realloc(void* Block, INT Size, INT Unknown1, INT Unknown2, INT Unknown3, INT Unknown4);   // +0x0C
    virtual void Unknown10();
    virtual void Free(void* Block);                                                                         // +0x14
};

Allocator* GetAllocator();

INT appAtoi(const ANSICHAR* S);                            // 0x10AF3710
const ANSICHAR* appCmdLine();                              // 0x10AF4700
// Whether Stream holds -Param or /Param.
UBOOL ParseParam(const ANSICHAR* Stream, const ANSICHAR* Param);   // 0x10AF3F40
FLOAT appAtof(const ANSICHAR* S);

// Ion Storm's own string, next to FString: one pointer to the characters,
// with the length in the INT before them (the block is length + 5 bytes).
// NULL is the empty string. UObject::GetPathName returns one.
class String
{
public:
    String(const ANSICHAR* S);                  // 0x109081E0
    ~String()
    {
        if (Data)
        {
            void* Block = Data - 4;
            GetAllocator()->Free(Block);
            Data = NULL;
        }
    }

    const ANSICHAR* operator*() const { return Data ? Data : ""; }

    ANSICHAR* Data;
};

class FRotator;

class FVector
{
public:
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}

    FVector operator+(const FVector& V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator-(const FVector& V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
    FLOAT operator|(const FVector& V) const { return X * V.X + Y * V.Y + Z * V.Z; }
    friend FVector operator*(FLOAT Scale, const FVector& V) { return FVector(V.X * Scale, V.Y * Scale, V.Z * Scale); }
    FVector operator-() const { return FVector(-X, -Y, -Z); }
    FVector operator*(const FVector& V) const { return FVector(X * V.X, Y * V.Y, Z * V.Z); }
    FVector operator/(FLOAT Scale) const { FLOAT RScale = 1.f / Scale; return FVector(X * RScale, Y * RScale, Z * RScale); }
    FVector operator^(const FVector& V) const { return FVector(Y * V.Z - Z * V.Y, Z * V.X - X * V.Z, X * V.Y - Y * V.X); }
    FVector operator+=(const FVector& V) { X += V.X; Y += V.Y; Z += V.Z; return *this; }
    FVector operator-=(const FVector& V) { X -= V.X; Y -= V.Y; Z -= V.Z; return *this; }
    FVector operator*=(FLOAT Scale) { X *= Scale; Y *= Scale; Z *= Scale; return *this; }
    FVector operator/=(FLOAT V) { FLOAT RV = 1.f / V; X *= RV; Y *= RV; Z *= RV; return *this; }
    FVector operator*=(const FVector& V) { X *= V.X; Y *= V.Y; Z *= V.Z; return *this; }
    UBOOL operator==(const FVector& V) const { return X == V.X && Y == V.Y && Z == V.Z; }
    UBOOL operator!=(const FVector& V) const { return X != V.X || Y != V.Y || Z != V.Z; }
    UBOOL IsZero() const { return X == 0.f && Y == 0.f && Z == 0.f; }

    FVector SafeNormal() const;                 // 0x10967580
    FRotator Rotation() const;                  // 0x10B056C0

    FLOAT X, Y, Z;
};

// Unreal angles: 65536 units per turn.
class FRotator
{
public:
    FRotator() {}
    FRotator(INT InPitch, INT InYaw, INT InRoll) : Pitch(InPitch), Yaw(InYaw), Roll(InRoll) {}

    FRotator operator+(const FRotator& R) const { return FRotator(Pitch + R.Pitch, Yaw + R.Yaw, Roll + R.Roll); }
    FRotator operator-(const FRotator& R) const { return FRotator(Pitch - R.Pitch, Yaw - R.Yaw, Roll - R.Roll); }
    FRotator operator+=(const FRotator& R) { Pitch += R.Pitch; Yaw += R.Yaw; Roll += R.Roll; return *this; }
    FRotator operator-=(const FRotator& R) { Pitch -= R.Pitch; Yaw -= R.Yaw; Roll -= R.Roll; return *this; }
    UBOOL operator==(const FRotator& R) const { return Pitch == R.Pitch && Yaw == R.Yaw && Roll == R.Roll; }
    UBOOL operator!=(const FRotator& R) const { return Pitch != R.Pitch || Yaw != R.Yaw || Roll != R.Roll; }
    UBOOL IsZero() const { return ((Pitch & 65535) == 0) && ((Yaw & 65535) == 0) && ((Roll & 65535) == 0); }
    // Scaling truncates (Ion Storm; stock Unreal Engine 2 rounds with appRound).
    FRotator operator*(FLOAT Scale) const { return FRotator((INT)(Pitch * Scale), (INT)(Yaw * Scale), (INT)(Roll * Scale)); }
    friend FRotator operator*(FLOAT Scale, const FRotator& R) { return FRotator((INT)(R.Pitch * Scale), (INT)(R.Yaw * Scale), (INT)(R.Roll * Scale)); }
    FRotator operator*=(FLOAT Scale) { Pitch = (INT)(Pitch * Scale); Yaw = (INT)(Yaw * Scale); Roll = (INT)(Roll * Scale); return *this; }

    INT Pitch, Yaw, Roll;
};

// --- Output devices -----------------------------------------------------------------

// GLog's vtable[0] is FOutputDeviceFile::Serialize(const char*, EName).
class FOutputDevice
{
public:
    virtual void Serialize(const ANSICHAR* V, EName Event) = 0;

    // Formats and writes a line in the Log category (0x2F8); __cdecl.
    void Logf(const ANSICHAR* Fmt, ...);                    // 0x10AF3AA0
    void Logf(EName Event, const ANSICHAR* Fmt, ...);       // 0x10AF5230
};

// --- Objects ------------------------------------------------------------------------

#define DECLARE_FUNCTION(func) void func(FFrame& Stack, RESULT_DECL);
#define RESULT_DECL void* const Result

// A class's class object. Not stock Unreal Engine 2 (a static object there):
// Ion Storm keeps a pointer and builds the class on first use, as Unreal
// Engine 3 later does. The builder takes the package name; both helpers are
// only called from here.
#define DECLARE_STATIC_CLASS(TClass, TSuperClass, TWithinClass, TPackage) \
public: \
    typedef TSuperClass Super; \
    typedef TWithinClass WithinClass; \
    static UClass* StaticClass() \
    { \
        if (!PrivateStaticClass) \
        { \
            PrivateStaticClass = GetPrivateStaticClass##TClass(TPackage); \
            InitializePrivateStaticClass##TClass(); \
        } \
        return PrivateStaticClass; \
    } \
private: \
    static UClass* PrivateStaticClass; \
    static UClass* GetPrivateStaticClass##TClass(const ANSICHAR* Package); \
    static void InitializePrivateStaticClass##TClass(); \
public:

// Links a class object once built: its superclass (none for a class that is
// its own, UObject), the class its objects live in, and its own class; then
// registers it if the object system is already up.
#define IMPLEMENT_STATIC_CLASS_WITH(TClass, Initialized) \
    void TClass::InitializePrivateStaticClass##TClass() \
    { \
        if (Super::StaticClass() != PrivateStaticClass) \
            PrivateStaticClass->SuperField = Super::StaticClass(); \
        else \
            PrivateStaticClass->SuperField = NULL; \
        PrivateStaticClass->ClassWithin = WithinClass::StaticClass(); \
        PrivateStaticClass->Class = UClass::StaticClass(); \
        if (Initialized && PrivateStaticClass->GetClass() == UClass::StaticClass()) \
            PrivateStaticClass->Register(); \
    }
#define IMPLEMENT_STATIC_CLASS(TClass) IMPLEMENT_STATIC_CLASS_WITH(TClass, GetInitialized())
// Core's own classes see the flag itself.
#define IMPLEMENT_CORE_STATIC_CLASS(TClass) IMPLEMENT_STATIC_CLASS_WITH(TClass, GObjInitialized)

// The first 0x28 bytes match stock Unreal Engine 2 (the SDK checks Name, Class
// and Outer at runtime). Of the virtual functions, only CallFunction's slot is
// known; the others are named by their vtable offset.
class UObject
{
public:
    virtual ~UObject();
    virtual void Unknown04();
    virtual void Unknown08();
    virtual void Unknown0C();
    virtual void Unknown10();
    virtual void Unknown14();
    virtual void Unknown18();
    virtual void Unknown1C();
    virtual void Unknown20();
    virtual void Unknown24();
    virtual void Unknown28();
    virtual void Unknown2C();
    virtual void Unknown30();
    virtual void Unknown34();
    virtual void Unknown38();
    virtual void Unknown3C();
    virtual void Unknown40();

    // Runs a script function (execFinalFunction and the other calls).
    virtual void CallFunction(FFrame& Stack, RESULT_DECL, UFunction* Function);
    virtual void Unknown48();
    // Stock Unreal Engine 2's slot after ScriptConsoleExec; class objects call
    // it once linked (IMPLEMENT_STATIC_CLASS).
    virtual void Register();        // +0x4C
    virtual void Unknown50();
    virtual void Unknown54();
    virtual void Unknown58();
    // Ion Storm: execLetBool calls it with the bool property about to be assigned.
    virtual void Unknown5C(UProperty* Property);

    UClass* GetClass() const { return Class; }
    static UBOOL GetInitialized();  // 0x10AD1D60: GObjInitialized
    const FName GetFName() const { return Name; }

    // Writes the object's config properties (execSaveConfig); resets a
    // class's (execResetConfig).
    void SaveConfig(DWORD Flags, const ANSICHAR* Filename);

    UFunction* FindFunctionChecked(FName InName, UBOOL Global = 0);   // 0x10AD5D90
    UBOOL IsA(UClass* SomeBase) const;                              // 0x10AD1EE0

    // Package.Group.Name, up to StopOuter.
    String GetPathName(UObject* StopOuter = NULL);      // 0x10AD4FC0
    static void ResetConfig(UClass* Class);

    // Script natives, named by the game's native table (docs/engine.md,
    // "Script natives").
    DECLARE_FUNCTION(execAbs)
    DECLARE_FUNCTION(execAddAdd_Byte)
    DECLARE_FUNCTION(execAddAdd_Int)
    DECLARE_FUNCTION(execAddAdd_PreByte)
    DECLARE_FUNCTION(execAddAdd_PreInt)
    DECLARE_FUNCTION(execAddEqual_ByteByte)
    DECLARE_FUNCTION(execAddEqual_FloatFloat)
    DECLARE_FUNCTION(execAddEqual_IntInt)
    DECLARE_FUNCTION(execAddEqual_RotatorRotator)
    DECLARE_FUNCTION(execAddEqual_VectorVector)
    DECLARE_FUNCTION(execAdd_FloatFloat)
    DECLARE_FUNCTION(execAdd_IntInt)
    DECLARE_FUNCTION(execAdd_RotatorRotator)
    DECLARE_FUNCTION(execAdd_VectorVector)
    DECLARE_FUNCTION(execAndAnd_BoolBool)
    DECLARE_FUNCTION(execAnd_IntInt)
    DECLARE_FUNCTION(execArrayElement)
    DECLARE_FUNCTION(execAsc)
    DECLARE_FUNCTION(execAssert)
    DECLARE_FUNCTION(execAt_StringString)
    DECLARE_FUNCTION(execAtan)
    DECLARE_FUNCTION(execBoolToByte)
    DECLARE_FUNCTION(execBoolToFloat)
    DECLARE_FUNCTION(execBoolToInt)
    DECLARE_FUNCTION(execBoolToString)
    DECLARE_FUNCTION(execBoolVariable)
    DECLARE_FUNCTION(execByteConst)
    DECLARE_FUNCTION(execByteToBool)
    DECLARE_FUNCTION(execByteToFloat)
    DECLARE_FUNCTION(execByteToInt)
    DECLARE_FUNCTION(execByteToString)
    DECLARE_FUNCTION(execCaps)
    DECLARE_FUNCTION(execCase)
    DECLARE_FUNCTION(execChr)
    DECLARE_FUNCTION(execClamp)
    DECLARE_FUNCTION(execClassContext)
    DECLARE_FUNCTION(execClassIsChildOf)
    DECLARE_FUNCTION(execComplementEqual_FloatFloat)
    DECLARE_FUNCTION(execComplementEqual_StringString)
    DECLARE_FUNCTION(execComplement_PreInt)
    DECLARE_FUNCTION(execConcat_StringString)
    DECLARE_FUNCTION(execContext)
    DECLARE_FUNCTION(execCos)
    DECLARE_FUNCTION(execCross_VectorVector)
    DECLARE_FUNCTION(execDefaultVariable)
    DECLARE_FUNCTION(execDisable)
    DECLARE_FUNCTION(execDivideEqual_ByteByte)
    DECLARE_FUNCTION(execDivideEqual_FloatFloat)
    DECLARE_FUNCTION(execDivideEqual_IntFloat)
    DECLARE_FUNCTION(execDivideEqual_RotatorFloat)
    DECLARE_FUNCTION(execDivideEqual_VectorFloat)
    DECLARE_FUNCTION(execDivide_FloatFloat)
    DECLARE_FUNCTION(execDivide_IntInt)
    DECLARE_FUNCTION(execDivide_RotatorFloat)
    DECLARE_FUNCTION(execDivide_VectorFloat)
    DECLARE_FUNCTION(execDot_VectorVector)
    DECLARE_FUNCTION(execDynArrayElement)
    DECLARE_FUNCTION(execDynArrayInsert)
    DECLARE_FUNCTION(execDynArrayLength)
    DECLARE_FUNCTION(execDynArrayRemove)
    DECLARE_FUNCTION(execDynamicCast)
    DECLARE_FUNCTION(execDynamicLoadObject)
    DECLARE_FUNCTION(execEatString)
    DECLARE_FUNCTION(execEnable)
    DECLARE_FUNCTION(execEndFunctionParms)
    DECLARE_FUNCTION(execEqualEqual_BoolBool)
    DECLARE_FUNCTION(execEqualEqual_FloatFloat)
    DECLARE_FUNCTION(execEqualEqual_RotatorRotator)
    DECLARE_FUNCTION(execEqualEqual_StringString)
    DECLARE_FUNCTION(execEqualEqual_VectorVector)
    DECLARE_FUNCTION(execExp)
    DECLARE_FUNCTION(execFClamp)
    DECLARE_FUNCTION(execFMax)
    DECLARE_FUNCTION(execFMin)
    DECLARE_FUNCTION(execFRand)
    DECLARE_FUNCTION(execFinalFunction)
    DECLARE_FUNCTION(execFloatConst)
    DECLARE_FUNCTION(execFloatToBool)
    DECLARE_FUNCTION(execFloatToByte)
    DECLARE_FUNCTION(execFloatToInt)
    DECLARE_FUNCTION(execFloatToString)
    DECLARE_FUNCTION(execGetAxes)
    DECLARE_FUNCTION(execGetEnum)
    DECLARE_FUNCTION(execGetPropertyText)
    DECLARE_FUNCTION(execGetStateName)
    DECLARE_FUNCTION(execGetUnAxes)
    DECLARE_FUNCTION(execGlobalFunction)
    DECLARE_FUNCTION(execGotoLabel)
    DECLARE_FUNCTION(execGotoState)
    DECLARE_FUNCTION(execGreaterEqual_FloatFloat)
    DECLARE_FUNCTION(execGreaterEqual_IntInt)
    DECLARE_FUNCTION(execGreaterEqual_StringString)
    DECLARE_FUNCTION(execGreaterGreaterGreater_IntInt)
    DECLARE_FUNCTION(execGreaterGreater_IntInt)
    DECLARE_FUNCTION(execGreaterGreater_VectorRotator)
    DECLARE_FUNCTION(execGreater_FloatFloat)
    DECLARE_FUNCTION(execGreater_IntInt)
    DECLARE_FUNCTION(execGreater_StringString)
    DECLARE_FUNCTION(execHighNative0)
    DECLARE_FUNCTION(execHighNative1)
    DECLARE_FUNCTION(execHighNative10)
    DECLARE_FUNCTION(execHighNative11)
    DECLARE_FUNCTION(execHighNative12)
    DECLARE_FUNCTION(execHighNative13)
    DECLARE_FUNCTION(execHighNative14)
    DECLARE_FUNCTION(execHighNative15)
    DECLARE_FUNCTION(execHighNative2)
    DECLARE_FUNCTION(execHighNative3)
    DECLARE_FUNCTION(execHighNative4)
    DECLARE_FUNCTION(execHighNative5)
    DECLARE_FUNCTION(execHighNative6)
    DECLARE_FUNCTION(execHighNative7)
    DECLARE_FUNCTION(execHighNative8)
    DECLARE_FUNCTION(execHighNative9)
    DECLARE_FUNCTION(execInStr)
    DECLARE_FUNCTION(execInstanceVariable)
    DECLARE_FUNCTION(execIntConstByte)
    DECLARE_FUNCTION(execIntToByte)
    DECLARE_FUNCTION(execIntToFloat)
    DECLARE_FUNCTION(execIntToString)
    DECLARE_FUNCTION(execInvert)
    DECLARE_FUNCTION(execIsA)
    DECLARE_FUNCTION(execIsInState)
    DECLARE_FUNCTION(execJump)
    DECLARE_FUNCTION(execJumpIfNot)
    DECLARE_FUNCTION(execLeft)
    DECLARE_FUNCTION(execLen)
    DECLARE_FUNCTION(execLerp)
    DECLARE_FUNCTION(execLessEqual_FloatFloat)
    DECLARE_FUNCTION(execLessEqual_IntInt)
    DECLARE_FUNCTION(execLessEqual_StringString)
    DECLARE_FUNCTION(execLessLess_IntInt)
    DECLARE_FUNCTION(execLessLess_VectorRotator)
    DECLARE_FUNCTION(execLess_FloatFloat)
    DECLARE_FUNCTION(execLess_IntInt)
    DECLARE_FUNCTION(execLess_StringString)
    DECLARE_FUNCTION(execLet)
    DECLARE_FUNCTION(execLetBool)
    DECLARE_FUNCTION(execLocalVariable)
    DECLARE_FUNCTION(execLocalize)
    DECLARE_FUNCTION(execLog)
    DECLARE_FUNCTION(execLoge)
    DECLARE_FUNCTION(execMax)
    DECLARE_FUNCTION(execMetaCast)
    DECLARE_FUNCTION(execMid)
    DECLARE_FUNCTION(execMin)
    DECLARE_FUNCTION(execMirrorVectorByNormal)
    DECLARE_FUNCTION(execMultiplyEqual_ByteByte)
    DECLARE_FUNCTION(execMultiplyEqual_FloatFloat)
    DECLARE_FUNCTION(execMultiplyEqual_IntFloat)
    DECLARE_FUNCTION(execMultiplyEqual_RotatorFloat)
    DECLARE_FUNCTION(execMultiplyEqual_VectorFloat)
    DECLARE_FUNCTION(execMultiplyEqual_VectorVector)
    DECLARE_FUNCTION(execMultiplyMultiply_FloatFloat)
    DECLARE_FUNCTION(execMultiply_FloatFloat)
    DECLARE_FUNCTION(execMultiply_FloatRotator)
    DECLARE_FUNCTION(execMultiply_FloatVector)
    DECLARE_FUNCTION(execMultiply_IntInt)
    DECLARE_FUNCTION(execMultiply_RotatorFloat)
    DECLARE_FUNCTION(execMultiply_VectorFloat)
    DECLARE_FUNCTION(execMultiply_VectorVector)
    DECLARE_FUNCTION(execNameConst)
    DECLARE_FUNCTION(execNameToString)
    DECLARE_FUNCTION(execNativeParm)
    DECLARE_FUNCTION(execNew)
    DECLARE_FUNCTION(execNormal)
    DECLARE_FUNCTION(execNormalize)
    DECLARE_FUNCTION(execNotEqual_BoolBool)
    DECLARE_FUNCTION(execNotEqual_FloatFloat)
    DECLARE_FUNCTION(execNotEqual_RotatorRotator)
    DECLARE_FUNCTION(execNotEqual_StringString)
    DECLARE_FUNCTION(execNotEqual_VectorVector)
    DECLARE_FUNCTION(execNot_PreBool)
    DECLARE_FUNCTION(execObjectToString)
    DECLARE_FUNCTION(execOrOr_BoolBool)
    DECLARE_FUNCTION(execOr_IntInt)
    DECLARE_FUNCTION(execOrthoRotation)
    DECLARE_FUNCTION(execPercent_FloatFloat)
    DECLARE_FUNCTION(execPrimitiveCast)
    DECLARE_FUNCTION(execRand)
    DECLARE_FUNCTION(execResetConfig)
    DECLARE_FUNCTION(execRight)
    DECLARE_FUNCTION(execRotRand)
    DECLARE_FUNCTION(execRotationConst)
    DECLARE_FUNCTION(execRotatorToBool)
    DECLARE_FUNCTION(execRotatorToString)
    DECLARE_FUNCTION(execRotatorToVector)
    DECLARE_FUNCTION(execSaveConfig)
    DECLARE_FUNCTION(execSelf)
    DECLARE_FUNCTION(execSetPropertyText)
    DECLARE_FUNCTION(execSin)
    DECLARE_FUNCTION(execSmerp)
    DECLARE_FUNCTION(execSqrt)
    DECLARE_FUNCTION(execSquare)
    DECLARE_FUNCTION(execStaticSaveConfig)
    DECLARE_FUNCTION(execStop)
    DECLARE_FUNCTION(execStringConst)
    DECLARE_FUNCTION(execStringToBool)
    DECLARE_FUNCTION(execStringToByte)
    DECLARE_FUNCTION(execStringToFloat)
    DECLARE_FUNCTION(execStringToInt)
    DECLARE_FUNCTION(execStringToRotator)
    DECLARE_FUNCTION(execStringToVector)
    DECLARE_FUNCTION(execStructCmpEq)
    DECLARE_FUNCTION(execStructCmpNe)
    DECLARE_FUNCTION(execStructMember)
    DECLARE_FUNCTION(execSubtractEqual_ByteByte)
    DECLARE_FUNCTION(execSubtractEqual_FloatFloat)
    DECLARE_FUNCTION(execSubtractEqual_IntInt)
    DECLARE_FUNCTION(execSubtractEqual_RotatorRotator)
    DECLARE_FUNCTION(execSubtractEqual_VectorVector)
    DECLARE_FUNCTION(execSubtractSubtract_Byte)
    DECLARE_FUNCTION(execSubtractSubtract_Int)
    DECLARE_FUNCTION(execSubtractSubtract_PreByte)
    DECLARE_FUNCTION(execSubtractSubtract_PreInt)
    DECLARE_FUNCTION(execSubtract_FloatFloat)
    DECLARE_FUNCTION(execSubtract_IntInt)
    DECLARE_FUNCTION(execSubtract_PreFloat)
    DECLARE_FUNCTION(execSubtract_PreInt)
    DECLARE_FUNCTION(execSubtract_PreVector)
    DECLARE_FUNCTION(execSubtract_RotatorRotator)
    DECLARE_FUNCTION(execSubtract_VectorVector)
    DECLARE_FUNCTION(execSwitch)
    DECLARE_FUNCTION(execTan)
    DECLARE_FUNCTION(execUnicodeStringConst)
    DECLARE_FUNCTION(execVRand)
    DECLARE_FUNCTION(execVSize)
    DECLARE_FUNCTION(execVectorConst)
    DECLARE_FUNCTION(execVectorToBool)
    DECLARE_FUNCTION(execVectorToRotator)
    DECLARE_FUNCTION(execVectorToString)
    DECLARE_FUNCTION(execVirtualFunction)
    DECLARE_FUNCTION(execWarn)
    DECLARE_FUNCTION(execXorXor_BoolBool)
    DECLARE_FUNCTION(execXor_IntInt)

    INT Index;                      // 0x04: slot in GObjObjects
    UObject* HashNext;              // 0x08: GObjHash bucket chain
    struct FStateFrame* StateFrame; // 0x0C
    class ULinkerLoad* _Linker;     // 0x10
    INT _LinkerIndex;               // 0x14
    UObject* Outer;                 // 0x18
    DWORD ObjectFlags;              // 0x1C
    FName Name;                     // 0x20
    UClass* Class;                  // 0x24

    DECLARE_STATIC_CLASS(UObject, UObject, UObject, "Core")

protected:
    // Read directly by Core's classes (IMPLEMENT_CORE_STATIC_CLASS), through
    // GetInitialized by the others.
    static UBOOL GObjInitialized;   // 0x10F3E424
};

// SuperField is at 0x2C in this build (0x28 in stock Unreal Engine 2): one
// more field comes first, here or in UObject.
class UField : public UObject
{
public:
    DWORD Unknown28;                // 0x28
    UField* SuperField;             // 0x2C: all 287 classes chain up to Object
    UField* Next;                   // 0x30 (stock order, not yet seen)

    DECLARE_STATIC_CLASS(UField, UObject, UObject, "Core")
};

// An enumeration's value names.
class UEnum : public UField
{
public:
    TArray<FName> Names;            // 0x34

    DECLARE_STATIC_CLASS(UEnum, UField, UStruct, "Core")
};

// Script sits 4 bytes after its stock Unreal Engine 2 offset, like SuperField.
class UStruct : public UField
{
public:
    BYTE Unknown34[0x14];
    FArray Script;                  // 0x48: the bytecode (TArray<BYTE>)

    UBOOL IsChildOf(const UStruct* SomeBase) const
    {
        for (const UStruct* S = this; S; S = (const UStruct*)S->SuperField)
            if (S == SomeBase)
                return 1;
        return 0;
    }

    DECLARE_STATIC_CLASS(UStruct, UField, UObject, "Core")
};

class UFunction : public UStruct
{
    DECLARE_STATIC_CLASS(UFunction, UStruct, UState, "Core")
};

class UState : public UStruct
{
    DECLARE_STATIC_CLASS(UState, UStruct, UObject, "Core")
};

// A package: the outermost object of each file.
class UPackage : public UObject
{
    DECLARE_STATIC_CLASS(UPackage, UObject, UObject, "Core")
};

// UState has no known fields yet, so UClass's padding covers them (and
// UStruct's after Script): shrink it when they get some.
class UClass : public UState
{
public:
    BYTE Unknown54[0x50];
    UClass* ClassWithin;            // 0xA4: set by IMPLEMENT_STATIC_CLASS
    BYTE UnknownA8[0x40];
    UObject* ClassDefaultObject;    // 0xE8 (docs/engine.md: static, probable)

    DECLARE_STATIC_CLASS(UClass, UState, UPackage, "Core")
};

// The checked downcast; out of line where the compiler keeps a copy
// (Cast<UEnum> at 0x10B03230).
template<class T> T* Cast(UObject* Src)
{
    return Src && Src->IsA(T::StaticClass()) ? (T*)Src : NULL;
}

// --- Script execution ---------------------------------------------------------------

// A native's signature; the tables the interpreter dispatches opcodes and
// native indices through (FFrame::Step), and primitive casts
// (execPrimitiveCast).
typedef void (UObject::*Native)(FFrame& Stack, RESULT_DECL);
extern Native GNatives[];
extern Native GCasts[];

// What the last Step() evaluated as a variable: its property and address
// (execDynArrayLength reads them), and flags for the script compiler.
extern UProperty* GProperty;        // 0x10F45C30
extern BYTE* GPropAddr;             // 0x10F45C34
extern DWORD GRuntimeUCFlags;       // 0x10F45C44

enum ERuntimeUCFlags
{
    RUC_ArrayLengthSet = 0x01,      // a dynamic array's length was assigned
};

// The state of one running script function (stock Unreal Engine 2 layout; the
// natives read Object and Code at these offsets).
class FFrame : public FOutputDevice
{
public:
    virtual void Serialize(const ANSICHAR* V, EName Event);

    // Runs the next expression, writing its value to Result. Out of line in
    // this build (0x10B0FC50), where stock Unreal Engine 2 inlines it, like the
    // readers below that take a constant from the bytecode.
    void Step(UObject* Context, RESULT_DECL);

    INT ReadInt();                  // 0x10B0FC70
    INT ReadWord();                 // 0x10B0FC90
    FLOAT ReadFloat();              // 0x10B0FC80
    FName ReadName();               // 0x10B0FCD0

    // The linker folded ReadObject into ReadInt: they compile to the same code.
    UObject* ReadObject() { return (UObject*)ReadInt(); }

    UStruct* Node;                  // 0x04
    UObject* Object;                // 0x08
    BYTE* Code;                     // 0x0C
    BYTE* Locals;                   // 0x10
};

// A native's parameters, read in order by running their expressions.
#define P_GET_UBOOL(var)       DWORD var = 0; Stack.Step(Stack.Object, &var);
#define P_GET_BYTE(var)        BYTE var = 0; Stack.Step(Stack.Object, &var);
#define P_GET_INT(var)         INT var = 0; Stack.Step(Stack.Object, &var);
#define P_GET_FLOAT(var)       FLOAT var = 0.f; Stack.Step(Stack.Object, &var);
#define P_GET_NAME(var)        FName var = NAME_None; Stack.Step(Stack.Object, &var);
#define P_GET_STR(var)         FString var; Stack.Step(Stack.Object, &var);
#define P_GET_VECTOR(var)      FVector var; Stack.Step(Stack.Object, &var);
#define P_GET_ROTATOR(var)     FRotator var; Stack.Step(Stack.Object, &var);
#define P_GET_OBJECT(cls, var) cls* var = NULL; Stack.Step(Stack.Object, &var);
#define P_FINISH               Stack.Code++;

#endif
