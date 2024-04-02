// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerController_Basic.generated.h"


/**-----------------	Exterior class declaration		-----------------*/
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

/**-----------------	Log definition Part		-----------------*/
DECLARE_LOG_CATEGORY_EXTERN(LogPlayerControllerBasic, Log, All);

/**
 * 
 * PlayerController Basic
 * 
 * A Player controller designed to interact witch a Character Basic | PlayerCharacter Basic 
 * Should be keep as a base for every PlayerController specialized to interact with Character Basic's child
 * 
 */
UCLASS(config = Game)
class TIME_API APlayerController_Basic : public APlayerController
{
	GENERATED_BODY()
	
	/**-----------------	Input Variable Part		-----------------*/
private:

	/** DefaultMappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	/** Used MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> CurrentMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;

	/** Pause Game Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> PauseGameAction;

	/**-----------------	Constructor Part		-----------------*/
public:

	/** Set the PlayerController's default value */
	APlayerController_Basic(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/**-----------------	Inherit Function Part		-----------------*/
protected:

	// APawn interface
	virtual void SetupInputComponent() override;

	// To add mapping context
	virtual void BeginPlay() override;

	/**-----------------	Input Function Part		-----------------*/
protected:

	/** Called for movement input */
	UFUNCTION(BlueprintCallable)
	virtual void Move(const FInputActionValue& Value);

	/** Called for looking input */
	UFUNCTION(BlueprintCallable)
	virtual void Look(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	virtual void Jump();

	UFUNCTION(BlueprintCallable)
	virtual void StopJumping();

	UFUNCTION(BlueprintCallable)
	virtual void PauseGame();
};
