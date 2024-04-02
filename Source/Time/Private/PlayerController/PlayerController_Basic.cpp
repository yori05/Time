// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/PlayerController_Basic.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Character/PlayerCharacter_Basic.h"
#include "Engine/World.h"
#include "GameMode/GameMode_Basic.h"
#include "InputMappingContext.h"

DEFINE_LOG_CATEGORY(LogPlayerControllerBasic);

/**-----------------	Constructor Part		-----------------*/
APlayerController_Basic::APlayerController_Basic(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	// set our turn rates for input

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> FHDefaultInputMappingContext(TEXT("/Game/Blueprint/Input/IMC_Default"));

	if (FHDefaultInputMappingContext.Object != nullptr)
	{
		DefaultMappingContext = FHDefaultInputMappingContext.Object;
	}


}

void APlayerController_Basic::SetupInputComponent()
{
	Super::SetupInputComponent();

	check(InputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

	// Set up action bindings
	if (IsValid(EnhancedInputComponent)) 
	{
		if (CurrentMappingContext == nullptr && DefaultMappingContext != nullptr)
		{
			CurrentMappingContext = DefaultMappingContext;
		}

		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			InputSystem->AddMappingContext(CurrentMappingContext, 0);
		}

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &APlayerController_Basic::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APlayerController_Basic::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerController_Basic::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerController_Basic::Look);

		// Pause the game
		EnhancedInputComponent->BindAction(PauseGameAction, ETriggerEvent::Started, this, &APlayerController_Basic::PauseGame);
	}
	else
	{
		UE_LOG(LogPlayerControllerBasic, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void APlayerController_Basic::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

/** Called for movement input */
void APlayerController_Basic::Move(const FInputActionValue& Value)
{
	auto MyPawn = GetPawn<APlayerCharacter_Basic>();

	if (IsValid(MyPawn))
	{
		MyPawn->Move(Value.Get<FVector2D>());
	}
}

/** Called for looking input */
void APlayerController_Basic::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	this->AddYawInput(LookAxisVector.X);
	this->AddPitchInput(LookAxisVector.Y);
}

void APlayerController_Basic::Jump()
{
	auto MyPawn = GetPawn<APlayerCharacter_Basic>();

	if (IsValid(MyPawn))
	{
		MyPawn->Jump();
	}
}

void APlayerController_Basic::StopJumping()
{
	auto MyPawn = GetPawn<APlayerCharacter_Basic>();

	if (IsValid(MyPawn))
	{
		MyPawn->StopJumping();
	}
}

void APlayerController_Basic::PauseGame()
{
	if (UWorld* World = GetWorld())
	{
		if (AGameMode_Basic* GM = World->GetAuthGameMode<AGameMode_Basic>())
		{
			if (!GM->RequestPauseGame())
			{
				GM->RequestResumeGame();
			}
		}
	}
}
