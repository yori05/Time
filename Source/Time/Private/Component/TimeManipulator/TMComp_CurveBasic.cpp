// Property of Florian Hulin, shouldn't be used without my consent.


#include "Component/TimeManipulator/TMComp_CurveBasic.h"


/**-----------------	Constructor Part		-----------------*/

UTMComp_CurveBasic::UTMComp_CurveBasic()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

}

/**-----------------	Inherit Function Part		-----------------*/

void UTMComp_CurveBasic::BeginPlay()
{
	Super::BeginPlay();

	// ....

	CreateCurves();
}

// Called every frame
void UTMComp_CurveBasic::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

}

// Called when the component is destroyed
void UTMComp_CurveBasic::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// ...

	DestroyCurves();
}

/**-----------------	Curve Part		-----------------*/

/**======	Creation / Destruction Part		======*/

void UTMComp_CurveBasic::CreateCurves()
{

}

void UTMComp_CurveBasic::DestroyCurves()
{

}


/**======	Set / Reset Part		======*/

void UTMComp_CurveBasic::SetCurves()
{

}

void UTMComp_CurveBasic::ResetCurves()
{

}


/**======	Record / Replay Part		======*/

void UTMComp_CurveBasic::RecordCurves()
{

}

void UTMComp_CurveBasic::ReplayCurves()
{

}

/**-----------------	Base Time Manipulator Function Part		-----------------*/
/**======	Step Action Part		======*/

void UTMComp_CurveBasic::StepMade()
{
	Super::StepMade();

	if (TMState_Current == ETimeManipulatorState::TMS_Forward)
	{
		RecordCurves();
	}
}

/**======	Perform State Part		======*/

void UTMComp_CurveBasic::TickReplayState(float _DeltaTime)
{
	Super::TickReplayState(_DeltaTime);

	ReplayCurves();
}
