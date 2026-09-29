// Classes known so far by name, package, superclass and within class: from
// the class objects Ion Storm builds on first use (DECLARE_STATIC_CLASS) and
// the initializer each links them with (IMPLEMENT_STATIC_CLASS). Actors
// (classes under Actor) take the A prefix, the others U. Layouts are not
// declared yet. Generated from the executable's class objects; edit by hand
// once a class gains fields.
#pragma once

#include "Core/CoreClasses.h"

class AActor : public UObject
{
    DECLARE_STATIC_CLASS(AActor, UObject, UObject, "Engine")
};

class UAnimation : public UObject
{
    DECLARE_STATIC_CLASS(UAnimation, UObject, UObject, "Engine")
};

class UBitmap : public UObject
{
    DECLARE_STATIC_CLASS(UBitmap, UObject, UObject, "Engine")
};

class UCARDEntry : public UObject
{
    DECLARE_STATIC_CLASS(UCARDEntry, UObject, UObject, "Engine")
};

class UCanvas : public UObject
{
    DECLARE_STATIC_CLASS(UCanvas, UObject, UObject, "Engine")
};

class UClient : public UObject
{
    DECLARE_STATIC_CLASS(UClient, UObject, UObject, "Engine")
};

class UFont : public UObject
{
    DECLARE_STATIC_CLASS(UFont, UObject, UObject, "Engine")
};

class ULevelBase : public UObject
{
    DECLARE_STATIC_CLASS(ULevelBase, UObject, UObject, "Engine")
};

class UMatObject : public UObject
{
    DECLARE_STATIC_CLASS(UMatObject, UObject, UObject, "Engine")
};

class UMeshAnimation : public UObject
{
    DECLARE_STATIC_CLASS(UMeshAnimation, UObject, UObject, "Engine")
};

class UPalette : public UObject
{
    DECLARE_STATIC_CLASS(UPalette, UObject, UObject, "Engine")
};

class UParticleEmitter : public UObject
{
    DECLARE_STATIC_CLASS(UParticleEmitter, UObject, UObject, "Engine")
};

class UPlayer : public UObject
{
    DECLARE_STATIC_CLASS(UPlayer, UObject, UObject, "Engine")
};

class UPolys : public UObject
{
    DECLARE_STATIC_CLASS(UPolys, UObject, UObject, "Engine")
};

class UPrimitive : public UObject
{
    DECLARE_STATIC_CLASS(UPrimitive, UObject, UObject, "Engine")
};

class URenderResource : public UObject
{
    DECLARE_STATIC_CLASS(URenderResource, UObject, UObject, "Engine")
};

class UStaticMesh : public UObject
{
    DECLARE_STATIC_CLASS(UStaticMesh, UObject, UObject, "Engine")
};

class UTriggerRegistrar : public UObject
{
    DECLARE_STATIC_CLASS(UTriggerRegistrar, UObject, UObject, "Engine")
};

class UWindowManager : public UObject
{
    DECLARE_STATIC_CLASS(UWindowManager, UObject, UObject, "Window")
};

class UAISubsystem : public USubsystem
{
    DECLARE_STATIC_CLASS(UAISubsystem, USubsystem, UObject, "Engine")
};

class UAlarmLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(UAlarmLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class UAmmoLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(UAmmoLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class UAssociationLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(UAssociationLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class UAttachmentLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(UAttachmentLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class UBeamEmitter : public UParticleEmitter
{
    DECLARE_STATIC_CLASS(UBeamEmitter, UParticleEmitter, UObject, "Engine")
};

class UBotDominationLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(UBotDominationLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class UBreakingBeamLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(UBreakingBeamLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class ABrush : public AActor
{
    DECLARE_STATIC_CLASS(ABrush, AActor, UObject, "Engine")
};

class UCinematicLightLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(UCinematicLightLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class AController : public AActor
{
    DECLARE_STATIC_CLASS(AController, AActor, UObject, "Engine")
};

class UDestroyOnDeathLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(UDestroyOnDeathLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class UDoorLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(UDoorLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class UElevatorFloorMarkerLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(UElevatorFloorMarkerLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class UElevatorLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(UElevatorLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class UEngine : public USubsystem
{
    DECLARE_STATIC_CLASS(UEngine, USubsystem, UObject, "Engine")
};

class AFX : public AActor
{
    DECLARE_STATIC_CLASS(AFX, AActor, UObject, "Engine")
};

class UFillLightLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(UFillLightLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class UFireEffectLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(UFireEffectLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class UFrobEventLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(UFrobEventLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class UFrobLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(UFrobLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class UGameSubsystem : public USubsystem
{
    DECLARE_STATIC_CLASS(UGameSubsystem, USubsystem, UObject, "Engine")
};

class UHardpointLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(UHardpointLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class UHighlightEventLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(UHighlightEventLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class UHitSpangLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(UHitSpangLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class UIndexBuffer : public URenderResource
{
    DECLARE_STATIC_CLASS(UIndexBuffer, URenderResource, UObject, "Engine")
};

class UInterestLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(UInterestLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class ULevel : public ULevelBase
{
    DECLARE_STATIC_CLASS(ULevel, ULevelBase, UObject, "Engine")
};

class ALight : public AActor
{
    DECLARE_STATIC_CLASS(ALight, AActor, UObject, "Engine")
};

class ULightLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(ULightLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class ULoadoutLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(ULoadoutLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class ULockAssociationLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(ULockAssociationLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class AMarker : public AActor
{
    DECLARE_STATIC_CLASS(AMarker, AActor, UObject, "Engine")
};

class UMatAction : public UMatObject
{
    DECLARE_STATIC_CLASS(UMatAction, UMatObject, UObject, "Engine")
};

class UMatSubAction : public UMatObject
{
    DECLARE_STATIC_CLASS(UMatSubAction, UMatObject, UObject, "Engine")
};

class UMesh : public UPrimitive
{
    DECLARE_STATIC_CLASS(UMesh, UPrimitive, UObject, "Engine")
};

class UMeshEmitter : public UParticleEmitter
{
    DECLARE_STATIC_CLASS(UMeshEmitter, UParticleEmitter, UObject, "Engine")
};

class UMeshInstance : public UPrimitive
{
    DECLARE_STATIC_CLASS(UMeshInstance, UPrimitive, UObject, "Engine")
};

class AMetaData : public AActor
{
    DECLARE_STATIC_CLASS(AMetaData, AActor, UObject, "Engine")
};

class AMetaProperty : public AActor
{
    DECLARE_STATIC_CLASS(AMetaProperty, AActor, UObject, "Engine")
};

class AMissingArch : public AActor
{
    DECLARE_STATIC_CLASS(AMissingArch, AActor, UObject, "Engine")
};

class UModel : public UPrimitive
{
    DECLARE_STATIC_CLASS(UModel, UPrimitive, UObject, "Engine")
};

class UMovementModeLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(UMovementModeLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class AObjSysTest : public AActor
{
    DECLARE_STATIC_CLASS(AObjSysTest, AActor, UObject, "Engine")
};

class UOwnershipLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(UOwnershipLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class APawn : public AActor
{
    DECLARE_STATIC_CLASS(APawn, AActor, UObject, "Engine")
};

class UPhysicsSubsystem : public USubsystem
{
    DECLARE_STATIC_CLASS(UPhysicsSubsystem, USubsystem, UObject, "Engine")
};

class UPlayerSetupInfoLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(UPlayerSetupInfoLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class UPowerLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(UPowerLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class UProjectileLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(UProjectileLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class UPuddleConnectorLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(UPuddleConnectorLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class UPuddleMarkLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(UPuddleMarkLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class UReferenceLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(UReferenceLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class URenderDevice : public USubsystem
{
    DECLARE_STATIC_CLASS(URenderDevice, USubsystem, UObject, "Engine")
};

class URuntimeFireEffectLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(URuntimeFireEffectLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class UServerCommandlet : public UCommandlet
{
    DECLARE_STATIC_CLASS(UServerCommandlet, UCommandlet, UObject, "Engine")
};

class USittingLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(USittingLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class USkeletalFireEffectLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(USkeletalFireEffectLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class USkinVertexBuffer : public URenderResource
{
    DECLARE_STATIC_CLASS(USkinVertexBuffer, URenderResource, UObject, "Engine")
};

class USleepingLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(USleepingLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class USparkEmitter : public UParticleEmitter
{
    DECLARE_STATIC_CLASS(USparkEmitter, UParticleEmitter, UObject, "Engine")
};

class USpawnLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(USpawnLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class USpriteEmitter : public UParticleEmitter
{
    DECLARE_STATIC_CLASS(USpriteEmitter, UParticleEmitter, UObject, "Engine")
};

class AStaticMeshActor : public AActor
{
    DECLARE_STATIC_CLASS(AStaticMeshActor, AActor, UObject, "Engine")
};

class UStimulusModifierLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(UStimulusModifierLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class USwooshLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(USwooshLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class UTargetLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(UTargetLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class UTexture : public UBitmap
{
    DECLARE_STATIC_CLASS(UTexture, UBitmap, UObject, "Engine")
};

class UTriggerScriptLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(UTriggerScriptLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class UUserArmImplementationLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(UUserArmImplementationLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class UUserLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(UUserLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class UVertexStreamBase : public URenderResource
{
    DECLARE_STATIC_CLASS(UVertexStreamBase, URenderResource, UObject, "Engine")
};

class UViewport : public UPlayer
{
    DECLARE_STATIC_CLASS(UViewport, UPlayer, UClient, "Engine")
};

class UVulnerabilityLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(UVulnerabilityLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class UWaypointInterpolationLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(UWaypointInterpolationLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class UWeaponModLinkDataObject : public ULinkDataObject
{
    DECLARE_STATIC_CLASS(UWeaponModLinkDataObject, ULinkDataObject, UObject, "Engine")
};

class UWindowsClient : public UClient
{
    DECLARE_STATIC_CLASS(UWindowsClient, UClient, UObject, "WinDrv")
};

class UD3DRenderDevice : public URenderDevice
{
    DECLARE_STATIC_CLASS(UD3DRenderDevice, URenderDevice, UObject, "D3DDrv")
};

class AAIController : public AController
{
    DECLARE_STATIC_CLASS(AAIController, AController, UObject, "Engine")
};

class UActionMoveCamera : public UMatAction
{
    DECLARE_STATIC_CLASS(UActionMoveCamera, UMatAction, UObject, "Engine")
};

class UActionPause : public UMatAction
{
    DECLARE_STATIC_CLASS(UActionPause, UMatAction, UObject, "Engine")
};

class UCreationSpawnLinkDataObject : public UHardpointLinkDataObject
{
    DECLARE_STATIC_CLASS(UCreationSpawnLinkDataObject, UHardpointLinkDataObject, UObject, "Engine")
};

class UCubemap : public UTexture
{
    DECLARE_STATIC_CLASS(UCubemap, UTexture, UObject, "Engine")
};

class UDeathSpawnLinkDataObject : public UHardpointLinkDataObject
{
    DECLARE_STATIC_CLASS(UDeathSpawnLinkDataObject, UHardpointLinkDataObject, UObject, "Engine")
};

class UDynamicBeamEmitter : public UBeamEmitter
{
    DECLARE_STATIC_CLASS(UDynamicBeamEmitter, UBeamEmitter, UObject, "Engine")
};

class AElevatorFloors : public AMetaData
{
    DECLARE_STATIC_CLASS(AElevatorFloors, AMetaData, UObject, "Engine")
};

class AEmitter : public AFX
{
    DECLARE_STATIC_CLASS(AEmitter, AFX, UObject, "Engine")
};

class UFlinderizeLinkDataObject : public UHardpointLinkDataObject
{
    DECLARE_STATIC_CLASS(UFlinderizeLinkDataObject, UHardpointLinkDataObject, UObject, "Engine")
};

class UGameEngine : public UEngine
{
    DECLARE_STATIC_CLASS(UGameEngine, UEngine, UObject, "Engine")
};

class UHingedAttachmentLinkDataObject : public UAttachmentLinkDataObject
{
    DECLARE_STATIC_CLASS(UHingedAttachmentLinkDataObject, UAttachmentLinkDataObject, UObject, "Engine")
};

class AInfo : public AMetaData
{
    DECLARE_STATIC_CLASS(AInfo, AMetaData, UObject, "Engine")
};

class AKeypoint : public AMarker
{
    DECLARE_STATIC_CLASS(AKeypoint, AMarker, UObject, "Engine")
};

class ULodMesh : public UMesh
{
    DECLARE_STATIC_CLASS(ULodMesh, UMesh, UObject, "Engine")
};

class ULodMeshInstance : public UMeshInstance
{
    DECLARE_STATIC_CLASS(ULodMeshInstance, UMeshInstance, UObject, "Engine")
};

class AObjSysTestChild : public AObjSysTest
{
    DECLARE_STATIC_CLASS(AObjSysTestChild, AObjSysTest, UObject, "Engine")
};

class APlayerController : public AController
{
    DECLARE_STATIC_CLASS(APlayerController, AController, UObject, "Engine")
};

class APlayerPawn : public APawn
{
    DECLARE_STATIC_CLASS(APlayerPawn, APawn, UObject, "Engine")
};

class UPointAttachmentLinkDataObject : public UAttachmentLinkDataObject
{
    DECLARE_STATIC_CLASS(UPointAttachmentLinkDataObject, UAttachmentLinkDataObject, UObject, "Engine")
};

class URigidAttachmentLinkDataObject : public UAttachmentLinkDataObject
{
    DECLARE_STATIC_CLASS(URigidAttachmentLinkDataObject, UAttachmentLinkDataObject, UObject, "Engine")
};

class URuntimeAttachmentLinkDataObject : public UAttachmentLinkDataObject
{
    DECLARE_STATIC_CLASS(URuntimeAttachmentLinkDataObject, UAttachmentLinkDataObject, UObject, "Engine")
};

class USlidingAttachmentLinkDataObject : public UAttachmentLinkDataObject
{
    DECLARE_STATIC_CLASS(USlidingAttachmentLinkDataObject, UAttachmentLinkDataObject, UObject, "Engine")
};

class USpawnableHardpointLinkDataObject : public UHardpointLinkDataObject
{
    DECLARE_STATIC_CLASS(USpawnableHardpointLinkDataObject, UHardpointLinkDataObject, UObject, "Engine")
};

class ASpecialOptions : public AMetaData
{
    DECLARE_STATIC_CLASS(ASpecialOptions, AMetaData, UObject, "Engine")
};

class AStimulusModifierObject : public AMetaProperty
{
    DECLARE_STATIC_CLASS(AStimulusModifierObject, AMetaProperty, UObject, "Engine")
};

class USubActionFOV : public UMatSubAction
{
    DECLARE_STATIC_CLASS(USubActionFOV, UMatSubAction, UObject, "Engine")
};

class USubActionFade : public UMatSubAction
{
    DECLARE_STATIC_CLASS(USubActionFade, UMatSubAction, UObject, "Engine")
};

class USubActionGameSpeed : public UMatSubAction
{
    DECLARE_STATIC_CLASS(USubActionGameSpeed, UMatSubAction, UObject, "Engine")
};

class USubActionOrientation : public UMatSubAction
{
    DECLARE_STATIC_CLASS(USubActionOrientation, UMatSubAction, UObject, "Engine")
};

class USubActionSceneSpeed : public UMatSubAction
{
    DECLARE_STATIC_CLASS(USubActionSceneSpeed, UMatSubAction, UObject, "Engine")
};

class USubActionTrigger : public UMatSubAction
{
    DECLARE_STATIC_CLASS(USubActionTrigger, UMatSubAction, UObject, "Engine")
};

class ASwooshEffectObject : public AMetaProperty
{
    DECLARE_STATIC_CLASS(ASwooshEffectObject, AMetaProperty, UObject, "Engine")
};

class UVertexBuffer : public UVertexStreamBase
{
    DECLARE_STATIC_CLASS(UVertexBuffer, UVertexStreamBase, UObject, "Engine")
};

class UVertexStreamCOLOR : public UVertexStreamBase
{
    DECLARE_STATIC_CLASS(UVertexStreamCOLOR, UVertexStreamBase, UObject, "Engine")
};

class UVertexStreamPosNormTex : public UVertexStreamBase
{
    DECLARE_STATIC_CLASS(UVertexStreamPosNormTex, UVertexStreamBase, UObject, "Engine")
};

class UVertexStreamUV : public UVertexStreamBase
{
    DECLARE_STATIC_CLASS(UVertexStreamUV, UVertexStreamBase, UObject, "Engine")
};

class UVertexStreamVECTOR : public UVertexStreamBase
{
    DECLARE_STATIC_CLASS(UVertexStreamVECTOR, UVertexStreamBase, UObject, "Engine")
};

class AVolume : public ABrush
{
    DECLARE_STATIC_CLASS(AVolume, ABrush, UObject, "Engine")
};

class AVulnerabilityObject : public AMetaProperty
{
    DECLARE_STATIC_CLASS(AVulnerabilityObject, AMetaProperty, UObject, "Engine")
};

class UFractalTexture : public UTexture
{
    DECLARE_STATIC_CLASS(UFractalTexture, UTexture, UObject, "Fire")
};

class UGamePhysics : public UPhysicsSubsystem
{
    DECLARE_STATIC_CLASS(UGamePhysics, UPhysicsSubsystem, UObject, "GamePhysics")
};

class UWindowsViewport : public UViewport
{
    DECLARE_STATIC_CLASS(UWindowsViewport, UViewport, UWindowsClient, "WinDrv")
};

class AAmbientLightVolume : public AVolume
{
    DECLARE_STATIC_CLASS(AAmbientLightVolume, AVolume, UObject, "Engine")
};

class ACamera : public APlayerController
{
    DECLARE_STATIC_CLASS(ACamera, APlayerController, UObject, "Engine")
};

class ACameraPoint : public AKeypoint
{
    DECLARE_STATIC_CLASS(ACameraPoint, AKeypoint, UObject, "Engine")
};

class AClipMarker : public AKeypoint
{
    DECLARE_STATIC_CLASS(AClipMarker, AKeypoint, UObject, "Engine")
};

class UCollisionSpawnLinkDataObject : public USpawnableHardpointLinkDataObject
{
    DECLARE_STATIC_CLASS(UCollisionSpawnLinkDataObject, USpawnableHardpointLinkDataObject, UObject, "Engine")
};

class ADeathWaterVolume : public AVolume
{
    DECLARE_STATIC_CLASS(ADeathWaterVolume, AVolume, UObject, "Engine")
};

class UDelaySpawnLinkDataObject : public USpawnableHardpointLinkDataObject
{
    DECLARE_STATIC_CLASS(UDelaySpawnLinkDataObject, USpawnableHardpointLinkDataObject, UObject, "Engine")
};

class UFragRoundLinkDataObject : public UFlinderizeLinkDataObject
{
    DECLARE_STATIC_CLASS(UFragRoundLinkDataObject, UFlinderizeLinkDataObject, UObject, "Engine")
};

class AInterpolationPoint : public AKeypoint
{
    DECLARE_STATIC_CLASS(AInterpolationPoint, AKeypoint, UObject, "Engine")
};

class ALookTarget : public AKeypoint
{
    DECLARE_STATIC_CLASS(ALookTarget, AKeypoint, UObject, "Engine")
};

class ANavigationPoint : public AKeypoint
{
    DECLARE_STATIC_CLASS(ANavigationPoint, AKeypoint, UObject, "Engine")
};

class APhysicsVolume : public AVolume
{
    DECLARE_STATIC_CLASS(APhysicsVolume, AVolume, UObject, "Engine")
};

class APolyMarker : public AKeypoint
{
    DECLARE_STATIC_CLASS(APolyMarker, AKeypoint, UObject, "Engine")
};

class ASceneManager : public AInfo
{
    DECLARE_STATIC_CLASS(ASceneManager, AInfo, UObject, "Engine")
};

class AShallowWaterVolume : public AVolume
{
    DECLARE_STATIC_CLASS(AShallowWaterVolume, AVolume, UObject, "Engine")
};

class USkeletalMesh : public ULodMesh
{
    DECLARE_STATIC_CLASS(USkeletalMesh, ULodMesh, UObject, "Engine")
};

class USkeletalMeshInstance : public ULodMeshInstance
{
    DECLARE_STATIC_CLASS(USkeletalMeshInstance, ULodMeshInstance, UObject, "Engine")
};

class ATerrainInfo : public AInfo
{
    DECLARE_STATIC_CLASS(ATerrainInfo, AInfo, UObject, "Engine")
};

class UVertMesh : public ULodMesh
{
    DECLARE_STATIC_CLASS(UVertMesh, ULodMesh, UObject, "Engine")
};

class UVertMeshInstance : public ULodMeshInstance
{
    DECLARE_STATIC_CLASS(UVertMeshInstance, ULodMeshInstance, UObject, "Engine")
};

class AWaypoint : public AKeypoint
{
    DECLARE_STATIC_CLASS(AWaypoint, AKeypoint, UObject, "Engine")
};

class AWaypointMarker : public AKeypoint
{
    DECLARE_STATIC_CLASS(AWaypointMarker, AKeypoint, UObject, "Engine")
};

class AZoneInfo : public AInfo
{
    DECLARE_STATIC_CLASS(AZoneInfo, AInfo, UObject, "Engine")
};

class AZoneProperties : public AInfo
{
    DECLARE_STATIC_CLASS(AZoneProperties, AInfo, UObject, "Engine")
};

class UFireTexture : public UFractalTexture
{
    DECLARE_STATIC_CLASS(UFireTexture, UFractalTexture, UObject, "Fire")
};

class UIceTexture : public UFractalTexture
{
    DECLARE_STATIC_CLASS(UIceTexture, UFractalTexture, UObject, "Fire")
};

class UWaterTexture : public UFractalTexture
{
    DECLARE_STATIC_CLASS(UWaterTexture, UFractalTexture, UObject, "Fire")
};

class ADefaultPhysicsVolume : public APhysicsVolume
{
    DECLARE_STATIC_CLASS(ADefaultPhysicsVolume, APhysicsVolume, UObject, "Engine")
};

class ALevelInfo : public AZoneInfo
{
    DECLARE_STATIC_CLASS(ALevelInfo, AZoneInfo, UObject, "Engine")
};

class ANorthMarker : public ANavigationPoint
{
    DECLARE_STATIC_CLASS(ANorthMarker, ANavigationPoint, UObject, "Engine")
};

class APathNode : public ANavigationPoint
{
    DECLARE_STATIC_CLASS(APathNode, ANavigationPoint, UObject, "Engine")
};

class APlayerStart : public ANavigationPoint
{
    DECLARE_STATIC_CLASS(APlayerStart, ANavigationPoint, UObject, "Engine")
};

class ASkyZoneInfo : public AZoneInfo
{
    DECLARE_STATIC_CLASS(ASkyZoneInfo, AZoneInfo, UObject, "Engine")
};

class UFluidTexture : public UWaterTexture
{
    DECLARE_STATIC_CLASS(UFluidTexture, UWaterTexture, UObject, "Fire")
};

class UWaveTexture : public UWaterTexture
{
    DECLARE_STATIC_CLASS(UWaveTexture, UWaterTexture, UObject, "Fire")
};

class UWetTexture : public UWaterTexture
{
    DECLARE_STATIC_CLASS(UWetTexture, UWaterTexture, UObject, "Fire")
};
