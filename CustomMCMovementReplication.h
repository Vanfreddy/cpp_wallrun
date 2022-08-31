// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomMCMovementTypes.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <GameFramework/CharacterMovementReplication.h>


class FSavedMove_CustomMCCharacter : public FSavedMove_Character
{
public:

	typedef FSavedMove_Character Super;

	// Settings
	float WallNormalThresholdCombine = 0.01;

	// Gameplay variables
	uint8 bWallrunWantsToUnstick : 1;
	float WantsToUnstickTimeRemaining = 0.0f;
	EWallRunSide WallRunSide = EWallRunSide::Left;
	// Done, possible need to decrease the WallNormalThresholdCombine
	FVector WallRunWallNormal = FVector::ZeroVector;
	float CurrentWallRunEndGravity = 1.0f;
	EWallRunState WallRunState = EWallRunState::End;
	float WallRunTimeRemaining = 0.0f;
	float WallRunCooldownLeftTimeRemaining = 0.0f;
	float WallRunCooldownRightTimeRemaining = 0.0f;

	// Overrides
	virtual void Clear() override;
	virtual uint8 GetCompressedFlags() const override;
	virtual bool CanCombineWith(const FSavedMovePtr& NewMovePtr, ACharacter* Character, float MaxDelta) const override;
	virtual void CombineWith(const FSavedMove_Character* OldMove, ACharacter* InCharacter, APlayerController* PC, const FVector& OldStartLocation) override;
	virtual void SetMoveFor(ACharacter* Character, float InDeltaTime, FVector const& NewAccel, class FNetworkPredictionData_Client_Character& ClientData) override;
	virtual void PrepMoveFor(class ACharacter* Character) override;
	virtual bool IsImportantMove(const FSavedMovePtr& LastAckedMove) const;


};

class FNetworkPredictionData_Client_CustomMCCharacter : public FNetworkPredictionData_Client_Character
{
public:
	typedef FNetworkPredictionData_Client_Character Super;

	FNetworkPredictionData_Client_CustomMCCharacter(const UCharacterMovementComponent& ClientMovement);

	virtual FSavedMovePtr AllocateNewMove() override;
};


struct  FCustomMCCharacterNetworkMoveData : FCharacterNetworkMoveData
{
public:
	bool bWantsToUnstick = false;

	virtual void ClientFillNetworkMoveData(const FSavedMove_Character& ClientMove, ENetworkMoveType MoveType) override;
	virtual bool Serialize(UCharacterMovementComponent& CharacterMovement, FArchive& Ar, UPackageMap* PackageMap, ENetworkMoveType MoveType) override;

private:
	typedef FCharacterNetworkMoveData Super;
};


struct  FCustomMCCharacterNetworkMoveDataContainer
	: FCharacterNetworkMoveDataContainer
{
public:
	FCustomMCCharacterNetworkMoveDataContainer();

private:
	typedef FCharacterNetworkMoveDataContainer Super;
	FCustomMCCharacterNetworkMoveData BFDefaultMoveData[3];
};
