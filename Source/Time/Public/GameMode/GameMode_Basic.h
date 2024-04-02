// Property of Florian Hulin, shouldn't be used without my consent.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameMode_Basic.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGMBasicEventSignature);

/**
 *	Default Game Mode
 *  
 *  Should be used as a base for other game mode, for a fast and easy use define basic class such as :
 *  - PlayerController_Basic
 *  - PlayerCharacter_Basic
 * 
 * Have the possibility to quit, pause and resume the game
 */
UCLASS()
class TIME_API AGameMode_Basic : public AGameModeBase
{
	GENERATED_BODY()
	
	/**-----------------	Variable Part		-----------------*/
protected:

	//Temp var to set if the game is pause or no
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pause", meta = (AllowPrivateAccess = "true"))
	bool bIsInPause = false;

	/**-----------------	Callback Part		-----------------*/
public:

	//Called when the game is requested to be paused
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FGMBasicEventSignature OnPauseGame;

	//Called when the game is requested to be resume
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FGMBasicEventSignature OnResumeGame;

	//Called when the game is requested to be quit
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FGMBasicEventSignature OnQuitGame;

	/**-----------------	Constructor Part		-----------------*/
public :

	// Sets default values for this game mode's properties
	AGameMode_Basic(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/**-----------------	Request Part		-----------------*/
public :

	/**
	*  Request the game mode to pause the game
	*  
	*  Will return true in case the game is paused or can be paused or can launch it on the next tick
	*/
	UFUNCTION(BlueprintCallable)
	virtual bool RequestPauseGame();

	/**
	*  Request the game mode to resume the game
	*
	*  Will return true in case the game is resume or can be resume or can launch it on the next tick
	*/
	UFUNCTION(BlueprintCallable)
	virtual bool RequestResumeGame();

	/**
	*  Request the game mode to quit the game
	*
	*  Will return true in case the game is quit or can be resume or can launch it on the next tick
	*/
	UFUNCTION(BlueprintCallable)
	virtual bool RequestQuitGame();

	/** CURRENTLY UNFUNCTIONNAL
	*  Request the game mode to launch the main menu of the game
	*
	*  Will return true in case the game is launching the main menu or can launch it on the next tick
	*/
	UFUNCTION(BlueprintCallable)
	virtual bool RequestMainMenuGame();

	/**-----------------	Chage Part		-----------------*/
	/**======	Pause Part		======*/
protected :

	/**
	*  Called by Request PauseGame
	* 
	*  Will pause the game calling action to so in this order :
	*  -> PauseGame : Action to do in c++
	*  -> ReceivePauseGame : Event implementable in Blueprint
	*  -> @OnPauseGame : Callback called when the game is paused
	* 
	*  It's possible to override this function but in case you want to add more action done by the GameMode you should check the PauseGame function and / or event
	*/
	UFUNCTION(BlueprintCallable)
	virtual void LaunchPauseGame();

	/**
	*  Pause game action need to do by the GameMode
	*  Use C++
	*  
	*  In case you want to implement action does by the game when the game is pause you need to override this function
	*/
	virtual void PauseGame();

	/**
	*  Pause game action need to do by the GameMode
	*  Use Blueprint
	*  
	*  In case you want to implement action done by the GameMode when the game is pause you need to implement this event
	*/
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "PauseGame"))
	void ReceivePauseGame();

	/**======	Resume Part		======*/
protected:

	/**
	*  Called by Request ResumeGame
	*
	*  Will Resume the game calling action to so in this order :
	*  -> ResumeGame : Action to do in c++
	*  -> ReceiveResumeGame : Event implementable in Blueprint
	*  -> @OnResumeGame : Callback called when the game is Resumed
	*
	*  It's possible to override this function but in case you want to add more action done by the GameMode you should check the ResumeGame function and / or event
	*/
	UFUNCTION(BlueprintCallable)
	virtual void LaunchResumeGame();

	/**
	*  Resume game action need to do by the GameMode
	*  Use C++
	*
	*  In case you want to implement action does by the game when the game is Resume you need to override this function
	*/
	virtual void ResumeGame();

	/**
	*  Resume game action need to do by the GameMode
	*  Use Blueprint
	*
	*  In case you want to implement action done by the GameMode when the game is Resume you need to implement this event
	*/
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "ResumeGame"))
	void ReceiveResumeGame();

	/**======	Quit Part		======*/
protected:

	/**
	*  Called by Request QuitGame
	*
	*  Will Quit the game calling action to so in this order :
	*  -> QuitGame : Action to do in c++
	*  -> ReceiveQuitGame : Event implementable in Blueprint
	*  -> @OnQuitGame : Callback called when the game is Quit
	*  -> Will stop the game after have called all these function
	*
	*  It's possible to override this function but in case you want to add more action done by the GameMode you should check the QuitGame function and / or event
	*/
	UFUNCTION(BlueprintCallable)
	virtual void LaunchQuitGame();

	/**
	*  Quit game action need to do by the GameMode
	*  Use C++
	*
	*  In case you want to implement action does by the game when the game is Quit you need to override this function
	*/
	virtual void QuitGame();

	/**
	*  Quit game action need to do by the GameMode
	*  Use Blueprint
	*
	*  In case you want to implement action done by the GameMode when the game is Quit you need to implement this event
	*/
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "QuitGame"))
	void ReceiveQuitGame();

};
