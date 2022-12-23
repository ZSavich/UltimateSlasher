// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/Pawn.h"
#include "Bird.generated.h"

class USphereComponent;
class UCameraComponent;
class USpringArmComponent;
class UInputAction;
class UInputMappingContext;

UCLASS()
class ULTIMATESLASHER_API ABird : public APawn
{
	GENERATED_BODY()

protected:
	/** General Components **/
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USkeletalMeshComponent* BirdMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UFloatingPawnMovement* BirdMovementComponent;

	/** Enhanced Input Assets **/
	UPROPERTY(EditDefaultsOnly, Category = "Input | Contexts")
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input | Actions")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input | Actions")
	UInputAction* LookAction;
	
public:
	ABird();

protected:
	virtual void BeginPlay() override;

	/** Enhanced Input Functions **/
	void EnhancedMove(const FInputActionValue& Value);
	void EnhancedLook(const FInputActionValue& Value);

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
