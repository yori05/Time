// Property of Florian Hulin, shouldn't be used without my consent.

#include "GameMode/GameMode_Basic.h"

#include "UObject/ConstructorHelpers.h"
#include "Character/PlayerCharacter_Basic.h"
#include "PlayerController/PlayerController_Basic.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "Kismet/KismetSystemLibrary.h"

/**-----------------	Constructor Part		-----------------*/

AGameMode_Basic::AGameMode_Basic(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	bIsInPause = false;

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprint/Character/PlayerCharacter/BP_PlayerCharacter_Basic"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	else
	{
		DefaultPawnClass = APlayerCharacter_Basic::StaticClass();
	}

	// set default pawn class to our Blueprinted player controller
	static ConstructorHelpers::FClassFinder<AController> PlayerControllerBPClass(TEXT("/Game/Blueprint/Controller/PlayerController/BP_PlayerController_Basic"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
	else
	{
		PlayerControllerClass = APlayerController_Basic::StaticClass();
	}

}

/**-----------------	Request Part		-----------------*/

bool AGameMode_Basic::RequestPauseGame()
{
	if (!bIsInPause)
	{
		LaunchPauseGame();

		return true;
	}

	return false;
}

bool AGameMode_Basic::RequestResumeGame()
{
	if (bIsInPause)
	{
		LaunchResumeGame();

		return true;
	}

	return false;
}

bool AGameMode_Basic::RequestQuitGame()
{
	LaunchQuitGame();

	return true;
}

bool AGameMode_Basic::RequestMainMenuGame()
{
	//LaunchMainMenu();

	return true;
}

/**-----------------	Chage Part		-----------------*/

/**======	Pause Part		======*/

void AGameMode_Basic::LaunchPauseGame()
{
	PauseGame();
	ReceivePauseGame();
	OnPauseGame.Broadcast();
}

void AGameMode_Basic::PauseGame()
{
	if (UWorld* World = GetWorld())
	{
		if (APlayerController* PC = World->GetFirstPlayerController<APlayerController>())
		{
			PC->SetPause(true);
			bIsInPause = true;
		}
	}
}

/**======	Resume Part		======*/

void AGameMode_Basic::LaunchResumeGame()
{
	ResumeGame();
	ReceiveResumeGame();
	OnResumeGame.Broadcast();
}

void AGameMode_Basic::ResumeGame()
{ 
	if (UWorld* World = GetWorld())
	{
		if (APlayerController* PC = World->GetFirstPlayerController<APlayerController>())
		{
			PC->SetPause(false);
			bIsInPause = false;
		}
	}
}

/**======	Quit Part		======*/

void AGameMode_Basic::LaunchQuitGame() 
{
	QuitGame();
	ReceiveQuitGame();
	OnQuitGame.Broadcast();

	// Request the game to be exit 
	//FGenericPlatformMisc::RequestExit(false);

	if (UWorld* World = GetWorld())
	{
		if (APlayerController* PC = World->GetFirstPlayerController<APlayerController>())
		{
			UKismetSystemLibrary::QuitGame(World, PC,EQuitPreference::Quit,false);
		}
	}

}

void AGameMode_Basic::QuitGame()
{
	// The game is'nt exit there to let the action be take by the child or other callback in case we want to save or something
}
