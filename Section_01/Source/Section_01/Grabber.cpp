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
	FindPhysicsHandleComponent();
	SetupInputComponent();
}

void UGrabber::SetupInputComponent(void)
{
	PawnInput = GetOwner()->FindComponentByClass<UInputComponent>();
	if (PawnInput)
	{
		PawnInput->BindAction(TEXT("Grab"), IE_Pressed, this, &UGrabber::Grab);
		PawnInput->BindAction(TEXT("Grab"), IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Pawn Input not found on Actor %s"), *(GetOwner()->GetName()));
	}
}
///Look for physics handle
void UGrabber::FindPhysicsHandleComponent(void)
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
		UE_LOG(LogTemp, Error, TEXT("Physics Handle not found on Actor %s"), *(GetOwner()->GetName()));
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandle->GetGrabbedComponent())
	{
		FVector Pos;
		FRotator Rot;

		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Pos, Rot);

		FVector EndPos = Pos + Rot.Vector() * Reach;

		PhysicsHandle->SetTargetLocation(EndPos);
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"));
	FHitResult Result = GetFirstPhysicsBodyInReach();
	AActor *ActorHit = Result.GetActor();
	if (ActorHit)
	{
		auto ComponentToGrab = Result.GetComponent();
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *(ActorHit->GetName()));
		PhysicsHandle->GrabComponentAtLocation( ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation());
	}

}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab released")); 
	
	auto GrabbedComponent = PhysicsHandle->GetGrabbedComponent();
	if (GrabbedComponent)
	{
		PhysicsHandle->ReleaseComponent();
	}

}

FHitResult UGrabber::GetFirstPhysicsBodyInReach(void)
{
	FVector Pos;
	FRotator Rot;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Pos, Rot);

	FVector EndPos = Pos + Rot.Vector() * Reach;

	/// see what we hit
	FHitResult Result;
	FCollisionQueryParams TraceQParams(FName(TEXT("")), false, GetOwner());
	FCollisionObjectQueryParams ObjectQParams(ECollisionChannel::ECC_PhysicsBody);

	if (GetWorld()->LineTraceSingleByObjectType(Result, Pos, EndPos, ObjectQParams, TraceQParams))
	{
	}
	return(Result);
}