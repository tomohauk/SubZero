//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "SubZeroCharacter.generated.h"

UCLASS(config=Game)
class ASubZeroCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	ASubZeroCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Dialogue", DisplayName = "In Dialogue")
	bool isInDialogue = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Dialogue", DisplayName = "DialogueTarget")
	class ANPC * targetDialogueActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue", DisplayName = "DialogueWidget")
	TSubclassOf<class UUserWidget> wDialogueWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue", DisplayName = "Dialogue Widget Actual")
	class UDialogueWidget * dialogueWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", DisplayName = "Inventory Widget")
	TSubclassOf<UUserWidget> wInventoryWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", DisplayName = "Inventory Widget Actual")
	class UInventoryUI * inventoryWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", DisplayName = "Inventory")
	class UInventory * inventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Dialogue", DisplayName = "Dialogue Widget Showing")
	bool isShowingDialogue = false;

	//BlueprintCallable close dialogue
	UFUNCTION(BlueprintCallable, DisplayName = "Close Dialogue", Category = "Dialogue")
	void CloseDialogue();
 
	//Show/Hide inventory
	UFUNCTION(BlueprintCallable, DisplayName = "Show/Hide Inventory", Category = "Inventory")
	void ToggleInventory();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", DisplayName = "Is Showing Inventory")
	bool bIsShowingInventory;

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	/** Bind Input Action event for player closing a widget.*/
	void Close();
	/** Closes inWidget widgets */
	void Close(UUserWidget * inWidget);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	virtual void Tick(float DeltaSeconds);
public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	void Interact();
};

