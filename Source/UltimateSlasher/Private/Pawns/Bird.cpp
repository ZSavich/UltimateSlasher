// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawns/Bird.h"

#include "EnhancedInputComponent.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"

ABird::ABird()
{
 	PrimaryActorTick.bCanEverTick = false;
	AutoPossessAI = EAutoPossessAI::Disabled;
	AutoPossessPlayer = EAutoReceiveInput::Disabled;
	AIControllerClass = nullptr;
	
	BirdMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>("BirdMovementComponent");
	BirdMovementComponent->MaxSpeed = 900.f;
	BirdMovementComponent->Acceleration = 2000.f;
	BirdMovementComponent->Deceleration = 2000.f;
	
	CapsuleComponent = CreateDefaultSubobject<USphereComponent>("CapsuleComponent");
	CapsuleComponent->SetSphereRadius(15.f);
	SetRootComponent(CapsuleComponent);

	BirdMesh = CreateDefaultSubobject<USkeletalMeshComponent>("BirdMesh");
	BirdMesh->SetupAttachment(GetRootComponent());

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom);
}

void ABird::BeginPlay()
{
	Super::BeginPlay();

	// Make sure that we have a valid PlayerController
	if (const APlayerController* pPlayerController = Cast<APlayerController>(GetController()))
	{
		// Get the Enhanced Input Local Player Subsystem from the Local Player that related to our Player Controller
		if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pPlayerController->GetLocalPlayer()))
		{
			// Clearing out any leftover mappings
			InputSubsystem->ClearAllMappings();

			// Add each Mapping Context, along with their priority values. Higher values out-prioritize lower values. 
			if (DefaultMappingContext)
			{
				InputSubsystem->AddMappingContext(DefaultMappingContext, 1);
			}
		}
	}
	
}

void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Make sure that we are using a UEnhancedInputComponent; If not, the project is not configured correctly
	if (UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// This calls the handler function by name on every tick while the input conditions are met
		// Such as when holding movement key down
		if (MoveAction)
		{
			PlayerEnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABird::EnhancedMove);
		}
		if (LookAction)
		{
			PlayerEnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABird::EnhancedLook);
		}
	}
}

void ABird::EnhancedMove(const FInputActionValue& Value)
{
	// Input is a float
	const float MovementValue = Value.Get<float>();
	
	if (Controller && MovementValue != 0.f)
	{
		// Add Movement to Forward Vector
		AddMovementInput(GetActorForwardVector(), MovementValue);
	}
}

void ABird::EnhancedLook(const FInputActionValue& Value)
{
	// Input is a Vector2D
	const FVector2D LookVector = Value.Get<FVector2D>();

	if (Controller)
	{
		// Add Yaw and Pitch input to Controller
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y);
	}
}
