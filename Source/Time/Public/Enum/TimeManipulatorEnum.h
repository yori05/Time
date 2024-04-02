// Property of Florian Hulin, shouldn't be used without my consent.

#pragma once

#include "CoreMinimal.h"

#include "TimeManipulatorEnum.generated.h"

/**
*  TimeManipulator State :
* State of the time manipulation
* Define in which state the object having this enum is :
*  - Forward
*  - Hold
*  - Backward
*
*/
UENUM(BlueprintType)
enum class ETimeManipulatorState : uint8
{
	/** Using to say the time is on forward movement, usually when the timeRecorder are recording event */
	TMS_Forward = 0 UMETA(DisplayName = "Forward"),

	/** Using to say the time is on hold, usually when the timeRecorder are on hold as well */
	TMS_Hold UMETA(DisplayName = "Hold"),

	/** Using to say the time is on backward movement, usually when the timeRecorder are rewind event */
	TMS_Backward UMETA(DisplayName = "Backward"),

	/** Size of this Enum */
	TMS_Max UMETA(Hidden),
};
