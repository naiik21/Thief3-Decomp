// Classes known so far by name, package, superclass and within class: from
// the class objects Ion Storm builds on first use (DECLARE_STATIC_CLASS) and
// the initializer each links them with (IMPLEMENT_STATIC_CLASS). Actors
// (classes under Actor) take the A prefix, the others U. Layouts are not
// declared yet. Generated from the executable's class objects; edit by hand
// once a class gains fields.
#pragma once

#include "Core/Core.h"

class UCommandlet : public UObject
{
    DECLARE_STATIC_CLASS(UCommandlet, UObject, UObject, "Core")
};

class UExporter : public UObject
{
    DECLARE_ABSTRACT_STATIC_CLASS(UExporter, UObject, UObject, "Core")

    void StaticConstructor();
};

class UFactory : public UObject
{
    DECLARE_ABSTRACT_STATIC_CLASS(UFactory, UObject, UObject, "Core")

    void StaticConstructor();
};

class ULanguage : public UObject
{
    DECLARE_ABSTRACT_STATIC_CLASS(ULanguage, UObject, UObject, "Core")
};

class ULinkDataObject : public UObject
{
    DECLARE_ABSTRACT_STATIC_CLASS(ULinkDataObject, UObject, UObject, "Core")
};

class ULinker : public UObject
{
    DECLARE_STATIC_CLASS(ULinker, UObject, UObject, "Core")
};

class USubsystem : public UObject
{
    DECLARE_ABSTRACT_STATIC_CLASS(USubsystem, UObject, UObject, "Core")
};

class UTextBuffer : public UObject
{
    DECLARE_STATIC_CLASS(UTextBuffer, UObject, UObject, "Core")
};

class UConst : public UField
{
    DECLARE_STATIC_CLASS(UConst, UField, UStruct, "Core")
};

class ULinkerLoad : public ULinker
{
    DECLARE_STATIC_CLASS(ULinkerLoad, ULinker, UObject, "Core")
};

class ULinkerSave : public ULinker
{
    DECLARE_STATIC_CLASS(ULinkerSave, ULinker, UObject, "Core")
};

class USystem : public USubsystem
{
    DECLARE_STATIC_CLASS(USystem, USubsystem, UObject, "Core")

    void StaticConstructor();
};

class UBitfieldEnum : public UEnum
{
    DECLARE_STATIC_CLASS(UBitfieldEnum, UEnum, UStruct, "Core")
};
