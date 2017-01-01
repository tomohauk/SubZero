//Copyright 2016-2017 Dark Rising Studios and the Sub Zero Development Community. All Rights Reserved.

#include "SubZero.h"
#include "Item.h"


// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->StaticMesh = LoadObject<UStaticMesh>(NULL, TEXT("/Game/Geometry/Meshes/1M_Cube"), nullptr, LOAD_None, nullptr);
	
	StaticMesh->SetSimulatePhysics(true);
	StaticMesh->WakeRigidBody();

	RootComponent = StaticMesh;

	uniqueID = this->GetUniqueID();
	
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

//	itemName = this->GetActorLabel();

	StaticMesh->WakeRigidBody();
}

// Called every frame
void AItem::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

#if WITH_EDITOR
void AItem::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	UProperty * property = PropertyChangedEvent.Property;
	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	
	if (PropertyName == GET_MEMBER_NAME_CHECKED(AItem, itemName))
	{
		if (UStrProperty * prop = Cast<UStrProperty>(property))
		{
			//FString t = TEXT(*prop->GetPropertyValue(property));

			//PRINTSTRING(t);
			//this->AppendName(t);

		}
	}
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif
