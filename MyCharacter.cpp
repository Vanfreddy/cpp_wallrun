// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

// Sets default values
AMyCharacter::AMyCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCustomMCCharacterMovement>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

bool AMyCharacter::IsFirstPerson() const
{
	return Controller && Controller->IsLocalPlayerController();
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	CMoveComp = Cast<UCustomMCCharacterMovement>(Super::GetMovementComponent());
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


bool AMyCharacter::CanJumpInternal_Implementation() const
{
	bool bCanJump = Super::CanJumpInternal_Implementation();
	UCustomMCCharacterMovement* MovCom = Cast<UCustomMCCharacterMovement>(GetCharacterMovement());
	if (!bCanJump && MovCom)
	{
		bCanJump = MovCom->IsWallRunning();
	}
	return bCanJump;
}
