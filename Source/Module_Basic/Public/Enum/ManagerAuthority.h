// Property of Florian Hulin, shouldn't be used without my consent.

#pragma once

#include "CoreMinimal.h"

#include "ManagerAuthority.generated.h"

/**
*  Manager authority :
* State of the authority of the manager using this enum
* Define how he will interact with the component he have the power on :
*  - Will get the full power on them
*  - Will controle them only if the component want to
*  - Won't be able to controle any component
*
*/
UENUM(BlueprintType)
enum class EManagerAuthority : uint8
{
	/** The manager will haave full power on his linked component */
	MANAGERAUTHORITY_Full = 0 UMETA(DisplayName = "Full"),

	/** The manager will control only the component that chose to listen to him */
	MANAGERAUTHORITY_Listen UMETA(DisplayName = "Listen"),

	/** The manager won't have any power on any component */
	MANAGERAUTHORITY_Silence UMETA(DisplayName = "Silence"),

	/** Size of this Enum */
	MANAGERAUTHORITY_Max UMETA(Hidden),
};
