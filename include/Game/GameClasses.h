// Classes known so far by name, package, superclass and within class: from
// the class objects Ion Storm builds on first use (DECLARE_STATIC_CLASS) and
// the initializer each links them with (IMPLEMENT_STATIC_CLASS). Actors
// (classes under Actor) take the A prefix, the others U. Layouts are not
// declared yet. Generated from the executable's class objects; edit by hand
// once a class gains fields.
#pragma once

#include "Engine/EngineClasses.h"

class AEnumEvidenceType : public AActor
{
    DECLARE_STATIC_CLASS(AEnumEvidenceType, AActor, UObject, "AICore")
};

class AEnumInferenceType : public AActor
{
    DECLARE_STATIC_CLASS(AEnumInferenceType, AActor, UObject, "AICore")
};

class AEnumStateType : public AActor
{
    DECLARE_STATIC_CLASS(AEnumStateType, AActor, UObject, "AICore")
};

class UInventorySwitchLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(UInventorySwitchLinkDataObject, ULinkDataObject, UObject, "T3Game")
};

class ULockLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(ULockLinkDataObject, ULinkDataObject, UObject, "T3Game")
};

class ULockTickLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(ULockTickLinkDataObject, ULinkDataObject, UObject, "T3Game")
};

class URopeArrowSpawnLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(URopeArrowSpawnLinkDataObject, ULinkDataObject, UObject, "T3Game")
};

class USpawnPoolLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(USpawnPoolLinkDataObject, ULinkDataObject, UObject, "T3Game")
};

class ASpellProjectile : public AActor
{
    DECLARE_STATIC_CLASS(ASpellProjectile, AActor, UObject, "T3Game")
};

class UT3GameRegistrar : public UTriggerRegistrar
{
    DECLARE_STATIC_CLASS(UT3GameRegistrar, UTriggerRegistrar, UObject, "T3Game")
};

class UAttachment_LinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(UAttachment_LinkDataObject, ULinkDataObject, UObject, "T3Player")
};

class UGarrettEquipLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(UGarrettEquipLinkDataObject, ULinkDataObject, UObject, "T3Player")
};

class UHUDRenderLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(UHUDRenderLinkDataObject, ULinkDataObject, UObject, "T3Player")
};

class UInvenBook_LinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(UInvenBook_LinkDataObject, ULinkDataObject, UObject, "T3Player")
};

class UAI : public UAISubsystem
{
    DECLARE_STATIC_CLASS(UAI, UAISubsystem, UObject, "AICore")
};

class AAIModel : public AMetaProperty
{
    DECLARE_STATIC_CLASS(AAIModel, AMetaProperty, UObject, "AICore")
};

class AAIPathPoint : public AMarker
{
    DECLARE_STATIC_CLASS(AAIPathPoint, AMarker, UObject, "AICore")
};

class AAIPawn : public APawn
{
    DECLARE_STATIC_CLASS(AAIPawn, APawn, UObject, "AICore")
};

class AFocusPoint : public AMarker
{
    DECLARE_STATIC_CLASS(AFocusPoint, AMarker, UObject, "AICore")
};

class ANavMeshInsertionPoint : public AMarker
{
    DECLARE_STATIC_CLASS(ANavMeshInsertionPoint, AMarker, UObject, "AICore")
};

class UT3Game : public UGameSubsystem
{
    DECLARE_STATIC_CLASS(UT3Game, UGameSubsystem, UObject, "T3Player")
};

class AAIBehaviorModel : public AAIModel
{
    DECLARE_STATIC_CLASS(AAIBehaviorModel, AAIModel, UObject, "AICore")
};

class AAICombatModel : public AAIModel
{
    DECLARE_STATIC_CLASS(AAICombatModel, AAIModel, UObject, "AICore")
};

class AAIContextVolume : public AVolume
{
    DECLARE_STATIC_CLASS(AAIContextVolume, AVolume, UObject, "AICore")
};

class AAIFactionModel : public AAIModel
{
    DECLARE_STATIC_CLASS(AAIFactionModel, AAIModel, UObject, "AICore")
};

class AAIMovementModel : public AAIModel
{
    DECLARE_STATIC_CLASS(AAIMovementModel, AAIModel, UObject, "AICore")
};

class AAIPawnController : public AAIController
{
    DECLARE_STATIC_CLASS(AAIPawnController, AAIController, UObject, "AICore")
};

class AAISensoryModel : public AAIModel
{
    DECLARE_STATIC_CLASS(AAISensoryModel, AAIModel, UObject, "AICore")
};

class AAITaggedVolume : public AVolume
{
    DECLARE_STATIC_CLASS(AAITaggedVolume, AVolume, UObject, "AICore")
};

class AAddAIPoint : public AAIPathPoint
{
    DECLARE_STATIC_CLASS(AAddAIPoint, AAIPathPoint, UObject, "AICore")
};

class AChangeDirectionPoint : public AAIPathPoint
{
    DECLARE_STATIC_CLASS(AChangeDirectionPoint, AAIPathPoint, UObject, "AICore")
};

class ACitySectionPopulationInfo : public AInfo
{
    DECLARE_STATIC_CLASS(ACitySectionPopulationInfo, AInfo, UObject, "AICore")
};

class AFormationPoint : public AAIPathPoint
{
    DECLARE_STATIC_CLASS(AFormationPoint, AAIPathPoint, UObject, "AICore")
};

class AFormationPointAbsolute : public AAIPathPoint
{
    DECLARE_STATIC_CLASS(AFormationPointAbsolute, AAIPathPoint, UObject, "AICore")
};

class AHeadTurnPoint : public AAIPathPoint
{
    DECLARE_STATIC_CLASS(AHeadTurnPoint, AAIPathPoint, UObject, "AICore")
};

class ALookPoint : public AAIPathPoint
{
    DECLARE_STATIC_CLASS(ALookPoint, AAIPathPoint, UObject, "AICore")
};

class ANavMeshSubtractionVolume : public AVolume
{
    DECLARE_STATIC_CLASS(ANavMeshSubtractionVolume, AVolume, UObject, "AICore")
};

class APatrolPoint : public AAIPathPoint
{
    DECLARE_STATIC_CLASS(APatrolPoint, AAIPathPoint, UObject, "AICore")
};

class ADifficultyInfo : public AInfo
{
    DECLARE_STATIC_CLASS(ADifficultyInfo, AInfo, UObject, "T3Game")
};

class AEnterMissionInfo : public AInfo
{
    DECLARE_STATIC_CLASS(AEnterMissionInfo, AInfo, UObject, "T3Game")
};

class AExitMissionInfo : public AInfo
{
    DECLARE_STATIC_CLASS(AExitMissionInfo, AInfo, UObject, "T3Game")
};

class AWakeupCameraPoint : public AKeypoint
{
    DECLARE_STATIC_CLASS(AWakeupCameraPoint, AKeypoint, UObject, "T3Game")
};

class UT3GamePhysics : public UGamePhysics
{
    DECLARE_STATIC_CLASS(UT3GamePhysics, UGamePhysics, UObject, "T3GamePhysics")
};

class AGarrett : public APlayerPawn
{
    DECLARE_STATIC_CLASS(AGarrett, APlayerPawn, UObject, "T3Player")
};

class UT3GameEngine : public UGameEngine
{
    DECLARE_STATIC_CLASS(UT3GameEngine, UGameEngine, UObject, "T3Player")
};

class AT3PlayerController : public APlayerController
{
    DECLARE_STATIC_CLASS(AT3PlayerController, APlayerController, UObject, "T3Player")
};

class ACityPopPoint : public APatrolPoint
{
    DECLARE_STATIC_CLASS(ACityPopPoint, APatrolPoint, UObject, "AICore")
};

class APlayAnimPoint : public ALookPoint
{
    DECLARE_STATIC_CLASS(APlayAnimPoint, ALookPoint, UObject, "AICore")
};

class APlayBarkPoint : public ALookPoint
{
    DECLARE_STATIC_CLASS(APlayBarkPoint, ALookPoint, UObject, "AICore")
};

class AWanderPoint : public APatrolPoint
{
    DECLARE_STATIC_CLASS(AWanderPoint, APatrolPoint, UObject, "AICore")
};

class AT3AIPawnController : public AAIPawnController
{
    DECLARE_STATIC_CLASS(AT3AIPawnController, AAIPawnController, UObject, "T3AI")
};

class AT3BehaviorModel : public AAIBehaviorModel
{
    DECLARE_STATIC_CLASS(AT3BehaviorModel, AAIBehaviorModel, UObject, "T3AI")
};

class AT3CombatModel : public AAICombatModel
{
    DECLARE_STATIC_CLASS(AT3CombatModel, AAICombatModel, UObject, "T3AI")
};

class AT3FactionModel : public AAIFactionModel
{
    DECLARE_STATIC_CLASS(AT3FactionModel, AAIFactionModel, UObject, "T3AI")
};

class AT3MovementModel : public AAIMovementModel
{
    DECLARE_STATIC_CLASS(AT3MovementModel, AAIMovementModel, UObject, "T3AI")
};

class AT3SensoryModel : public AAISensoryModel
{
    DECLARE_STATIC_CLASS(AT3SensoryModel, AAISensoryModel, UObject, "T3AI")
};
