// Property of Florian Hulin, shouldn't be used without my consent.

#pragma once

#include "CoreMinimal.h"
#include "Character/Character_Basic.h"
#include "PlayerCharacter_Basic.generated.h"

class USpringArmComponent;
class UCameraComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogPlayerCharacter, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayCharBasicEventSignature);

/**
 * 
 * PlayerCharacter Basic
 * 
 * Child of Character Basic
 * 
 * Should contain component not needed for an AI like camera, spring arm, etc ...
 * 
 * Could be changed for a Component in the future if child of Character_Basic need to be direved as PlayerCharacter
 * 
 */
UCLASS(config = Game)
class TIME_API APlayerCharacter_Basic : public ACharacter_Basic
{
	GENERATED_BODY()
	
	/**-----------------	Component Part		-----------------*/
private:

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/**-----------------	Constructor Part		-----------------*/
public:

	// Sets default values for this character's properties
	APlayerCharacter_Basic(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/**-----------------	Actor Function Part		-----------------*/
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**-----------------	Component Accessor Part		-----------------*/
public:

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
