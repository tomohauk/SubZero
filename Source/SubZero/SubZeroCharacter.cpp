//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.

#include "SubZero.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "Item.h"
#include "Inventory/Inventory.h"
#include "Inventory/InventoryUI.h"
#include "NPC.h"
#include "DrawDebugHelpers.h"
#include "Engine.h"
#include "UI/DialogueWidget.h"
#include "WidgetBlueprintLibrary.h"
#include "SubZeroCharacter.h"
#include "Public/QuestSystem/QuestBuilder.h"

void ASubZeroCharacter::BeginPlay()
{
	Super::BeginPlay();

	UInventory * tmpInv = NewObject<UInventory>();

	if (IsValid(tmpInv))
	{
		inventory = tmpInv;
	}
	else
	{
		PRINTSTRING("tmpInv invalid!");
	}

	UQuestBuilder * qb = NewObject<UQuestBuilder>();
	qb->InitiateQuestBuilder();
	qb->CreateQuests();
}

//////////////////////////////////////////////////////////////////////////
// ASubZeroCharacter

ASubZeroCharacter::ASubZeroCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
	EnableInput(Cast<APlayerController>(this->GetController()));

	//
	bIsShowingInventory = false;
}

//////////////////////////////////////////////////////////////////////////
// Input

void ASubZeroCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//World Interaction
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ASubZeroCharacter::Interact);
	PlayerInputComponent->BindAction("Close", IE_Pressed, this, &ASubZeroCharacter::Close);
	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &ASubZeroCharacter::ToggleInventory);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASubZeroCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASubZeroCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ASubZeroCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ASubZeroCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ASubZeroCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ASubZeroCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ASubZeroCharacter::OnResetVR);
}

void ASubZeroCharacter::Tick(float DeltaSeconds)
{
	//Close dialogue widget after the player is 400 units away from target
	if (isInDialogue && IsValid(targetDialogueActor))
	{
		FVector npcLocation = targetDialogueActor->GetActorLocation();
		FVector playerLocation = this->GetActorLocation();
		float lengthFromTarget = UKismetMathLibrary::VSize(npcLocation - playerLocation);

		if (lengthFromTarget >= 560)
		{
			Close(dialogueWidget);
		}
	}
}

void ASubZeroCharacter::Interact()
{

	FHitResult hitResults(ForceInit);

	FVector StartPoint;
	FRotator EyeRotation;
	GetActorEyesViewPoint(StartPoint, EyeRotation);
	StartPoint += FVector(0.0f, 0.0f, 30.0f);
	
	FVector EndPoint = StartPoint + ( FollowCamera->GetForwardVector() * 200 );
	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("Trace")), true, this);
	GetWorld()->LineTraceSingleByChannel(hitResults, StartPoint, EndPoint, ECC_Pawn,RV_TraceParams);
	
	if (hitResults.GetActor())
	{
		//Interaction with an NPC
		if (ANPC * npc = Cast<ANPC>(hitResults.GetActor()))
		{
			if (isInDialogue)
				return;

			if (wDialogueWidget)
			{
				dialogueWidget = CreateWidget<UDialogueWidget>(Cast<APlayerController>(this->GetController()), wDialogueWidget);

				if (dialogueWidget && (!dialogueWidget->IsVisible() && !dialogueWidget->IsInViewport()))
				{
					this->isInDialogue = true;
					this->targetDialogueActor = npc;

					dialogueWidget->debugNPCName = npc->GetName();
					dialogueWidget->debugTopicCount = npc->dialogueDB->GetTopics().Num();
					dialogueWidget->targetNPC = npc;

					dialogueWidget->AddToViewport();

					UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(Cast<APlayerController>(this->GetController()), dialogueWidget, EMouseLockMode::DoNotLock, false);
					Cast<APlayerController>(this->GetController())->bShowMouseCursor = true;

					npc->Interact(this);
				}
			}
		}
		//Interaction with an Item in the world
		else if (AItem * item = Cast<AItem>(hitResults.GetActor()))
		{
			PRINTSTRING(FString::FromInt(item->GetUniqueID()));
			inventory->PickupItem(item);
		}
		//Not sure what it is, so return.
		else
		{
			GEngine->AddOnScreenDebugMessage(0, 2.0f, FColor::Black, "Could Not Cast!");
		}
	}
}

void ASubZeroCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ASubZeroCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	// jump, but only on the first touch
	if (FingerIndex == ETouchIndex::Touch1)
	{
		Jump();
	}
}

void ASubZeroCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (FingerIndex == ETouchIndex::Touch1)
	{
		StopJumping();
	}
}

void ASubZeroCharacter::Close( UUserWidget * inWidget)
{
	//Close Dialogue Menu
	if ( IsValid(inWidget) && isInDialogue && inWidget->IsInViewport() && inWidget->IsVisible())
	{
		inWidget->RemoveFromParent();

		if (Cast<UDialogueWidget>(inWidget))
		{
			isInDialogue = false;
			targetDialogueActor = nullptr;
			UWidgetBlueprintLibrary::SetInputMode_GameOnly(Cast<APlayerController>(this->GetController()));
			Cast<APlayerController>(this->GetController())->bShowMouseCursor = false;
		}

	}
}

void ASubZeroCharacter::Close()
{
	if (isInDialogue)
	{
		Close(dialogueWidget);
	}
}

void ASubZeroCharacter::CloseDialogue()
{
	Close();
}

void ASubZeroCharacter::ToggleInventory()
{
	if (bIsShowingInventory)//Hide Inventory
	{
		inventoryWidget->RemoveFromViewport();
		
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(Cast<APlayerController>(this->GetController()));

		bIsShowingInventory = false;
		inventoryWidget->bIsInventoryOpen = false;	
		Cast<APlayerController>(this->GetController())->bShowMouseCursor = false;
	}
	else//Show Inventory
	{
		inventoryWidget = CreateWidget<UInventoryUI>(Cast<APlayerController>(this->GetController()), wInventoryWidget);

		if (inventoryWidget)
		{
//			UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(Cast<APlayerController>(this->GetController()), inventoryWidget);
			inventoryWidget->AddToViewport();

			bIsShowingInventory = true;
			inventoryWidget->bIsInventoryOpen = true;
			Cast<APlayerController>(this->GetController())->bShowMouseCursor = true;
		}
	}

	return;
}

void ASubZeroCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ASubZeroCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ASubZeroCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ASubZeroCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
