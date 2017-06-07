// Copyright Spiral House Ltd 2017

#include "OpenDoor.h"
#include "Engine.h"

// Sets default values for this component's properties
UDoorEvent::UDoorEvent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UDoorEvent::BeginPlay()
{
	Super::BeginPlay(); 
	Owner = GetOwner();
	if( Owner )
		OrigYaw = Owner->GetActorRotation().Yaw;

	if (!PresurePlate)
		UE_LOG(LogTemp, Error, TEXT("PresurePlate not found on Actor %s"), *(Owner->GetName()));

}


// Called every frame
void UDoorEvent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetTotalMassOfActorsOnPlate() >= TriggerMass)
	{
		OnOpen.Broadcast();
	}
	else
	{
		OnClose.Broadcast();
	}
}

float UDoorEvent::GetTotalMassOfActorsOnPlate(void)
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
