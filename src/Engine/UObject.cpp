// Engine/UObject.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"
                     // 0x10F46DE8

// An out parameter: its address when it is a variable, else a temporary. The
// caller saves GPropertyLValue before the first and restores it after the last.
#define P_GET_VECTOR_REF(var) FVector var##T; GPropAddr = NULL; GPropertyLValue = 1; Stack.Step(Stack.Object, &var##T);                               FVector* var = GPropAddr ? (FVector*)GPropAddr : &var##T;

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
    virtual void Unknown48();
    virtual void Unknown4C();
    virtual void Unknown50();
    virtual void Unknown54();
    virtual void Unknown58();
    virtual void Unknown5C();
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
    BYTE Unknown3C[0x24];
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

    FCoords& operator*=(const FRotator& Rot);   // 0x109620B0
    FCoords operator*(const FRotator& Rot) const { return FCoords(*this) *= Rot; }
    FCoords& operator/=(const FRotator& Rot);   // 0x10961AF0
    FCoords operator/(const FRotator& Rot) const { return FCoords(*this) /= Rot; }
};

// The unit coordinate system (GMath.UnitCoords in stock Unreal Engine 2).
extern FCoords GUnitCoords;

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

// FUNCTION: 0x10AFD810 ?execSelf@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execSelf(FFrame& Stack, RESULT_DECL)
{
    *(UObject**)Result = this;
}

// FUNCTION: 0x10AFD900 ?execFinalFunction@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execFinalFunction(FFrame& Stack, RESULT_DECL)
{
    CallFunction(Stack, Result, (UFunction*)Stack.ReadObject());
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

// FUNCTION: 0x10AFE360 ?execNot_PreBool@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execNot_PreBool(FFrame& Stack, RESULT_DECL)
{
    P_GET_UBOOL(A);
    P_FINISH;
    *(DWORD*)Result = !A;
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

// FUNCTION: 0x10AFF3F0 ?execSubtract_PreFloat@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execSubtract_PreFloat(FFrame& Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_FINISH;
    *(FLOAT*)Result = -A;
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

// FUNCTION: 0x10AFFCE0 ?execFRand@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execFRand(FFrame& Stack, RESULT_DECL)
{
    P_FINISH;
    *(FLOAT*)Result = appFrand();
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

// FUNCTION: 0x10B00580 ?execAdd_VectorVector@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execAdd_VectorVector(FFrame& Stack, RESULT_DECL)
{
    P_GET_VECTOR(A);
    P_GET_VECTOR(B);
    P_FINISH;
    *(FVector*)Result = A + B;
}

// FUNCTION: 0x10B00F30 ?execVRand@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execVRand(FFrame& Stack, RESULT_DECL)
{
    P_FINISH;
    *(FVector*)Result = appVRand();
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

// FUNCTION: 0x10B014C0 ?execAdd_RotatorRotator@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execAdd_RotatorRotator(FFrame& Stack, RESULT_DECL)
{
    P_GET_ROTATOR(A);
    P_GET_ROTATOR(B);
    P_FINISH;
    *(FRotator*)Result = A + B;
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

// FUNCTION: 0x10B02200 ?execLen@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execLen(FFrame& Stack, RESULT_DECL)
{
    P_GET_STR(S);
    P_FINISH;
    *(INT*)Result = S.Len();
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

// FUNCTION: 0x10B040F0 ?execSquare@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execSquare(FFrame& Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_FINISH;
    *(FLOAT*)Result = A * A;
}

// FUNCTION: 0x10B04810 ?execStaticSaveConfig@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execStaticSaveConfig(FFrame& Stack, RESULT_DECL)
{
    P_FINISH;
    GetClass()->ClassDefaultObject->SaveConfig(0, NULL);
}

// FUNCTION: 0x10B04FF0 ?execObjectToString@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execObjectToString(FFrame& Stack, RESULT_DECL)
{
    P_GET_OBJECT(UObject, Obj);
    *(FString*)Result = *(Obj ? Obj->GetPathName() : String("None"));
}
