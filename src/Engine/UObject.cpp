// Engine/UObject.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"
                     // 0x10F46DE8

// An out parameter: its address when it is a variable, else a temporary. The
// caller saves GPropertyLValue before the first and restores it after the last.
#define P_GET_VECTOR_REF(var) FVector var##T; GPropAddr = NULL; GPropertyLValue = 1; Stack.Step(Stack.Object, &var##T);                               FVector* var = GPropAddr ? (FVector*)GPropAddr : &var##T;
#include <math.h>
#include <stdlib.h>
// Out parameters of a basic type, read as P_GET_VECTOR_REF reads vectors.
#define P_GET_INT_REF(var)   INT var##T = 0; GPropAddr = NULL; GPropertyLValue = 1; Stack.Step(Stack.Object, &var##T); \
                             INT* var = GPropAddr ? (INT*)GPropAddr : &var##T;
#define P_GET_BYTE_REF(var)  BYTE var##T = 0; GPropAddr = NULL; GPropertyLValue = 1; Stack.Step(Stack.Object, &var##T); \
                             BYTE* var = GPropAddr ? (BYTE*)GPropAddr : &var##T;
#define P_GET_FLOAT_REF(var) FLOAT var##T = 0.f; GPropAddr = NULL; GPropertyLValue = 1; Stack.Step(Stack.Object, &var##T); \
                             FLOAT* var = GPropAddr ? (FLOAT*)GPropAddr : &var##T;
#define P_GET_ROTATOR_REF(var) FRotator var##T; GPropAddr = NULL; GPropertyLValue = 1; Stack.Step(Stack.Object, &var##T); \
                               FRotator* var = GPropAddr ? (FRotator*)GPropAddr : &var##T;
                            // 0x10F7B038
#define CHECK_RUNAWAY \
    if (++GRunaway > 10000000) \
    { \
        if (!ParseParam(appCmdLine(), "norunaway")) \
            Stack.Logf((EName)0x2F9, "Runaway loop detected (over %i iterations)", 10000000); \
        GRunaway = 0; \
    }

float appFrand();

FVector appVRand();

// Set while the natives that write through their first operand (Let, +=, ++,
// dynamic array Insert/Remove, ...) evaluate it; 0x10F45C38.
extern DWORD GPropertyLValue;

// Ion Storm's Clamp orders its bounds first (the original execClamp, 0x10B03F50,
// compiles to the same two branches).
template<class T> inline T Clamp(const T X, const T Min, const T Max)
{
    return Min < Max ? (X < Min ? Min : X < Max ? X : Max)
                     : (X < Max ? Max : X < Min ? X : Min);
}

// Stock Unreal Engine 2 layout: ArrayDim and ElementSize follow UField.
class UProperty : public UField
{
public:
    // +0x48 to +0x5C are UObject's.
    virtual void Unknown60();
    virtual void Unknown64();
    virtual void Unknown68();
    virtual void Unknown6C();
    virtual void Unknown70();
    virtual void Unknown74();
    virtual void Unknown78();
    virtual void Unknown7C();
    virtual void Unknown80();
    virtual void Unknown84();
    virtual void Unknown88();
    virtual void Unknown8C();
    virtual void Unknown90();
    virtual void Unknown94();
    virtual void Unknown98();
    virtual void Unknown9C();
    virtual void UnknownA0();
    virtual void UnknownA4();
    virtual void UnknownA8();
    virtual void UnknownAC();
    virtual void CopySingleValue(void* Dest, void* Src, UObject* Obj);     // vtable +0xB0
    virtual void CopyCompleteValue(void* Dest, void* Src, UObject* Obj);   // vtable +0xB4
    virtual void DestroyValue(void* Dest) const;   // vtable +0xB8
    virtual void UnknownBC();
    virtual void UnknownC0();
    virtual void UnknownC4();
    virtual void UnknownC8();
    // Ion Storm: temporary storage for a value, and its release.
    virtual BYTE* CreateDefaultValue();            // vtable +0xCC
    virtual void DestroyDefaultValue(BYTE* Value); // vtable +0xD0

    INT ArrayDim;                   // 0x34
    INT ElementSize;                // 0x38
    BYTE Pad3C[0xC];
    INT Offset;                     // 0x48: into the object, or the frame's locals
    BYTE Pad4C[0x14];
};

class UArrayProperty : public UProperty
{
public:
    UProperty* Inner;               // 0x60
};

// A coordinate system: an origin and three axes.
class FCoords
{
public:
    FVector Origin, XAxis, YAxis, ZAxis;

    FCoords() {}
    FCoords(const FVector& InOrigin, const FVector& InX, const FVector& InY, const FVector& InZ)
        : Origin(InOrigin), XAxis(InX), YAxis(InY), ZAxis(InZ) {}

    FRotator OrthoRotation() const;             // 0x10B05EF0
    FCoords& operator*=(const FRotator& Rot);   // 0x109620B0
    FCoords operator*(const FRotator& Rot) const { return FCoords(*this) *= Rot; }
    FCoords& operator/=(const FRotator& Rot);   // 0x10961AF0
    FCoords operator/(const FRotator& Rot) const { return FCoords(*this) /= Rot; }
};

// The unit coordinate system (GMath.UnitCoords in stock Unreal Engine 2).
extern FCoords GUnitCoords;

// Stock Unreal Engine 2's math wrappers (UnVcWin32.h) and templates (UnTemplate.h).
inline DOUBLE appSqrt(DOUBLE Value) { return sqrt(Value); }

inline DOUBLE appSin(DOUBLE Value) { return sin(Value); }

inline DOUBLE appCos(DOUBLE Value) { return cos(Value); }

inline DOUBLE appTan(DOUBLE Value) { return tan(Value); }

inline DOUBLE appAtan(DOUBLE Value) { return atan(Value); }

inline DOUBLE appLoge(DOUBLE Value) { return log(Value); }

inline DOUBLE appExp(DOUBLE Value) { return exp(Value); }

inline DOUBLE appFmod(DOUBLE Y, DOUBLE X) { return fmod(Y, X); }

inline DOUBLE appPow(DOUBLE A, DOUBLE B) { return pow(A, B); }

// Ion Storm's own, out of line (execRand calls it, not the CRT's rand).
INT appRand();

                                  // 0x10AF3A20

template<class T> inline T Abs(const T A) { return (A >= (T)0) ? A : -A; }

template<class T> inline T Min(const T A, const T B) { return (A <= B) ? A : B; }

template<class T> inline T Max(const T A, const T B) { return (A >= B) ? A : B; }

// A state's running frame (UObject::StateFrame); StateNode sits 4 bytes after
// its stock Unreal Engine 2 offset.
struct FStateFrame : public FFrame
{
    DWORD Unknown14[2];
    UState* StateNode;              // 0x1C
};

class UBoolProperty : public UProperty
{
public:
    DWORD BitMask;                  // 0x60
};

// Ion Storm's runaway loop check: counts jumps, and warns (unless -norunaway)
// past ten million.
extern INT GRunaway;

// Transforms V by Coords into Out (0x109672E0); FVector::TransformVectorBy
// wraps it in stock Unreal Engine 2.
void TransformVectorBy(const FCoords& Coords, const FVector& V, FVector& Out);

inline FVector TransformVectorBy(const FVector& V, const FCoords& Coords)
{
    FVector Out;
    TransformVectorBy(Coords, V, Out);
    return Out;
}

// FUNCTION: 0x10AD1D60 ?GetInitialized@UObject@@SAHXZ
UBOOL UObject::GetInitialized()
{
    return GObjInitialized;
}

// FUNCTION: 0x10AFD2F0 ?execLocalVariable@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execLocalVariable(FFrame& Stack, RESULT_DECL)
{
    GProperty = (UProperty*)Stack.ReadObject();
    GPropAddr = Stack.Locals + GProperty->Offset;
    if (Result)
        GProperty->CopyCompleteValue(Result, GPropAddr, NULL);
}

// FUNCTION: 0x10AFD470 ?execDynArrayLength@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execDynArrayLength(FFrame& Stack, RESULT_DECL)
{
    GProperty = NULL;
    Stack.Step(this, NULL);
    if (!GPropAddr)
        return;
    FArray* Array = (FArray*)GPropAddr;
    if (!Result)
        GRuntimeUCFlags |= RUC_ArrayLengthSet;
    else
        *(INT*)Result = Array->Num();
}

// FUNCTION: 0x10AFD4B0 ?execBoolVariable@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execBoolVariable(FFrame& Stack, RESULT_DECL)
{
    // Get bool variable.
    BYTE B = *Stack.Code++;
    UBoolProperty* Property = *(UBoolProperty**)Stack.Code;
    (this->*GNatives[B])(Stack, NULL);
    GProperty = Property;

    // A copy, not a pointer to the bool: EX_Let takes care of bools itself.
    if (Result)
        *(DWORD*)Result = (GPropAddr && (*(DWORD*)GPropAddr & Property->BitMask)) ? 1 : 0;
}

// FUNCTION: 0x10AFD510 ?execNativeParm@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execNativeParm(FFrame& Stack, RESULT_DECL)
{
    UProperty* Property = (UProperty*)Stack.ReadObject();
    if (Result)
    {
        GPropAddr = Stack.Locals + Property->Offset;
        Property->CopyCompleteValue(Result, Stack.Locals + Property->Offset, NULL);
    }
}

// FUNCTION: 0x10AFD550 ?execEndFunctionParms@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execEndFunctionParms(FFrame& Stack, RESULT_DECL)
{
    Stack.Code--;
}

// FUNCTION: 0x10AFD560 ?execStop@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execStop(FFrame& Stack, RESULT_DECL)
{
    Stack.Code = NULL;
}

// FUNCTION: 0x10AFD5D0 ?execAssert@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execAssert(FFrame& Stack, RESULT_DECL)
{
    INT wLine = Stack.ReadWord();
    P_GET_UBOOL(Assertion);
    if (!Assertion)
        Stack.Logf((EName)0x2F9, "Assertion failed, line %i", wLine);
}

// FUNCTION: 0x10AFD770 ?execLetBool@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execLetBool(FFrame& Stack, RESULT_DECL)
{
    GPropAddr = NULL;
    GProperty = NULL;
    GPropertyLValue = 1;
    Stack.Step(Stack.Object, NULL);
    UBoolProperty* BoolProperty = (UBoolProperty*)GProperty;
    DWORD* BoolAddr = (DWORD*)GPropAddr;
    GPropertyLValue = 0;
    DWORD NewValue = 0;
    Unknown5C(GProperty);
    Stack.Step(Stack.Object, &NewValue);
    if (BoolAddr)
    {
        if (NewValue)
            *BoolAddr |= BoolProperty->BitMask;
        else
            *BoolAddr &= ~BoolProperty->BitMask;
    }
}

// FUNCTION: 0x10AFD810 ?execSelf@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execSelf(FFrame& Stack, RESULT_DECL)
{
    *(UObject**)Result = this;
}

// FUNCTION: 0x10AFD8C0 ?execVirtualFunction@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execVirtualFunction(FFrame& Stack, RESULT_DECL)
{
    CallFunction(Stack, Result, FindFunctionChecked(Stack.ReadName()));
}

// FUNCTION: 0x10AFD900 ?execFinalFunction@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execFinalFunction(FFrame& Stack, RESULT_DECL)
{
    CallFunction(Stack, Result, (UFunction*)Stack.ReadObject());
}

// FUNCTION: 0x10AFD930 ?execGlobalFunction@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execGlobalFunction(FFrame& Stack, RESULT_DECL)
{
    CallFunction(Stack, Result, FindFunctionChecked(Stack.ReadName(), 1));
}

// FUNCTION: 0x10AFDB70 ?execFloatConst@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execFloatConst(FFrame& Stack, RESULT_DECL)
{
    *(FLOAT*)Result = Stack.ReadFloat();
}

// FUNCTION: 0x10AFDBB0 ?execNameConst@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execNameConst(FFrame& Stack, RESULT_DECL)
{
    *(FName*)Result = Stack.ReadName();
}

// FUNCTION: 0x10AFDBD0 ?execByteConst@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execByteConst(FFrame& Stack, RESULT_DECL)
{
    *(BYTE*)Result = *Stack.Code++;
}

// FUNCTION: 0x10AFDC10 ?execIntConstByte@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execIntConstByte(FFrame& Stack, RESULT_DECL)
{
    *(INT*)Result = *Stack.Code;
    Stack.Code++;
}

// FUNCTION: 0x10AFDC30 ?execDynamicCast@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execDynamicCast(FFrame& Stack, RESULT_DECL)
{
    UClass* Class = (UClass*)Stack.ReadObject();
    P_GET_OBJECT(UObject, Castee);
    *(UObject**)Result = (Castee && Castee->IsA(Class)) ? Castee : NULL;
}

// FUNCTION: 0x10AFDC90 ?execPrimitiveCast@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execPrimitiveCast(FFrame& Stack, RESULT_DECL)
{
    INT B = *Stack.Code++;
    (Stack.Object->*GCasts[B])(Stack, Result);
}

// FUNCTION: 0x10AFDCB0 ?execByteToInt@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execByteToInt(FFrame& Stack, RESULT_DECL)
{
    P_GET_BYTE(V);
    *(INT*)Result = V;
}

// FUNCTION: 0x10AFDCE0 ?execByteToBool@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execByteToBool(FFrame& Stack, RESULT_DECL)
{
    P_GET_BYTE(V);
    *(UBOOL*)Result = (V != 0);
}

// FUNCTION: 0x10AFDD10 ?execByteToFloat@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execByteToFloat(FFrame& Stack, RESULT_DECL)
{
    P_GET_BYTE(V);
    *(FLOAT*)Result = V;
}

// FUNCTION: 0x10AFDD40 ?execByteToString@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execByteToString(FFrame& Stack, RESULT_DECL)
{
    P_GET_BYTE(B);
    *(FString*)Result = FString::Printf("%i", B);
}

// FUNCTION: 0x10AFDDC0 ?execIntToByte@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execIntToByte(FFrame& Stack, RESULT_DECL)
{
    P_GET_INT(A);
    *(BYTE*)Result = (BYTE)A;
}

// FUNCTION: 0x10AFDDF0 ?execIntToFloat@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execIntToFloat(FFrame& Stack, RESULT_DECL)
{
    P_GET_INT(V);
    *(FLOAT*)Result = V;
}

// FUNCTION: 0x10AFDE20 ?execIntToString@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execIntToString(FFrame& Stack, RESULT_DECL)
{
    P_GET_INT(V);
    *(FString*)Result = FString::Printf("%i", V);
}

// FUNCTION: 0x10AFDEA0 ?execBoolToByte@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execBoolToByte(FFrame& Stack, RESULT_DECL)
{
    P_GET_UBOOL(A);
    *(BYTE*)Result = A & 1;
}

// FUNCTION: 0x10AFDED0 ?execBoolToInt@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execBoolToInt(FFrame& Stack, RESULT_DECL)
{
    P_GET_UBOOL(V);
    *(INT*)Result = V & 1;
}

// FUNCTION: 0x10AFDF00 ?execBoolToFloat@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execBoolToFloat(FFrame& Stack, RESULT_DECL)
{
    P_GET_UBOOL(A);
    *(FLOAT*)Result = (INT)(A & 1);
}

// FUNCTION: 0x10AFDF40 ?execBoolToString@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execBoolToString(FFrame& Stack, RESULT_DECL)
{
    P_GET_UBOOL(A);
    *(FString*)Result = A ? "True" : "False";
}

// FUNCTION: 0x10AFDF80 ?execFloatToByte@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execFloatToByte(FFrame& Stack, RESULT_DECL)
{
    P_GET_FLOAT(V);
    *(BYTE*)Result = (BYTE)V;
}

// FUNCTION: 0x10AFDFB0 ?execFloatToInt@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execFloatToInt(FFrame& Stack, RESULT_DECL)
{
    P_GET_FLOAT(V);
    *(INT*)Result = (INT)V;
}

// FUNCTION: 0x10AFDFE0 ?execFloatToBool@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execFloatToBool(FFrame& Stack, RESULT_DECL)
{
    P_GET_FLOAT(V);
    *(DWORD*)Result = V != 0.f;
}

// FUNCTION: 0x10AFE0E0 ?execStringToByte@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execStringToByte(FFrame& Stack, RESULT_DECL)
{
    P_GET_STR(Str);
    *(BYTE*)Result = appAtoi(*Str);
}

// FUNCTION: 0x10AFE160 ?execStringToInt@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execStringToInt(FFrame& Stack, RESULT_DECL)
{
    P_GET_STR(Str);
    *(INT*)Result = appAtoi(*Str);
}

// FUNCTION: 0x10AFE2E0 ?execStringToFloat@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execStringToFloat(FFrame& Stack, RESULT_DECL)
{
    P_GET_STR(Str);
    *(FLOAT*)Result = appAtof(*Str);
}

// FUNCTION: 0x10AFE360 ?execNot_PreBool@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execNot_PreBool(FFrame& Stack, RESULT_DECL)
{
    P_GET_UBOOL(A);
    P_FINISH;
    *(DWORD*)Result = !A;
}

// FUNCTION: 0x10AFE3A0 ?execEqualEqual_BoolBool@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execEqualEqual_BoolBool(FFrame& Stack, RESULT_DECL)
{
    P_GET_UBOOL(A);
    P_GET_UBOOL(B);
    P_FINISH;
    *(DWORD*)Result = ((!A) == (!B));
}

// FUNCTION: 0x10AFE410 ?execNotEqual_BoolBool@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execNotEqual_BoolBool(FFrame& Stack, RESULT_DECL)
{
    P_GET_UBOOL(A);
    P_GET_UBOOL(B);
    P_FINISH;
    *(DWORD*)Result = ((!A) != (!B));
}

// FUNCTION: 0x10AFE480 ?execAndAnd_BoolBool@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execAndAnd_BoolBool(FFrame& Stack, RESULT_DECL)
{
    P_GET_UBOOL(A);
    _WORD W;
    Stack.Code++;
    W = *(_WORD*)Stack.Code;
    Stack.Code += 2;
    if (A)
    {
        P_GET_UBOOL(B);
        *(DWORD*)Result = A && B;
        Stack.Code++;
    }
    else
    {
        *(DWORD*)Result = 0;
        Stack.Code += W;
    }
}

// FUNCTION: 0x10AFE520 ?execXorXor_BoolBool@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execXorXor_BoolBool(FFrame& Stack, RESULT_DECL)
{
    P_GET_UBOOL(A);
    P_GET_UBOOL(B);
    P_FINISH;
    *(DWORD*)Result = !A ^ !B;
}

// FUNCTION: 0x10AFE580 ?execOrOr_BoolBool@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execOrOr_BoolBool(FFrame& Stack, RESULT_DECL)
{
    P_GET_UBOOL(A);
    _WORD W;
    Stack.Code++;
    W = *(_WORD*)Stack.Code;
    Stack.Code += 2;
    if (!A)
    {
        P_GET_UBOOL(B);
        *(DWORD*)Result = A || B;
        Stack.Code++;
    }
    else
    {
        *(DWORD*)Result = 1;
        Stack.Code += W;
    }
}

// FUNCTION: 0x10AFE620 ?execMultiplyEqual_ByteByte@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execMultiplyEqual_ByteByte(FFrame& Stack, RESULT_DECL)
{
    DWORD SavedLValue = GPropertyLValue;
    P_GET_BYTE_REF(A);
    GPropertyLValue = SavedLValue;
    P_GET_BYTE(B);
    P_FINISH;
    *(BYTE*)Result = (*A *= B);
}

// FUNCTION: 0x10AFE6A0 ?execDivideEqual_ByteByte@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execDivideEqual_ByteByte(FFrame& Stack, RESULT_DECL)
{
    DWORD SavedLValue = GPropertyLValue;
    P_GET_BYTE_REF(A);
    GPropertyLValue = SavedLValue;
    P_GET_BYTE(B);
    P_FINISH;
    *(BYTE*)Result = B ? (*A /= B) : 0;
}

// FUNCTION: 0x10AFE740 ?execAddEqual_ByteByte@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execAddEqual_ByteByte(FFrame& Stack, RESULT_DECL)
{
    DWORD SavedLValue = GPropertyLValue;
    P_GET_BYTE_REF(A);
    GPropertyLValue = SavedLValue;
    P_GET_BYTE(B);
    P_FINISH;
    *(BYTE*)Result = (*A += B);
}

// FUNCTION: 0x10AFE7C0 ?execSubtractEqual_ByteByte@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execSubtractEqual_ByteByte(FFrame& Stack, RESULT_DECL)
{
    DWORD SavedLValue = GPropertyLValue;
    P_GET_BYTE_REF(A);
    GPropertyLValue = SavedLValue;
    P_GET_BYTE(B);
    P_FINISH;
    *(BYTE*)Result = (*A -= B);
}

// FUNCTION: 0x10AFE840 ?execAddAdd_PreByte@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execAddAdd_PreByte(FFrame& Stack, RESULT_DECL)
{
    DWORD SavedLValue = GPropertyLValue;
    P_GET_BYTE_REF(A);
    GPropertyLValue = SavedLValue;
    P_FINISH;
    *(BYTE*)Result = ++(*A);
}

// FUNCTION: 0x10AFE8A0 ?execSubtractSubtract_PreByte@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execSubtractSubtract_PreByte(FFrame& Stack, RESULT_DECL)
{
    DWORD SavedLValue = GPropertyLValue;
    P_GET_BYTE_REF(A);
    GPropertyLValue = SavedLValue;
    P_FINISH;
    *(BYTE*)Result = --(*A);
}

// FUNCTION: 0x10AFE900 ?execAddAdd_Byte@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execAddAdd_Byte(FFrame& Stack, RESULT_DECL)
{
    DWORD SavedLValue = GPropertyLValue;
    P_GET_BYTE_REF(A);
    GPropertyLValue = SavedLValue;
    P_FINISH;
    *(BYTE*)Result = (*A)++;
}

// FUNCTION: 0x10AFE960 ?execSubtractSubtract_Byte@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execSubtractSubtract_Byte(FFrame& Stack, RESULT_DECL)
{
    DWORD SavedLValue = GPropertyLValue;
    P_GET_BYTE_REF(A);
    GPropertyLValue = SavedLValue;
    P_FINISH;
    *(BYTE*)Result = (*A)--;
}

// FUNCTION: 0x10AFE9C0 ?execComplement_PreInt@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execComplement_PreInt(FFrame& Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_FINISH;
    *(INT*)Result = ~A;
}

// FUNCTION: 0x10AFEA00 ?execGreaterGreaterGreater_IntInt@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execGreaterGreaterGreater_IntInt(FFrame& Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(INT*)Result = ((DWORD)A) >> B;
}

// FUNCTION: 0x10AFEA60 ?execSubtract_PreInt@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execSubtract_PreInt(FFrame& Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_FINISH;
    *(INT*)Result = -A;
}

// FUNCTION: 0x10AFEAA0 ?execMultiply_IntInt@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execMultiply_IntInt(FFrame& Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(INT*)Result = A * B;
}

// FUNCTION: 0x10AFEB00 ?execDivide_IntInt@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execDivide_IntInt(FFrame& Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(INT*)Result = B ? A / B : 0;
}

// FUNCTION: 0x10AFEB60 ?execAdd_IntInt@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execAdd_IntInt(FFrame& Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(INT*)Result = A + B;
}

// FUNCTION: 0x10AFEBC0 ?execSubtract_IntInt@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execSubtract_IntInt(FFrame& Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(INT*)Result = A - B;
}

// FUNCTION: 0x10AFEC20 ?execLessLess_IntInt@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execLessLess_IntInt(FFrame& Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(INT*)Result = A << B;
}

// FUNCTION: 0x10AFEC80 ?execGreaterGreater_IntInt@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execGreaterGreater_IntInt(FFrame& Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(INT*)Result = A >> B;
}

// FUNCTION: 0x10AFECE0 ?execLess_IntInt@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execLess_IntInt(FFrame& Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(DWORD*)Result = A < B;
}

// FUNCTION: 0x10AFED40 ?execGreater_IntInt@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execGreater_IntInt(FFrame& Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(DWORD*)Result = A > B;
}

// FUNCTION: 0x10AFEDA0 ?execLessEqual_IntInt@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execLessEqual_IntInt(FFrame& Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(DWORD*)Result = A <= B;
}

// FUNCTION: 0x10AFEE00 ?execGreaterEqual_IntInt@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execGreaterEqual_IntInt(FFrame& Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(DWORD*)Result = A >= B;
}

// FUNCTION: 0x10AFEE60 ?execAnd_IntInt@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execAnd_IntInt(FFrame& Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(INT*)Result = A & B;
}

// FUNCTION: 0x10AFEEC0 ?execXor_IntInt@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execXor_IntInt(FFrame& Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(INT*)Result = A ^ B;
}

// FUNCTION: 0x10AFEF20 ?execOr_IntInt@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execOr_IntInt(FFrame& Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(INT*)Result = A | B;
}

// FUNCTION: 0x10AFEF80 ?execMultiplyEqual_IntFloat@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execMultiplyEqual_IntFloat(FFrame& Stack, RESULT_DECL)
{
    DWORD SavedLValue = GPropertyLValue;
    P_GET_INT_REF(A);
    GPropertyLValue = SavedLValue;
    P_GET_FLOAT(B);
    P_FINISH;
    *(INT*)Result = *A = (INT)(*A * B);
}

// FUNCTION: 0x10AFF010 ?execDivideEqual_IntFloat@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execDivideEqual_IntFloat(FFrame& Stack, RESULT_DECL)
{
    DWORD SavedLValue = GPropertyLValue;
    P_GET_INT_REF(A);
    GPropertyLValue = SavedLValue;
    P_GET_FLOAT(B);
    P_FINISH;
    *(INT*)Result = *A = (INT)(B ? *A / B : 0.f);
}

// FUNCTION: 0x10AFF0C0 ?execAddEqual_IntInt@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execAddEqual_IntInt(FFrame& Stack, RESULT_DECL)
{
    DWORD SavedLValue = GPropertyLValue;
    P_GET_INT_REF(A);
    GPropertyLValue = SavedLValue;
    P_GET_INT(B);
    P_FINISH;
    *(INT*)Result = (*A += B);
}

// FUNCTION: 0x10AFF150 ?execSubtractEqual_IntInt@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execSubtractEqual_IntInt(FFrame& Stack, RESULT_DECL)
{
    DWORD SavedLValue = GPropertyLValue;
    P_GET_INT_REF(A);
    GPropertyLValue = SavedLValue;
    P_GET_INT(B);
    P_FINISH;
    *(INT*)Result = (*A -= B);
}

// FUNCTION: 0x10AFF1E0 ?execAddAdd_PreInt@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execAddAdd_PreInt(FFrame& Stack, RESULT_DECL)
{
    DWORD SavedLValue = GPropertyLValue;
    P_GET_INT_REF(A);
    GPropertyLValue = SavedLValue;
    P_FINISH;
    *(INT*)Result = ++(*A);
}

// FUNCTION: 0x10AFF250 ?execSubtractSubtract_PreInt@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execSubtractSubtract_PreInt(FFrame& Stack, RESULT_DECL)
{
    DWORD SavedLValue = GPropertyLValue;
    P_GET_INT_REF(A);
    GPropertyLValue = SavedLValue;
    P_FINISH;
    *(INT*)Result = --(*A);
}

// FUNCTION: 0x10AFF2C0 ?execAddAdd_Int@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execAddAdd_Int(FFrame& Stack, RESULT_DECL)
{
    DWORD SavedLValue = GPropertyLValue;
    P_GET_INT_REF(A);
    GPropertyLValue = SavedLValue;
    P_FINISH;
    *(INT*)Result = (*A)++;
}

// FUNCTION: 0x10AFF330 ?execSubtractSubtract_Int@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execSubtractSubtract_Int(FFrame& Stack, RESULT_DECL)
{
    DWORD SavedLValue = GPropertyLValue;
    P_GET_INT_REF(A);
    GPropertyLValue = SavedLValue;
    P_FINISH;
    *(INT*)Result = (*A)--;
}

// FUNCTION: 0x10AFF3A0 ?execRand@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execRand(FFrame& Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_FINISH;
    *(INT*)Result = A > 0 ? (appRand() % A) : 0;
}

// FUNCTION: 0x10AFF3F0 ?execSubtract_PreFloat@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execSubtract_PreFloat(FFrame& Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_FINISH;
    *(FLOAT*)Result = -A;
}

// FUNCTION: 0x10AFF430 ?execMultiplyMultiply_FloatFloat@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execMultiplyMultiply_FloatFloat(FFrame& Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_GET_FLOAT(B);
    P_FINISH;
    *(FLOAT*)Result = appPow(A, B);
}

// FUNCTION: 0x10AFF490 ?execMultiply_FloatFloat@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execMultiply_FloatFloat(FFrame& Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_GET_FLOAT(B);
    P_FINISH;
    *(FLOAT*)Result = A * B;
}

// FUNCTION: 0x10AFF4E0 ?execDivide_FloatFloat@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execDivide_FloatFloat(FFrame& Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_GET_FLOAT(B);
    P_FINISH;
    *(FLOAT*)Result = A / B;
}

// FUNCTION: 0x10AFF530 ?execPercent_FloatFloat@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execPercent_FloatFloat(FFrame& Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_GET_FLOAT(B);
    P_FINISH;
    *(FLOAT*)Result = appFmod(A, B);
}

// FUNCTION: 0x10AFF590 ?execAdd_FloatFloat@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execAdd_FloatFloat(FFrame& Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_GET_FLOAT(B);
    P_FINISH;
    *(FLOAT*)Result = A + B;
}

// FUNCTION: 0x10AFF5E0 ?execSubtract_FloatFloat@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execSubtract_FloatFloat(FFrame& Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_GET_FLOAT(B);
    P_FINISH;
    *(FLOAT*)Result = A - B;
}

// FUNCTION: 0x10AFF630 ?execLess_FloatFloat@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execLess_FloatFloat(FFrame& Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_GET_FLOAT(B);
    P_FINISH;
    *(DWORD*)Result = A < B;
}

// FUNCTION: 0x10AFF6A0 ?execGreater_FloatFloat@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execGreater_FloatFloat(FFrame& Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_GET_FLOAT(B);
    P_FINISH;
    *(DWORD*)Result = A > B;
}

// FUNCTION: 0x10AFF710 ?execLessEqual_FloatFloat@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execLessEqual_FloatFloat(FFrame& Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_GET_FLOAT(B);
    P_FINISH;
    *(DWORD*)Result = A <= B;
}

// FUNCTION: 0x10AFF780 ?execGreaterEqual_FloatFloat@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execGreaterEqual_FloatFloat(FFrame& Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_GET_FLOAT(B);
    P_FINISH;
    *(DWORD*)Result = A >= B;
}

// FUNCTION: 0x10AFF7F0 ?execEqualEqual_FloatFloat@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execEqualEqual_FloatFloat(FFrame& Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_GET_FLOAT(B);
    P_FINISH;
    *(DWORD*)Result = A == B;
}

// FUNCTION: 0x10AFF860 ?execNotEqual_FloatFloat@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execNotEqual_FloatFloat(FFrame& Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_GET_FLOAT(B);
    P_FINISH;
    *(DWORD*)Result = A != B;
}

// FUNCTION: 0x10AFF8D0 ?execMultiplyEqual_FloatFloat@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execMultiplyEqual_FloatFloat(FFrame& Stack, RESULT_DECL)
{
    DWORD SavedLValue = GPropertyLValue;
    P_GET_FLOAT_REF(A);
    GPropertyLValue = SavedLValue;
    P_GET_FLOAT(B);
    P_FINISH;
    *(FLOAT*)Result = (*A *= B);
}

// FUNCTION: 0x10AFF960 ?execDivideEqual_FloatFloat@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execDivideEqual_FloatFloat(FFrame& Stack, RESULT_DECL)
{
    DWORD SavedLValue = GPropertyLValue;
    P_GET_FLOAT_REF(A);
    GPropertyLValue = SavedLValue;
    P_GET_FLOAT(B);
    P_FINISH;
    *(FLOAT*)Result = (*A /= B);
}

// FUNCTION: 0x10AFF9F0 ?execAddEqual_FloatFloat@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execAddEqual_FloatFloat(FFrame& Stack, RESULT_DECL)
{
    DWORD SavedLValue = GPropertyLValue;
    P_GET_FLOAT_REF(A);
    GPropertyLValue = SavedLValue;
    P_GET_FLOAT(B);
    P_FINISH;
    *(FLOAT*)Result = (*A += B);
}

// FUNCTION: 0x10AFFA80 ?execSubtractEqual_FloatFloat@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execSubtractEqual_FloatFloat(FFrame& Stack, RESULT_DECL)
{
    DWORD SavedLValue = GPropertyLValue;
    P_GET_FLOAT_REF(A);
    GPropertyLValue = SavedLValue;
    P_GET_FLOAT(B);
    P_FINISH;
    *(FLOAT*)Result = (*A -= B);
}

// FUNCTION: 0x10AFFB10 ?execSin@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execSin(FFrame& Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_FINISH;
    *(FLOAT*)Result = appSin(A);
}

// FUNCTION: 0x10AFFB50 ?execCos@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execCos(FFrame& Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_FINISH;
    *(FLOAT*)Result = appCos(A);
}

// FUNCTION: 0x10AFFB90 ?execTan@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execTan(FFrame& Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_FINISH;
    *(FLOAT*)Result = appTan(A);
}

// FUNCTION: 0x10AFFBD0 ?execAtan@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execAtan(FFrame& Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_FINISH;
    *(FLOAT*)Result = appAtan(A);
}

// FUNCTION: 0x10AFFC10 ?execExp@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execExp(FFrame& Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_FINISH;
    *(FLOAT*)Result = appExp(A);
}

// FUNCTION: 0x10AFFC60 ?execLoge@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execLoge(FFrame& Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_FINISH;
    *(FLOAT*)Result = appLoge(A);
}

// FUNCTION: 0x10AFFCA0 ?execSqrt@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execSqrt(FFrame& Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_FINISH;
    *(FLOAT*)Result = appSqrt(A);
}

// FUNCTION: 0x10AFFCE0 ?execFRand@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execFRand(FFrame& Stack, RESULT_DECL)
{
    P_FINISH;
    *(FLOAT*)Result = appFrand();
}

// FUNCTION: 0x10AFFD00 ?execLerp@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execLerp(FFrame& Stack, RESULT_DECL)
{
    P_GET_FLOAT(V);
    P_GET_FLOAT(A);
    P_GET_FLOAT(B);
    P_FINISH;
    *(FLOAT*)Result = A + V * (B - A);
}

// FUNCTION: 0x10AFFD80 ?execSmerp@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execSmerp(FFrame& Stack, RESULT_DECL)
{
    P_GET_FLOAT(V);
    P_GET_FLOAT(A);
    P_GET_FLOAT(B);
    P_FINISH;
    *(FLOAT*)Result = A + (3.f * V * V - 2 * V * V * V) * (B - A);
}

// FUNCTION: 0x10AFFE10 ?execRotationConst@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execRotationConst(FFrame& Stack, RESULT_DECL)
{
    ((FRotator*)Result)->Pitch = Stack.ReadInt();
    ((FRotator*)Result)->Yaw = Stack.ReadInt();
    ((FRotator*)Result)->Roll = Stack.ReadInt();
}

// FUNCTION: 0x10AFFE40 ?execVectorConst@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execVectorConst(FFrame& Stack, RESULT_DECL)
{
    *(FVector*)Result = *(FVector*)Stack.Code;
    Stack.Code += sizeof(FVector);
}

// FUNCTION: 0x10B00010 ?execVectorToBool@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execVectorToBool(FFrame& Stack, RESULT_DECL)
{
    FVector V(0, 0, 0);
    Stack.Step(Stack.Object, &V);
    *(DWORD*)Result = !V.IsZero();
}

// FUNCTION: 0x10B00140 ?execVectorToRotator@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execVectorToRotator(FFrame& Stack, RESULT_DECL)
{
    FVector V(0, 0, 0);
    Stack.Step(Stack.Object, &V);
    *(FRotator*)Result = V.Rotation();
}

// FUNCTION: 0x10B001A0 ?execRotatorToBool@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execRotatorToBool(FFrame& Stack, RESULT_DECL)
{
    FRotator R(0, 0, 0);
    Stack.Step(Stack.Object, &R);
    *(DWORD*)Result = !R.IsZero();
}

// FUNCTION: 0x10B00220 ?execRotatorToVector@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execRotatorToVector(FFrame& Stack, RESULT_DECL)
{
    FRotator R(0, 0, 0);
    Stack.Step(Stack.Object, &R);
    *(FVector*)Result = (GUnitCoords / R).XAxis;
}

// FUNCTION: 0x10B00320 ?execSubtract_PreVector@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execSubtract_PreVector(FFrame& Stack, RESULT_DECL)
{
    P_GET_VECTOR(A);
    P_FINISH;
    *(FVector*)Result = -A;
}

// FUNCTION: 0x10B00380 ?execMultiply_VectorFloat@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execMultiply_VectorFloat(FFrame& Stack, RESULT_DECL)
{
    P_GET_VECTOR(A);
    P_GET_FLOAT(B);
    P_FINISH;
    *(FVector*)Result = A * B;
}

// FUNCTION: 0x10B00400 ?execMultiply_FloatVector@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execMultiply_FloatVector(FFrame& Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_GET_VECTOR(B);
    P_FINISH;
    *(FVector*)Result = A * B;
}

// FUNCTION: 0x10B00480 ?execMultiply_VectorVector@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execMultiply_VectorVector(FFrame& Stack, RESULT_DECL)
{
    P_GET_VECTOR(A);
    P_GET_VECTOR(B);
    P_FINISH;
    *(FVector*)Result = A * B;
}

// FUNCTION: 0x10B00500 ?execDivide_VectorFloat@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execDivide_VectorFloat(FFrame& Stack, RESULT_DECL)
{
    P_GET_VECTOR(A);
    P_GET_FLOAT(B);
    P_FINISH;
    *(FVector*)Result = A / B;
}

// FUNCTION: 0x10B00580 ?execAdd_VectorVector@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execAdd_VectorVector(FFrame& Stack, RESULT_DECL)
{
    P_GET_VECTOR(A);
    P_GET_VECTOR(B);
    P_FINISH;
    *(FVector*)Result = A + B;
}

// FUNCTION: 0x10B00600 ?execSubtract_VectorVector@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execSubtract_VectorVector(FFrame& Stack, RESULT_DECL)
{
    P_GET_VECTOR(A);
    P_GET_VECTOR(B);
    P_FINISH;
    *(FVector*)Result = A - B;
}

// FUNCTION: 0x10B00680 ?execLessLess_VectorRotator@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execLessLess_VectorRotator(FFrame& Stack, RESULT_DECL)
{
    P_GET_VECTOR(A);
    P_GET_ROTATOR(B);
    P_FINISH;
    *(FVector*)Result = TransformVectorBy(A, GUnitCoords / B);
}

// FUNCTION: 0x10B00720 ?execGreaterGreater_VectorRotator@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execGreaterGreater_VectorRotator(FFrame& Stack, RESULT_DECL)
{
    P_GET_VECTOR(A);
    P_GET_ROTATOR(B);
    P_FINISH;
    *(FVector*)Result = TransformVectorBy(A, GUnitCoords * B);
}

// FUNCTION: 0x10B007C0 ?execEqualEqual_VectorVector@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execEqualEqual_VectorVector(FFrame& Stack, RESULT_DECL)
{
    P_GET_VECTOR(A);
    P_GET_VECTOR(B);
    P_FINISH;
    *(DWORD*)Result = A == B;
}

// FUNCTION: 0x10B00850 ?execNotEqual_VectorVector@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execNotEqual_VectorVector(FFrame& Stack, RESULT_DECL)
{
    P_GET_VECTOR(A);
    P_GET_VECTOR(B);
    P_FINISH;
    *(DWORD*)Result = A != B;
}

// FUNCTION: 0x10B008E0 ?execDot_VectorVector@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execDot_VectorVector(FFrame& Stack, RESULT_DECL)
{
    P_GET_VECTOR(A);
    P_GET_VECTOR(B);
    P_FINISH;
    *(FLOAT*)Result = A | B;
}

// FUNCTION: 0x10B00940 ?execCross_VectorVector@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execCross_VectorVector(FFrame& Stack, RESULT_DECL)
{
    P_GET_VECTOR(A);
    P_GET_VECTOR(B);
    P_FINISH;
    *(FVector*)Result = A ^ B;
}

// FUNCTION: 0x10B009D0 ?execMultiplyEqual_VectorFloat@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execMultiplyEqual_VectorFloat(FFrame& Stack, RESULT_DECL)
{
    DWORD SavedLValue = GPropertyLValue;
    P_GET_VECTOR_REF(A);
    GPropertyLValue = SavedLValue;
    P_GET_FLOAT(B);
    P_FINISH;
    *(FVector*)Result = (*A *= B);
}

// FUNCTION: 0x10B00A70 ?execMultiplyEqual_VectorVector@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execMultiplyEqual_VectorVector(FFrame& Stack, RESULT_DECL)
{
    DWORD SavedLValue = GPropertyLValue;
    P_GET_VECTOR_REF(A);
    GPropertyLValue = SavedLValue;
    P_GET_VECTOR(B);
    P_FINISH;
    *(FVector*)Result = (*A *= B);
}

// FUNCTION: 0x10B00B10 ?execDivideEqual_VectorFloat@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execDivideEqual_VectorFloat(FFrame& Stack, RESULT_DECL)
{
    DWORD SavedLValue = GPropertyLValue;
    P_GET_VECTOR_REF(A);
    GPropertyLValue = SavedLValue;
    P_GET_FLOAT(B);
    P_FINISH;
    *(FVector*)Result = (*A /= B);
}

// FUNCTION: 0x10B00BC0 ?execAddEqual_VectorVector@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execAddEqual_VectorVector(FFrame& Stack, RESULT_DECL)
{
    DWORD SavedLValue = GPropertyLValue;
    P_GET_VECTOR_REF(A);
    GPropertyLValue = SavedLValue;
    P_GET_VECTOR(B);
    P_FINISH;
    *(FVector*)Result = (*A += B);
}

// FUNCTION: 0x10B00C60 ?execSubtractEqual_VectorVector@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execSubtractEqual_VectorVector(FFrame& Stack, RESULT_DECL)
{
    DWORD SavedLValue = GPropertyLValue;
    P_GET_VECTOR_REF(A);
    GPropertyLValue = SavedLValue;
    P_GET_VECTOR(B);
    P_FINISH;
    *(FVector*)Result = (*A -= B);
}

// FUNCTION: 0x10B00D00 ?execVSize@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execVSize(FFrame& Stack, RESULT_DECL)
{
    P_GET_VECTOR(A);
    P_FINISH;
    *(FLOAT*)Result = appSqrt(A.X * A.X + A.Y * A.Y + A.Z * A.Z);
}

// FUNCTION: 0x10B00D50 ?execNormal@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execNormal(FFrame& Stack, RESULT_DECL)
{
    P_GET_VECTOR(A);
    P_FINISH;
    *(FVector*)Result = A.SafeNormal();
}

// FUNCTION: 0x10B00F30 ?execVRand@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execVRand(FFrame& Stack, RESULT_DECL)
{
    P_FINISH;
    *(FVector*)Result = appVRand();
}

// FUNCTION: 0x10B00F70 ?execRotRand@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execRotRand(FFrame& Stack, RESULT_DECL)
{
    DWORD bRoll = 0;
    Stack.Step(Stack.Object, &bRoll);
    P_FINISH;
    FRotator RRot;
    RRot.Yaw = ((2 * appRand()) % 65535);
    RRot.Pitch = ((2 * appRand()) % 65535);
    if (bRoll)
        RRot.Roll = ((2 * appRand()) % 65535);
    else
        RRot.Roll = 0;
    *(FRotator*)Result = RRot;
}

// FUNCTION: 0x10B01000 ?execMirrorVectorByNormal@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execMirrorVectorByNormal(FFrame& Stack, RESULT_DECL)
{
    P_GET_VECTOR(A);
    P_GET_VECTOR(B);
    P_FINISH;
    B = B.SafeNormal();
    *(FVector*)Result = A - 2.f * B * (B | A);
}

// FUNCTION: 0x10B010E0 ?execEqualEqual_RotatorRotator@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execEqualEqual_RotatorRotator(FFrame& Stack, RESULT_DECL)
{
    P_GET_ROTATOR(A);
    P_GET_ROTATOR(B);
    P_FINISH;
    *(DWORD*)Result = A == B;
}

// FUNCTION: 0x10B01150 ?execNotEqual_RotatorRotator@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execNotEqual_RotatorRotator(FFrame& Stack, RESULT_DECL)
{
    P_GET_ROTATOR(A);
    P_GET_ROTATOR(B);
    P_FINISH;
    *(DWORD*)Result = A != B;
}

// FUNCTION: 0x10B011C0 ?execMultiply_RotatorFloat@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execMultiply_RotatorFloat(FFrame& Stack, RESULT_DECL)
{
    P_GET_ROTATOR(A);
    P_GET_FLOAT(B);
    P_FINISH;
    *(FRotator*)Result = A * B;
}

// FUNCTION: 0x10B01240 ?execMultiply_FloatRotator@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execMultiply_FloatRotator(FFrame& Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_GET_ROTATOR(B);
    P_FINISH;
    *(FRotator*)Result = A * B;
}

// FUNCTION: 0x10B012C0 ?execDivide_RotatorFloat@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execDivide_RotatorFloat(FFrame& Stack, RESULT_DECL)
{
    P_GET_ROTATOR(A);
    P_GET_FLOAT(B);
    P_FINISH;
    *(FRotator*)Result = A * (1.f / B);
}

// FUNCTION: 0x10B01340 ?execMultiplyEqual_RotatorFloat@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execMultiplyEqual_RotatorFloat(FFrame& Stack, RESULT_DECL)
{
    DWORD SavedLValue = GPropertyLValue;
    P_GET_ROTATOR_REF(A);
    GPropertyLValue = SavedLValue;
    P_GET_FLOAT(B);
    P_FINISH;
    *(FRotator*)Result = (*A *= B);
}

// FUNCTION: 0x10B01400 ?execDivideEqual_RotatorFloat@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execDivideEqual_RotatorFloat(FFrame& Stack, RESULT_DECL)
{
    DWORD SavedLValue = GPropertyLValue;
    P_GET_ROTATOR_REF(A);
    GPropertyLValue = SavedLValue;
    P_GET_FLOAT(B);
    P_FINISH;
    *(FRotator*)Result = (*A *= (1.f / B));
}

// FUNCTION: 0x10B014C0 ?execAdd_RotatorRotator@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execAdd_RotatorRotator(FFrame& Stack, RESULT_DECL)
{
    P_GET_ROTATOR(A);
    P_GET_ROTATOR(B);
    P_FINISH;
    *(FRotator*)Result = A + B;
}

// FUNCTION: 0x10B01530 ?execSubtract_RotatorRotator@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execSubtract_RotatorRotator(FFrame& Stack, RESULT_DECL)
{
    P_GET_ROTATOR(A);
    P_GET_ROTATOR(B);
    P_FINISH;
    *(FRotator*)Result = A - B;
}

// FUNCTION: 0x10B01590 ?execAddEqual_RotatorRotator@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execAddEqual_RotatorRotator(FFrame& Stack, RESULT_DECL)
{
    DWORD SavedLValue = GPropertyLValue;
    P_GET_ROTATOR_REF(A);
    GPropertyLValue = SavedLValue;
    P_GET_ROTATOR(B);
    P_FINISH;
    *(FRotator*)Result = (*A += B);
}

// FUNCTION: 0x10B01630 ?execSubtractEqual_RotatorRotator@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execSubtractEqual_RotatorRotator(FFrame& Stack, RESULT_DECL)
{
    DWORD SavedLValue = GPropertyLValue;
    P_GET_ROTATOR_REF(A);
    GPropertyLValue = SavedLValue;
    P_GET_ROTATOR(B);
    P_FINISH;
    *(FRotator*)Result = (*A -= B);
}

// FUNCTION: 0x10B016D0 ?execGetAxes@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execGetAxes(FFrame& Stack, RESULT_DECL)
{
    P_GET_ROTATOR(A);
    DWORD SavedLValue = GPropertyLValue;
    P_GET_VECTOR_REF(X);
    P_GET_VECTOR_REF(Y);
    P_GET_VECTOR_REF(Z);
    GPropertyLValue = SavedLValue;
    P_FINISH;
    FCoords Coords = GUnitCoords / A;
    *X = Coords.XAxis;
    *Y = Coords.YAxis;
    *Z = Coords.ZAxis;
}

// FUNCTION: 0x10B01810 ?execGetUnAxes@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execGetUnAxes(FFrame& Stack, RESULT_DECL)
{
    P_GET_ROTATOR(A);
    DWORD SavedLValue = GPropertyLValue;
    P_GET_VECTOR_REF(X);
    P_GET_VECTOR_REF(Y);
    P_GET_VECTOR_REF(Z);
    GPropertyLValue = SavedLValue;
    P_FINISH;
    FCoords Coords = GUnitCoords * A;
    *X = Coords.XAxis;
    *Y = Coords.YAxis;
    *Z = Coords.ZAxis;
}

// FUNCTION: 0x10B01950 ?execOrthoRotation@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execOrthoRotation(FFrame& Stack, RESULT_DECL)
{
    P_GET_VECTOR(X);
    P_GET_VECTOR(Y);
    P_GET_VECTOR(Z);
    P_FINISH;
    FCoords Coords = FCoords(FVector(0, 0, 0), X, Y, Z);
    *(FRotator*)Result = Coords.OrthoRotation();
}

// FUNCTION: 0x10B01A30 ?execNormalize@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execNormalize(FFrame& Stack, RESULT_DECL)
{
    P_GET_ROTATOR(Rot);
    P_FINISH;
    Rot.Pitch = Rot.Pitch & 0xFFFF;
    if (Rot.Pitch > 32767)
        Rot.Pitch -= 0x10000;
    Rot.Roll = Rot.Roll & 0xFFFF;
    if (Rot.Roll > 32767)
        Rot.Roll -= 0x10000;
    Rot.Yaw = Rot.Yaw & 0xFFFF;
    if (Rot.Yaw > 32767)
        Rot.Yaw -= 0x10000;
    *(FRotator*)Result = Rot;
}

// FUNCTION: 0x10B01AB0 ?execEatString@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execEatString(FFrame& Stack, RESULT_DECL)
{
    // Calls a function returning a string, and discards the result.
    FString String;
    Stack.Step(this, &String);
}

// FUNCTION: 0x10B02200 ?execLen@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execLen(FFrame& Stack, RESULT_DECL)
{
    P_GET_STR(S);
    P_FINISH;
    *(INT*)Result = S.Len();
}

// FUNCTION: 0x10B02600 ?execChr@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execChr(FFrame& Stack, RESULT_DECL)
{
    P_GET_INT(i);
    P_FINISH;
    ANSICHAR Temp[2];
    Temp[0] = i;
    Temp[1] = 0;
    *(FString*)Result = Temp;
}

// FUNCTION: 0x10B02650 ?execAsc@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execAsc(FFrame& Stack, RESULT_DECL)
{
    P_GET_STR(S);
    P_FINISH;
    *(INT*)Result = **S;
}

// FUNCTION: 0x10B028B0 ?execHighNative0@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execHighNative0(FFrame& Stack, RESULT_DECL)
{
    BYTE B = *Stack.Code++;
    (this->*GNatives[0 * 256 + B])(Stack, Result);
}

// FUNCTION: 0x10B028E0 ?execHighNative1@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execHighNative1(FFrame& Stack, RESULT_DECL)
{
    BYTE B = *Stack.Code++;
    (this->*GNatives[1 * 256 + B])(Stack, Result);
}

// FUNCTION: 0x10B02910 ?execHighNative2@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execHighNative2(FFrame& Stack, RESULT_DECL)
{
    BYTE B = *Stack.Code++;
    (this->*GNatives[2 * 256 + B])(Stack, Result);
}

// FUNCTION: 0x10B02940 ?execHighNative3@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execHighNative3(FFrame& Stack, RESULT_DECL)
{
    BYTE B = *Stack.Code++;
    (this->*GNatives[3 * 256 + B])(Stack, Result);
}

// FUNCTION: 0x10B02970 ?execHighNative4@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execHighNative4(FFrame& Stack, RESULT_DECL)
{
    BYTE B = *Stack.Code++;
    (this->*GNatives[4 * 256 + B])(Stack, Result);
}

// FUNCTION: 0x10B029A0 ?execHighNative5@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execHighNative5(FFrame& Stack, RESULT_DECL)
{
    BYTE B = *Stack.Code++;
    (this->*GNatives[5 * 256 + B])(Stack, Result);
}

// FUNCTION: 0x10B029D0 ?execHighNative6@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execHighNative6(FFrame& Stack, RESULT_DECL)
{
    BYTE B = *Stack.Code++;
    (this->*GNatives[6 * 256 + B])(Stack, Result);
}

// FUNCTION: 0x10B02A00 ?execHighNative7@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execHighNative7(FFrame& Stack, RESULT_DECL)
{
    BYTE B = *Stack.Code++;
    (this->*GNatives[7 * 256 + B])(Stack, Result);
}

// FUNCTION: 0x10B02A30 ?execHighNative8@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execHighNative8(FFrame& Stack, RESULT_DECL)
{
    BYTE B = *Stack.Code++;
    (this->*GNatives[8 * 256 + B])(Stack, Result);
}

// FUNCTION: 0x10B02A60 ?execHighNative9@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execHighNative9(FFrame& Stack, RESULT_DECL)
{
    BYTE B = *Stack.Code++;
    (this->*GNatives[9 * 256 + B])(Stack, Result);
}

// FUNCTION: 0x10B02A90 ?execHighNative10@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execHighNative10(FFrame& Stack, RESULT_DECL)
{
    BYTE B = *Stack.Code++;
    (this->*GNatives[10 * 256 + B])(Stack, Result);
}

// FUNCTION: 0x10B02AC0 ?execHighNative11@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execHighNative11(FFrame& Stack, RESULT_DECL)
{
    BYTE B = *Stack.Code++;
    (this->*GNatives[11 * 256 + B])(Stack, Result);
}

// FUNCTION: 0x10B02AF0 ?execHighNative12@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execHighNative12(FFrame& Stack, RESULT_DECL)
{
    BYTE B = *Stack.Code++;
    (this->*GNatives[12 * 256 + B])(Stack, Result);
}

// FUNCTION: 0x10B02B20 ?execHighNative13@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execHighNative13(FFrame& Stack, RESULT_DECL)
{
    BYTE B = *Stack.Code++;
    (this->*GNatives[13 * 256 + B])(Stack, Result);
}

// FUNCTION: 0x10B02B50 ?execHighNative14@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execHighNative14(FFrame& Stack, RESULT_DECL)
{
    BYTE B = *Stack.Code++;
    (this->*GNatives[14 * 256 + B])(Stack, Result);
}

// FUNCTION: 0x10B02B80 ?execHighNative15@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execHighNative15(FFrame& Stack, RESULT_DECL)
{
    BYTE B = *Stack.Code++;
    (this->*GNatives[15 * 256 + B])(Stack, Result);
}

// FUNCTION: 0x10B02C90 ?execSaveConfig@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execSaveConfig(FFrame& Stack, RESULT_DECL)
{
    P_FINISH;
    SaveConfig(0, NULL);
}

// FUNCTION: 0x10B02CB0 ?execResetConfig@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execResetConfig(FFrame& Stack, RESULT_DECL)
{
    P_FINISH;
    ResetConfig(GetClass());
}

// FUNCTION: 0x10B02DA0 ?execIsInState@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execIsInState(FFrame& Stack, RESULT_DECL)
{
    P_GET_NAME(StateName);
    P_FINISH;
    if (StateFrame)
        for (UState* Test = StateFrame->StateNode; Test; Test = (UState*)Test->SuperField)
            if (Test->GetFName() == StateName)
            {
                *(DWORD*)Result = 1;
                return;
            }
    *(DWORD*)Result = 0;
}

// FUNCTION: 0x10B02E00 ?execGetStateName@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execGetStateName(FFrame& Stack, RESULT_DECL)
{
    P_FINISH;
    *(FName*)Result = (StateFrame && StateFrame->StateNode) ? StateFrame->StateNode->GetFName() : FName(NAME_None);
}

// FUNCTION: 0x10B02E50 ?execIsA@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execIsA(FFrame& Stack, RESULT_DECL)
{
    P_GET_NAME(ClassName);
    P_FINISH;
    UClass* TempClass;
    for (TempClass = GetClass(); TempClass; TempClass = (UClass*)TempClass->SuperField)
        if (TempClass->GetFName() == ClassName)
            break;
    *(DWORD*)Result = TempClass != NULL;
}

// FUNCTION: 0x10B034A0 ?execDynArrayElement@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execDynArrayElement(FFrame& Stack, RESULT_DECL)
{
    // The index is read, never written, whatever the element is used for.
    DWORD SavedLValue = GPropertyLValue;
    GPropertyLValue = 0;
    P_GET_INT(Index);
    GPropertyLValue = SavedLValue;

    GProperty = NULL;
    Stack.Step(this, NULL);
    if (GProperty && GPropAddr)
    {
        UArrayProperty* ArrayProp = (UArrayProperty*)GProperty;
        FArray* Array = (FArray*)GPropAddr;
        if (Index >= Array->Num() || Index < 0)
        {
            // Reading clamps the index; writing grows the array.
            if (!GPropertyLValue)
            {
                Stack.Logf("Accessed array out of bounds (%i/%i)", Index, ArrayProp->ArrayDim);
                Index = Clamp(Index, 0, Array->Num() - 1);
            }
            else
                Array->AddZeroed(ArrayProp->Inner->ElementSize, Index - Array->Num() + 1);
        }
        GPropAddr = Array->Data ? (BYTE*)Array->Data + Index * ((UArrayProperty*)GProperty)->Inner->ElementSize : NULL;
    }
    if (Result)
    {
        if (!GPropAddr)
        {
            // Out of range with no array: the element type's default value.
            BYTE* Value = ((UArrayProperty*)GProperty)->Inner->CreateDefaultValue();
            ((UArrayProperty*)GProperty)->Inner->CopySingleValue(Result, Value, NULL);
            ((UArrayProperty*)GProperty)->Inner->DestroyDefaultValue(Value);
        }
        else
            ((UArrayProperty*)GProperty)->Inner->CopySingleValue(Result, GPropAddr, NULL);
    }
}

// FUNCTION: 0x10B03600 ?execDynArrayInsert@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execDynArrayInsert(FFrame& Stack, RESULT_DECL)
{
    GProperty = NULL;
    GPropertyLValue = 1;
    Stack.Step(this, NULL);
    GPropertyLValue = 0;
    P_GET_INT(Offset);
    P_GET_INT(Count);
    FArray* Array = (FArray*)GPropAddr;
    if (Array && Count)
    {
        if (Count < 0)
        {
            Stack.Logf("Attempt to insert a negative number of elements");
            return;
        }
        if (Offset < 0 || Offset > Array->Num())
        {
            Stack.Logf("Attempt to insert %i elements at %i an %i-element array", Count, Offset, Array->Num());
            Offset = Clamp(Offset, 0, Array->Num());
        }
        Array->Insert(Offset, Count, ((UArrayProperty*)GProperty)->Inner->ElementSize);
    }
}

// FUNCTION: 0x10B036F0 ?execDynArrayRemove@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execDynArrayRemove(FFrame& Stack, RESULT_DECL)
{
    GProperty = NULL;
    GPropertyLValue = 1;
    Stack.Step(this, NULL);
    GPropertyLValue = 0;
    P_GET_INT(Offset);
    P_GET_INT(Count);
    FArray* Array = (FArray*)GPropAddr;
    if (Array && Count)
    {
        if (Count < 0)
        {
            Stack.Logf("Attempt to remove a negative number of elements");
            return;
        }
        if (Offset < 0 || Offset >= Array->Num() || Offset + Count > Array->Num())
        {
            if (Count == 1)
                Stack.Logf("Attempt to remove element %i in an %i-element array", Offset, Array->Num());
            else
                Stack.Logf("Attempt to remove elements %i through %i in an %i-element array",
                           Offset, Offset + Count - 1, Array->Num());
            Offset = Clamp(Offset, 0, Array->Num());
            if (Offset + Count > Array->Num())
                Count = Array->Num() - Offset;
        }
        for (INT i = Offset; i < Offset + Count; i++)
            ((UArrayProperty*)GProperty)->Inner->DestroyValue(
                (BYTE*)Array->Data + ((UArrayProperty*)GProperty)->Inner->ElementSize * i);
        Array->Remove(Offset, Count, ((UArrayProperty*)GProperty)->Inner->ElementSize);
    }
}

// FUNCTION: 0x10B03A60 ?execJump@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execJump(FFrame& Stack, RESULT_DECL)
{
    CHECK_RUNAWAY;
    // Jump immediate.
    INT Offset = Stack.ReadWord();
    Stack.Code = (BYTE*)Stack.Node->Script.Data + Offset;
}

// FUNCTION: 0x10B03AD0 ?execJumpIfNot@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execJumpIfNot(FFrame& Stack, RESULT_DECL)
{
    CHECK_RUNAWAY;
    // Get code offset.
    INT wOffset = Stack.ReadWord();

    // Get boolean test value.
    P_GET_UBOOL(Value);

    // Jump if false.
    if (!Value)
        Stack.Code = (BYTE*)Stack.Node->Script.Data + wOffset;
}

// FUNCTION: 0x10B03D60 ?execMetaCast@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execMetaCast(FFrame& Stack, RESULT_DECL)
{
    UClass* MetaClass = (UClass*)Stack.ReadObject();

    // Compile actual expression.
    P_GET_OBJECT(UObject, Castee);
    *(UObject**)Result = (Castee && Castee->IsA(UClass::StaticClass()) && ((UClass*)Castee)->IsChildOf(MetaClass)) ? Castee : NULL;
}

// FUNCTION: 0x10B03E90 ?execMin@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execMin(FFrame& Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(INT*)Result = Min(A, B);
}

// FUNCTION: 0x10B03EF0 ?execMax@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execMax(FFrame& Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(INT*)Result = Max(A, B);
}

// FUNCTION: 0x10B03F50 ?execClamp@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execClamp(FFrame& Stack, RESULT_DECL)
{
    P_GET_INT(V);
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(INT*)Result = Clamp(V, A, B);
}

// FUNCTION: 0x10B04010 ?execComplementEqual_FloatFloat@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execComplementEqual_FloatFloat(FFrame& Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_GET_FLOAT(B);
    P_FINISH;
    *(DWORD*)Result = Abs(A - B) < (1.e-4);
}

// FUNCTION: 0x10B04090 ?execAbs@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execAbs(FFrame& Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_FINISH;
    *(FLOAT*)Result = Abs(A);
}

// FUNCTION: 0x10B040F0 ?execSquare@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execSquare(FFrame& Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_FINISH;
    *(FLOAT*)Result = A * A;
}

// FUNCTION: 0x10B04130 ?execFMin@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execFMin(FFrame& Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_GET_FLOAT(B);
    P_FINISH;
    *(FLOAT*)Result = Min(A, B);
}

// FUNCTION: 0x10B041A0 ?execFMax@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execFMax(FFrame& Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_GET_FLOAT(B);
    P_FINISH;
    *(FLOAT*)Result = Max(A, B);
}

// FUNCTION: 0x10B04210 ?execFClamp@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execFClamp(FFrame& Stack, RESULT_DECL)
{
    P_GET_FLOAT(V);
    P_GET_FLOAT(A);
    P_GET_FLOAT(B);
    P_FINISH;
    *(FLOAT*)Result = Clamp(V, A, B);
}

// FUNCTION: 0x10B043C0 ?execClassIsChildOf@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execClassIsChildOf(FFrame& Stack, RESULT_DECL)
{
    P_GET_OBJECT(UClass, K);
    P_GET_OBJECT(UClass, C);
    P_FINISH;
    *(DWORD*)Result = (C && K) ? K->IsChildOf(C) : 0;
}

// FUNCTION: 0x10B04810 ?execStaticSaveConfig@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execStaticSaveConfig(FFrame& Stack, RESULT_DECL)
{
    P_FINISH;
    GetClass()->ClassDefaultObject->SaveConfig(0, NULL);
}

// FUNCTION: 0x10B04840 ?execGetEnum@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execGetEnum(FFrame& Stack, RESULT_DECL)
{
    P_GET_OBJECT(UObject, E);
    P_GET_INT(i);
    P_FINISH;

    *(FName*)Result = NAME_None;
    if (Cast<UEnum>(E) && i >= 0 && i < Cast<UEnum>(E)->Names.Num())
        *(FName*)Result = Cast<UEnum>(E)->Names(i);
}

// FUNCTION: 0x10B04FF0 ?execObjectToString@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execObjectToString(FFrame& Stack, RESULT_DECL)
{
    P_GET_OBJECT(UObject, Obj);
    *(FString*)Result = *(Obj ? Obj->GetPathName() : String("None"));
}
