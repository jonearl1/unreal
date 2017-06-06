// Copyright Spiral House Ltd 2017

#include "Grabber.h"
#include "Engine.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty"));
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get player viewpoint this tick
	FVector Pos;
	FRotator Rot;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Pos, Rot);

	//UE_LOG(LogTemp, Warning, TEXT("PlayerPos %s, PlayerRot %s"), *Pos.ToString(), *Rot.ToString());
	// Ray - cast out to reach distance

	float Reach = 10.0f;
	FVector EndPos = Pos + Rot.Vector() * Reach;

	// see what we hit

}

