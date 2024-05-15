// Property of Florian Hulin, shouldn't be used without my consent.


#include "Component/TimeManipulator/TMComponent_PhysicsBasic.h"
#include "Curves/CurveLinearColor.h"
#include "Curves/CurveVector.h"
#include "Curves/CurveFloat.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/MovementComponent.h"

/**-----------------	Constructor Part		-----------------*/

UTMComponent_PhysicsBasic::UTMComponent_PhysicsBasic()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

}

/**-----------------	Inherit Function Part		-----------------*/

void UTMComponent_PhysicsBasic::BeginPlay()
{
	Super::BeginPlay();


	if (SavedPhysicComponent == nullptr)
	{
		if (GetOwner() != nullptr)
		{
			SavedPhysicComponent = GetOwner()->GetComponentByClass<UPrimitiveComponent>();
		}
	}

	RecordCurves();
}

/**-----------------	Time State Part		-----------------*/

void UTMComponent_PhysicsBasic::ActivateRecordState()
{
	Super::ActivateRecordState();

	ReplayCurves();

	if (IsValid(SavedPhysicComponent) && bStopPhysicOnState)
	{
		SavedPhysicComponent->SetSimulatePhysics(true);
		SavedPhysicComponent->SetEnableGravity(true);

		SavedPhysicComponent->SetPhysicsLinearVelocity(VelocityVector);
		SavedPhysicComponent->SetPhysicsAngularVelocityInRadians(AngularVelocityVector);
	}
}

void UTMComponent_PhysicsBasic::ActivateStopState()
{
	Super::ActivateStopState();

	if (IsValid(SavedPhysicComponent) && bStopPhysicOnState)
	{
		SavedPhysicComponent->SetSimulatePhysics(false);
		SavedPhysicComponent->SetEnableGravity(false);

		//SavedPhysicComponent->SetPhysicsLinearVelocity(FVector::ZeroVector);
		//SavedPhysicComponent->SetPhysicsAngularVelocityInRadians(FVector::ZeroVector);
	}
}

void UTMComponent_PhysicsBasic::ActivateReplayState()
{
	Super::ActivateReplayState();

	if (IsValid(SavedPhysicComponent) && bStopPhysicOnState)
	{
		SavedPhysicComponent->SetSimulatePhysics(false);
		SavedPhysicComponent->SetEnableGravity(false);

		VelocityVector = SavedPhysicComponent->GetPhysicsLinearVelocity();
		AngularVelocityVector = SavedPhysicComponent->GetPhysicsAngularVelocityInRadians();

		SavedPhysicComponent->SetPhysicsLinearVelocity(FVector::ZeroVector);
		SavedPhysicComponent->SetPhysicsAngularVelocityInRadians(FVector::ZeroVector);
	}
}

/**-----------------	Curve Creation / Destroy Part		-----------------*/

void UTMComponent_PhysicsBasic::CreateCurves()
{
	Super::CreateCurves();

	CreatePhysicsCurves();
}

void UTMComponent_PhysicsBasic::CreatePhysicsCurves()
{
	if (!IsValid(LocationCurve) && bHandleLocation)
	{
		LocationCurve = NewObject<UCurveVector>();
	}

	if (!IsValid(RotationCurve) && bHandleRotation)
	{
		RotationCurve = NewObject<UCurveVector>();
	}

	if (!IsValid(ScaleCurve) && bHandleScale)
	{
		ScaleCurve = NewObject<UCurveVector>();
	}

	if (!IsValid(VelocityCurve) && bHandleVelocity)
	{
		VelocityCurve = NewObject<UCurveVector>();
	}


	if (!IsValid(AngularVelocityCurve) && bHandleAngularVelocity)
	{
		AngularVelocityCurve = NewObject<UCurveVector>();
	}
}

void UTMComponent_PhysicsBasic::DestroyCurves()
{
	Super::DestroyCurves();

	DestroyPhysicsCurves();
}

void UTMComponent_PhysicsBasic::DestroyPhysicsCurves()
{
	if (IsValid(LocationCurve))
	{
		LocationCurve->ConditionalBeginDestroy();
	}
	if (IsValid(RotationCurve))
	{
		RotationCurve->ConditionalBeginDestroy();
	}
	if (IsValid(ScaleCurve))
	{
		ScaleCurve->ConditionalBeginDestroy();
	}
	if (IsValid(VelocityCurve))
	{
		VelocityCurve->ConditionalBeginDestroy();
	}
	if (IsValid(AngularVelocityCurve))
	{
		AngularVelocityCurve->ConditionalBeginDestroy();
	}
}

/**-----------------	Set Curve Part		-----------------*/

void UTMComponent_PhysicsBasic::ResetCurves()
{
	Super::ResetCurves();

	ResetLocationCurve();
	ResetRotationCurve();
	ResetScaleCurve();
	ResetVelocityCurve();
	ResetAngularVelocityCurve();
}

void UTMComponent_PhysicsBasic::ResetLocationCurve()
{
	if (IsValid(LocationCurve))
	{
		LocationCurve->ResetCurve();
	}
}

void UTMComponent_PhysicsBasic::ResetRotationCurve()
{
	if (IsValid(RotationCurve))
	{
		RotationCurve->ResetCurve();
	}
}

void UTMComponent_PhysicsBasic::ResetScaleCurve()
{
	if (IsValid(ScaleCurve))
	{
		ScaleCurve->ResetCurve();
	}
}

void UTMComponent_PhysicsBasic::ResetVelocityCurve()
{
	if (IsValid(VelocityCurve))
	{
		VelocityCurve->ResetCurve();
	}
}

void UTMComponent_PhysicsBasic::ResetAngularVelocityCurve()
{
	if (IsValid(AngularVelocityCurve))
	{
		AngularVelocityCurve->ResetCurve();
	}
}

/**-----------------	Record Curve Part		-----------------*/

void UTMComponent_PhysicsBasic::RecordCurves()
{
	Super::RecordCurves();

	RecordLocationCurve();
	RecordRotationCurve();
	RecordScaleCurve();
	RecordVelocityCurve();
	RecordAngularVelocityCurve();
}

void UTMComponent_PhysicsBasic::RecordLocationCurve()
{
	if (SavedPhysicComponent != nullptr && bHandleLocation)
	{
		LocationVector = SavedPhysicComponent->GetComponentLocation();

		if (IsValid(LocationCurve))
		{
			LocationCurve->FloatCurves[0].UpdateOrAddKey(TimeSaved, LocationVector.X, false, TimeStep / 2.f);
			LocationCurve->FloatCurves[1].UpdateOrAddKey(TimeSaved, LocationVector.Y, false, TimeStep / 2.f);
			LocationCurve->FloatCurves[2].UpdateOrAddKey(TimeSaved, LocationVector.Z, false, TimeStep / 2.f);
		}
	}
}

void UTMComponent_PhysicsBasic::RecordRotationCurve()
{
	if (SavedPhysicComponent != nullptr && bHandleRotation)
	{
		RotationRotator = SavedPhysicComponent->GetComponentRotation();
		RotationVector = FVector(RotationRotator.Pitch, RotationRotator.Yaw, RotationRotator.Roll);

		if (IsValid(RotationCurve))
		{
			RotationCurve->FloatCurves[0].UpdateOrAddKey(TimeSaved, RotationVector.X, false, TimeStep / 2.f);
			RotationCurve->FloatCurves[1].UpdateOrAddKey(TimeSaved, RotationVector.Y, false, TimeStep / 2.f);
			RotationCurve->FloatCurves[2].UpdateOrAddKey(TimeSaved, RotationVector.Z, false, TimeStep / 2.f);
		}
	}
}

void UTMComponent_PhysicsBasic::RecordScaleCurve()
{
	if (GetOwner() != nullptr && bHandleScale)
	{
		ScaleVector = GetOwner()->GetActorScale3D();

		if (IsValid(ScaleCurve))
		{
			ScaleCurve->FloatCurves[0].UpdateOrAddKey(TimeSaved, ScaleVector.X, false, TimeStep / 2.f);
			ScaleCurve->FloatCurves[1].UpdateOrAddKey(TimeSaved, ScaleVector.Y, false, TimeStep / 2.f);
			ScaleCurve->FloatCurves[2].UpdateOrAddKey(TimeSaved, ScaleVector.Z, false, TimeStep / 2.f);
		}
	}
}

void UTMComponent_PhysicsBasic::RecordVelocityCurve()
{
	if (SavedPhysicComponent != nullptr && bHandleVelocity)
	{
		VelocityVector = SavedPhysicComponent->GetPhysicsLinearVelocity();

		if (IsValid(VelocityCurve))
		{
			VelocityCurve->FloatCurves[0].UpdateOrAddKey(TimeSaved, VelocityVector.X, false, TimeStep / 2.f);
			VelocityCurve->FloatCurves[1].UpdateOrAddKey(TimeSaved, VelocityVector.Y, false, TimeStep / 2.f);
			VelocityCurve->FloatCurves[2].UpdateOrAddKey(TimeSaved, VelocityVector.Z, false, TimeStep / 2.f);
		}
	}
}

void UTMComponent_PhysicsBasic::RecordAngularVelocityCurve()
{
	if (SavedPhysicComponent != nullptr && bHandleAngularVelocity)
	{
		AngularVelocityVector = SavedPhysicComponent->GetPhysicsAngularVelocityInRadians();

		if (IsValid(AngularVelocityCurve))
		{
			AngularVelocityCurve->FloatCurves[0].UpdateOrAddKey(TimeSaved, AngularVelocityVector.X, false, TimeStep / 2.f);
			AngularVelocityCurve->FloatCurves[1].UpdateOrAddKey(TimeSaved, AngularVelocityVector.Y, false, TimeStep / 2.f);
			AngularVelocityCurve->FloatCurves[2].UpdateOrAddKey(TimeSaved, AngularVelocityVector.Z, false, TimeStep / 2.f);
		}
	}
}

/**-----------------	Replay Curve Part		-----------------*/

void UTMComponent_PhysicsBasic::ReplayCurves()
{
	Super::ReplayCurves();

	ReplayLocationCurve();
	ReplayRotationCurve();
	ReplayScaleCurve();
	ReplayVelocityCurve();
	ReplayAngularVelocityCurve();
}

void UTMComponent_PhysicsBasic::ReplayLocationCurve()
{
	if (IsValid(SavedPhysicComponent) && bHandleLocation)
	{
		if (IsValid(LocationCurve))
		{
			TimeScoped = TimeSaved - ((bIncrementByStep) ? TimeElapsed : 0.f); // Real time
			LocationVector = LocationCurve->GetVectorValue(TimeScoped);

			TimeScoped = TimeSaved - ((!bIncrementByStep) ? TimeElapsed : 0.f); // Time of the current step made to scope
			LocationVectorA = LocationCurve->GetVectorValue(TimeScoped);

			TimeScoped = TimeSaved - ((!bIncrementByStep) ? TimeElapsed : 0.f) - TimeStep; // Time of the next step made to scope
			LocationVectorB = LocationCurve->GetVectorValue(TimeScoped);

			LocationVector = FMath::Lerp(LocationVectorA, LocationVectorB, 1 - (TimeElapsed / TimeStep));
			SavedPhysicComponent->SetWorldLocation(LocationVector, false, nullptr,ETeleportType::TeleportPhysics);
		}
	}
}

void UTMComponent_PhysicsBasic::ReplayRotationCurve()
{
	if (SavedPhysicComponent != nullptr && bHandleRotation)
	{

		if (IsValid(RotationCurve))
		{
			TimeScoped = TimeSaved - ((bIncrementByStep) ? TimeElapsed : 0.f); // Real time
			RotationVector = RotationCurve->GetVectorValue(TimeScoped);

			TimeScoped = TimeSaved - ((!bIncrementByStep) ? TimeElapsed : 0.f); // Time of the current step made to scope
			RotationVectorA = RotationCurve->GetVectorValue(TimeScoped);

			TimeScoped = TimeSaved - ((!bIncrementByStep) ? TimeElapsed : 0.f) - TimeStep; // Time of the next step made to scope 
			RotationVectorB = RotationCurve->GetVectorValue(TimeScoped);
		
			RotationRotatorA = FRotator(RotationVectorA.X, RotationVectorA.Y, RotationVectorA.Z);
			RotationRotatorB = FRotator(RotationVectorB.X, RotationVectorB.Y, RotationVectorB.Z);
			RotationRotator = FRotator(FQuat::Slerp(RotationRotatorA.Quaternion(), RotationRotatorB.Quaternion(), 1 -(TimeElapsed / TimeStep))); //FMath::LerpRange(RotationRotatorA, RotationRotatorB, TimeElapsed / TimeStep);
			SavedPhysicComponent->SetWorldRotation(RotationRotator, false, nullptr, ETeleportType::TeleportPhysics);
		}



	}
}

void UTMComponent_PhysicsBasic::ReplayScaleCurve()
{
	if (GetOwner() != nullptr && bHandleScale)
	{
		if (IsValid(ScaleCurve))
		{
			TimeScoped = TimeSaved - ((bIncrementByStep) ? TimeElapsed : 0.f); // Real time
			ScaleVector = ScaleCurve->GetVectorValue(TimeScoped);

			GetOwner()->SetActorScale3D(ScaleVector);
		}
	}
}

void UTMComponent_PhysicsBasic::ReplayVelocityCurve()
{
	if (SavedPhysicComponent != nullptr && bHandleVelocity)
	{
		if (IsValid(VelocityCurve))
		{
			TimeScoped = TimeSaved - ((bIncrementByStep) ? TimeElapsed : 0.f); // Real time
			VelocityVector = VelocityCurve->GetVectorValue(TimeScoped);
	
			//SavedPhysicComponent->SetPhysicsLinearVelocity(VelocityVector);
		}
	}
}

void UTMComponent_PhysicsBasic::ReplayAngularVelocityCurve()
{
	if (SavedPhysicComponent != nullptr && bHandleAngularVelocity)
	{
		if (IsValid(AngularVelocityCurve))
		{
			TimeScoped = TimeSaved - ((bIncrementByStep) ? TimeElapsed : 0.f); // Real time
			AngularVelocityVector = AngularVelocityCurve->GetVectorValue(TimeScoped);

			//SavedPhysicComponent->SetPhysicsAngularVelocityInRadians(AngularVelocityVector);
		}

	}
}
