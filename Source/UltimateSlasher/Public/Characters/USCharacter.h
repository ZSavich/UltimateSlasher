// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "USCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;
class UGroomComponent;

UCLASS()
class ULTIMATESLASHER_API AUSCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	/** Character's Camera Components **/
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	UCameraComponent* FollowCamera;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	USpringArmComponent* CameraBoom;

	/** Groom Components **/
	UPROPERTY(EditDefaultsOnly, Category = "Groom")
	UGroomComponent* HairGroom;

	UPROPERTY(EditDefaultsOnly, Category = "Groom")
	UGroomComponent* EyebrowsGroom;
	
	/** Enhanced Input Actions **/
	UPROPERTY(EditDefaultsOnly, Category = "Inputs | Mapping Context")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Inputs | Actions")
	UInputAction* MovementAction;

	UPROPERTY(EditDefaultsOnly, Category = "Inputs | Actions")
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Inputs | Actions")
	UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly, Category = "Inputs | Actions")
	UInputAction* EKeyAction;

	UPROPERTY(EditDefaultsOnly, Category = "Inputs | Actions")
	UInputAction* AttackAction;

	UPROPERTY(EditDefaultsOnly, Category = "Inputs | Actions")
	UInputAction* DodgeAction;

public:
	AUSCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	/** Enhanced Input Functions **/
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void EKeyPressed(const FInputActionValue& Value);
	void Attack(const FInputActionValue& Value);
	void Dodge(const FInputActionValue& Value);
};
