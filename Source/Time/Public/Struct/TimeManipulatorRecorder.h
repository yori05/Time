// Property of Florian Hulin, shouldn't be used without my consent.

#pragma once

#include "CoreMinimal.h"

#include "TimeManipulatorRecorder.generated.h"

class UCurveFloat;
class UCurveVector;
class UCurveLinearColor;

/**
*  Recorder float
*  Part of the Time Manipulator system
*
* Used by the time manipulator component will link the float value and record her variation in the time.
* Will keep a copy of this value when editing or looking at the curve
*
*/
USTRUCT(BlueprintType)
struct FTimeRecorderFloat
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCurveFloat> Curve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time", meta = (AllowPrivateAccess = "true"))
	float Value;
};

/**
*  Recorder Vector
*  Part of the Time Manipulator system
*
* Used by the time manipulator component will link the vector value and record his variation in the time.
* Will keep a copy of this value when editing or looking at the curve
*
*/
USTRUCT(BlueprintType)
struct FTimeRecorderVector
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCurveVector> Curve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time", meta = (AllowPrivateAccess = "true"))
	FVector Value;
};

/**
*  Recorder Rotator
*  Part of the Time Manipulator system
*
* Used by the time manipulator component will link the rotator value and record his variation in the time.
* Will keep a copy of this value when editing or looking at the curve
* 
* Could use the rotator recording XYZW or two directionnal vector will compare result to set the meth to keep
*
*/
USTRUCT(BlueprintType)
struct FTimeRecorderRotator
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCurveLinearColor> Curve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time", meta = (AllowPrivateAccess = "true"))
	FRotator Value;
};

/**
*  Recorder Rotator
*  Part of the Time Manipulator system
*
* Used by the time manipulator component will link the rotator value and record his variation in the time.
* Will keep a copy of this value when editing or looking at the curve
*
* Could use the rotator recording XYZW or two directionnal vector will compare result to set the meth to keep
*
*/
USTRUCT(BlueprintType)
struct FTimeRecorderDirectionnalRotator
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCurveVector> ForwardCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCurveVector> UpCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time", meta = (AllowPrivateAccess = "true"))
	FRotator Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time", meta = (AllowPrivateAccess = "true"))
	FVector ForwardValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time", meta = (AllowPrivateAccess = "true"))
	FVector UpValue;

};

//	Could add a recorder with CurveTable in case we want something else
