//

#pragma once

#include "GameFramework/Actor.h"
#include "Item.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	IT_Weapon UMETA(DisplayName = "Weapon"),
	IT_Food UMETA(DisplayName = "Food"),
	IT_Misc UMETA(DisplayName = "Misc")
};

UCLASS(Blueprintable)
class SUBZERO_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	class UStaticMeshComponent * StaticMesh;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//Unique ID
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	int32 uniqueID;



	//Items name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FString itemName;

	//Items health <= 0 is destroyed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int itemHealth;

	//The items type	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	EItemType itemType;

	//itemName change to update display name
#if WITH_EDITOR
	void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent);
#endif



};
