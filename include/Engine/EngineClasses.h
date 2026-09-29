// Engine classes known so far only by name and package, from the class objects
// Ion Storm builds on first use (DECLARE_STATIC_CLASS). Layouts are not
// declared yet; where stock Unreal Engine 2 has intermediate classes between a
// class and the one it derives from here, the comment names them.
#pragma once

#include "Core/Core.h"

class AActor : public UObject
{
    DECLARE_STATIC_CLASS(AActor, "Engine")
};

class APawn : public AActor
{
    DECLARE_STATIC_CLASS(APawn, "Engine")
};

// Thief's player pawn (not in stock Unreal Engine 2).
class APlayerPawn : public APawn
{
    DECLARE_STATIC_CLASS(APlayerPawn, "Engine")
};

class APlayerController : public AActor   // via AController
{
    DECLARE_STATIC_CLASS(APlayerController, "Engine")
};

class AVolume : public AActor             // via ABrush
{
    DECLARE_STATIC_CLASS(AVolume, "Engine")
};

class ASkyZoneInfo : public AActor        // via AInfo, AZoneInfo
{
    DECLARE_STATIC_CLASS(ASkyZoneInfo, "Engine")
};

class AEmitter : public AActor
{
    DECLARE_STATIC_CLASS(AEmitter, "Engine")
};

class ULevel : public UObject             // via ULevelBase
{
    DECLARE_STATIC_CLASS(ULevel, "Engine")
};

class UTexture : public UObject           // via UMaterial, URenderedMaterial, UBitmapMaterial
{
    DECLARE_STATIC_CLASS(UTexture, "Engine")
};

class USkeletalMesh : public UObject      // via UPrimitive, UMesh, ULodMesh
{
    DECLARE_STATIC_CLASS(USkeletalMesh, "Engine")
};

class USkeletalMeshInstance : public UObject  // via UMeshInstance, ULodMeshInstance
{
    DECLARE_STATIC_CLASS(USkeletalMeshInstance, "Engine")
};

class UParticleEmitter : public UObject
{
    DECLARE_STATIC_CLASS(UParticleEmitter, "Engine")
};

class USpriteEmitter : public UParticleEmitter
{
    DECLARE_STATIC_CLASS(USpriteEmitter, "Engine")
};
