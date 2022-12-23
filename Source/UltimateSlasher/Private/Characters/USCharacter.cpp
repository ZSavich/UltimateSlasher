// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/USCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GroomComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

AUSCharacter::AUSCharacter()
{
 	PrimaryActorTick.bCanEverTick = false;
	
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SetupAttachment(GetRootComponent());

	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->bUsePawnControlRotation = false;
	FollowCamera->SetupAttachment(CameraBoom);

	HairGroom = CreateDefaultSubobject<UGroomComponent>("HairGroom");
	HairGroom->SetupAttachment(GetMesh());
	HairGroom->AttachmentName = FString("head");

	EyebrowsGroom = CreateDefaultSubobject<UGroomComponent>("EyebrowsGroom");
	EyebrowsGroom->SetupAttachment(GetMesh());
	EyebrowsGroom->AttachmentName = FString("head");
}

void AUSCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (const APlayerController* PC = GetController<APlayerController>())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			// Remove all mappings that can be added before
			Subsystem->ClearAllMappings();

			// Add Default Mapping
			if (DefaultMappingContext)
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}
}

void AUSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (MovementAction)
		{
			EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AUSCharacter::Move);
		}
		if (LookAction)
		{
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AUSCharacter::Look);
		}
		if (JumpAction)
		{
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		}
		if (EKeyAction)
		{
			EnhancedInputComponent->BindAction(EKeyAction, ETriggerEvent::Triggered, this, &AUSCharacter::EKeyPressed);
		}
		if (AttackAction)
		{
			EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AUSCharacter::Attack);
		}
		if (DodgeAction)
		{
			EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Triggered, this, &AUSCharacter::Dodge);
		}
	}
}

void AUSCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	if (Controller && MovementVector != FVector2D::Zero())
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawDirection(0.f, Rotation.Yaw, 0.f);

		const FVector ForwardDirection = FRotationMatrix(YawDirection).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawDirection).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.X);
		AddMovementInput(RightDirection, MovementVector.Y);
	}
}

void AUSCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookingVector = Value.Get<FVector2D>();
	if (Controller && LookingVector != FVector2D::Zero())
	{
		AddControllerYawInput(LookingVector.X);
		AddControllerPitchInput(LookingVector.Y);
	}
}

void AUSCharacter::EKeyPressed(const FInputActionValue& Value)
{
	
}

void AUSCharacter::Attack(const FInputActionValue& Value)
{
	
}

void AUSCharacter::Dodge(const FInputActionValue& Value)
{
	
}


