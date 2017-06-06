// Copyright Spiral House Ltd 2017

#include "OpenDoor.h"
#include "Engine.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay(); 
	Owner = GetOwner();
	if( Owner )
	{
		OrigYaw = Owner->GetActorRotation().Yaw;
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetTotalMassOfActorsOnPlate() >= 30.0f)
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	if( GetWorld()->GetTimeSeconds() > LastDoorOpenTime + DoorCloseDelay)
	{
		CloseDoor();
	}
}

void UOpenDoor::OpenDoor( void )
{
	Owner->SetActorRotation(FRotator(0.0f, OrigYaw + OpenAngle, 0.0f));
}

void UOpenDoor::CloseDoor(void)
{
	Owner->SetActorRotation(FRotator(0.0f, OrigYaw, 0.0f));
}

float UOpenDoor::GetTotalMassOfActorsOnPlate(void)
{
	float weight = 0.0f;
	if (PresurePlate)
	{
		TArray<AActor*> ActorList;
		PresurePlate->GetOverlappingActors(ActorList);

		for (auto *Actor : ActorList)
		{
			//UE_LOG(LogTemp, Warning, TEXT("On Plate %s"), *(Actor->GetName()));
			weight += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		}
	}
	return(weight);
}
