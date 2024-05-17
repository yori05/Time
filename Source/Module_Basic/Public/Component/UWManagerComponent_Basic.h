// Property of Florian Hulin, shouldn't be used without my consent.

#pragma once

/**-----------------	Include		-----------------*/

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enum/ManagerAuthority.h"

#include "UWManagerComponent_Basic.generated.h"

/**-----------------	Exterior class declaration		-----------------*/

class UUserWidget;
class APlayerController;
class AGameModeBase;

/**-----------------	Helper Struct declaration		-----------------*/

/**
*  User Widget Manager Helper
* 
* A struct to save data for the widget hold by the UWManagerComponent
*/
USTRUCT(BlueprintType)
struct FUWManagerHelper
{
	GENERATED_USTRUCT_BODY()

	/**-----------------	Variable Part		-----------------*/
public:

	/**
	*  Instance of the userwidget
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UUserWidget> Instance;

	/**
	* Class of the userwidget to instance
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> Class;

	/**
	* Name of widget same as the key for the Map to store it
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Name", meta = (AllowPrivateAccess = "true"))
	FString Name;

	/**
	* Should this widget be instanciate on the begin play of this component
	* True by default
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting", meta = (AllowPrivateAccess = "true"))
	bool bInstanciateOnBP = true;

	/**
	* Should this widget be add to viewport after have been instantiate on the begin play of this component
	* True by default
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting", meta = (AllowPrivateAccess = "true"))
	bool bAddToVPOnBP = true;

	/**
	* Should this widget be remove from the parent (to hide it) after have been add to viewport on the begin play of this component
	* True by default
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting", meta = (AllowPrivateAccess = "true"))
	bool bRemoveFromParentOnBP = true;

	/**
	* Is This Widget on the Viewport
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Setting", meta = (AllowPrivateAccess = "true"))
	bool bIsOnVP = false;

};

/**-----------------	Class declaration		-----------------*/

/**
*  UserWidget Manager Component Basic
* 
* A helper component whome will instanciate UW when we want and store them in a Map
* Use UWManagerHelper to save the data of the widget manage by this component
*/
UCLASS( ClassGroup=(Basic), meta=(BlueprintSpawnableComponent))
class MODULE_BASIC_API UUWManagerComponent_Basic : public UActorComponent
{
	GENERATED_BODY()

	/**-----------------	Variable Part		-----------------*/
protected:

	/**
	* Map of every UW helper of this component 
	* Use the name of the helper as the key to this map
	* *Both value should be the same ex : Key = "UIMenu" Value.Name = "UIMenu"
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TMap<FString, FUWManagerHelper> UWInstances;

	/**
	* On @BeginPlay Will look if this component is used on a PlayerController
	* In other case will search the player controller to use to spawn userwidget on it
	* *By default 0 for the main play
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting", meta = (AllowPrivateAccess = "true"))
	int32 IndexOfThePlayer = 0;
	
	/**
	* GameModeBase used by this component to instantiate widget
	* Will first check (in the begin play) if the Actor owner is a GameModeBase and link to him if it's the case
	* *For now saved as a AGameModeBase maybe will be saved as a AGameMode_Basic later
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Setting", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AGameModeBase> GM;

	/**
	* PlayerController used by this component to instantiate widget
	* Will first check (in the begin play) if the Actor owner is a PlayerController and link to him if it's the case
	* *For now saved as a APlayerController maybe will be saved as a APlayerController_Basic later
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Setting", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<APlayerController> PC;

	/***************************************------------ For now this part is muted will see if usefull or no (To delete or unmute) --------------****************************************************/
	///**
	//* Should this widget be instanciate on the begin play of this component
	//*/
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting", meta = (AllowPrivateAccess = "true"))
	//bool bInstanciateOnBP;
	//
	///**
	//* ManagerAuthority :
	//* Can this mananger apply his [BeginPlayRules] on every FUWManagerHelper or should he apply the FUWManagerHelper's one
	//* 
	//*/
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Management", meta = (AllowPrivateAccess = "true"))
	//EManagerAuthority ManagerAuthority = EManagerAuthority::MANAGERAUTHORITY_Listen;
	//
	//
	///**
	//* Should this widget be instanciate on the begin play of this component
	//*/
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeginPlayRules", meta = (AllowPrivateAccess = "true"))
	//bool bInstanciateOnBP;
	//
	///**
	//* Should this widget be add to viewport after have been instantiate on the begin play of this component
	//*/
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeginPlayRules", meta = (AllowPrivateAccess = "true"))
	//bool bAddToVPOnBP;
	//
	///**
	//* Should this widget be remove from the parent (to hide it) after have been add to viewport on the begin play of this component
	//*/
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeginPlayRules", meta = (AllowPrivateAccess = "true"))
	//bool bRemoveFromParentOnBP;


	/**-----------------	Constructor Part		-----------------*/
public:	

	// Sets default values for this component's properties
	UUWManagerComponent_Basic();

	/**-----------------	Component Function Part		-----------------*/
protected:

	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
	/**-----------------	UserWidget Management Part		-----------------*/
protected:


	UFUNCTION(BlueprintCallable)
	void CatchGameMode();

	UFUNCTION(BlueprintCallable)
	void CatchPlayerController();

	/**-----------------	UserWidget Management Part		-----------------*/
protected:

	/**
	* Will instantiate every UW using the helper on begin play (depending of the helper setting)
	*/
	UFUNCTION(BlueprintCallable)
	virtual void InitializeMapInstances();

	UFUNCTION(BlueprintCallable)
	virtual bool InitializeFromHelper(FUWManagerHelper& Helper);

	UFUNCTION(BlueprintCallable)
	virtual bool CreateWidgetFromHelper(FUWManagerHelper& Helper);

	UFUNCTION(BlueprintCallable)
	virtual bool AddUWToViewport(FUWManagerHelper& Helper);

	UFUNCTION(BlueprintCallable)
	virtual bool RemoveUWFromParent(FUWManagerHelper& Helper);

public:

	UFUNCTION(BlueprintCallable)
	virtual bool RequestInstantiateUW(const FString &UWName);

	UFUNCTION(BlueprintCallable)
	virtual bool RequestAddUWToViewport(const FString &UWName);

	UFUNCTION(BlueprintCallable)
	virtual bool RequestRemoveUWFromParent(const FString &UWName);

	UFUNCTION(BlueprintCallable)
	virtual bool RequestInsertNewUW(const FString& UWName, TSubclassOf<UUserWidget> UWClass, bool bInstantiate = true, bool bAddToVP = true, bool bRemoveFromParent = true);

};
