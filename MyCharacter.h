// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CustomMCCharacterMovement.h"
#include "MyCharacter.generated.h"

UCLASS()
class AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	// Sets default values for this character's properties
	AMyCharacter(const FObjectInitializer& ObjectInitializer);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement: Wall Running")
	UCustomMCCharacterMovement* CMoveComp;
	/** get camera view type */
	UFUNCTION(BlueprintCallable, Category = Mesh)
		virtual bool IsFirstPerson() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
