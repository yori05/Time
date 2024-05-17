// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**-----------------	Include		-----------------*/

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Character_Basic.generated.h"

/**-----------------	Exterior class declaration		-----------------*/
class UCapsuleComponent;

/**-----------------	Log definition Part		-----------------*/
DECLARE_LOG_CATEGORY_EXTERN(LogChararacterBasic, Log, All);

/**-----------------	Delegate definition Part		-----------------*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCharacterBasicEventSignature);

/**
 *	Character_Basic
 *	
 *  Base For PlCharacter and AICharacter using PlayerController_Basic or AIController_Basic
 *  Should be used to make child if need default movement / action for both PlCharacter and AICharacter, in other case should make a child directly from one of these two. 
 * 
 */
UCLASS(config = Game)
class MODULE_BASIC_API ACharacter_Basic : public ACharacter
{
	GENERATED_BODY()

	/**-----------------	Constructor Part		-----------------*/
public:
	// Sets default values for this character's properties
	ACharacter_Basic(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/**-----------------	Actor Function Part		-----------------*/
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	/**-----------------	Action Function Part		-----------------*/
public:
	//Called by the controller to move the character. Y => Forward Direction | X => Right Direction
	UFUNCTION(BlueprintCallable)
	virtual void Move(FVector2D Value);
};
