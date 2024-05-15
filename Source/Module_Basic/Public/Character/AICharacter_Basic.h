// Property of Florian Hulin, shouldn't be used without my consent.

#pragma once

/**-----------------	Include declaration		-----------------*/

#include "CoreMinimal.h"
#include "Character/Character_Basic.h"
#include "AICharacter_Basic.generated.h"

/**-----------------	Exterior class declaration		-----------------*/

//class USenseConfigComponent_Basic;

/**-----------------	Log declaration		-----------------*/

DECLARE_LOG_CATEGORY_EXTERN(LogAICharacter, Log, All);

/**-----------------	Delegate declaration		-----------------*/

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAICharBasicEventSignature);

/**
 *  AICharacter Basic
 * 
 * Child of Character Basic
 * 
 * Should contain component not needed for an Player like [something], etc ...
 * 
 * Could be changed for a Component in the future if child of Character_Basic need to be direved as AICharacter
 */
UCLASS(config = Game)
class MODULE_BASIC_API AAICharacter_Basic : public ACharacter_Basic
{
	GENERATED_BODY()
	
	/**-----------------	Component Part		-----------------*/
protected:


	/**-----------------	Constructor Part		-----------------*/
public:

	// Sets default values for this AI controller's properties
	AAICharacter_Basic(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/**-----------------	Component Accessor Part		-----------------*/
public:


};
