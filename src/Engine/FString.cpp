// Engine/FString.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

typedef int INT;

typedef char ANSICHAR;

// A dynamic array's header. Ion Storm's arrays take a debug name, which this
// constructor (0x10AF4B90) ignores: it only clears the header.
class FArray
{
public:
    FArray(INT ElementSize, const ANSICHAR* Name);

    void* Data;
    INT ArrayNum;
    INT ArrayMax;
};

class FString : public FArray
{
public:
    FString();
};

// FUNCTION: 0x10AF8230 ??0FString@@QAE@XZ
FString::FString()
    : FArray(sizeof(FString), "FString")
{
}
