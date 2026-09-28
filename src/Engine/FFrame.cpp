// Engine/FFrame.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

// FUNCTION: 0x10B0FCD0 ?ReadName@FFrame@@QAE?AVFName@@XZ
FName FFrame::ReadName()
{
    FName N = *(FName*)Code;
    Code += sizeof(FName);
    return N;
}
