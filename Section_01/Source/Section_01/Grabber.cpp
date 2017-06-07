// Copyright Spiral House Ltd 2017

#include "Grabber.h"
#include "Engine.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
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

	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
		PhysicsHandle->SetTargetLocation(GetAttachedPos());
}

void UGrabber::Grab()
{
	if (!PhysicsHandle)
		return;
	FHitResult Result = GetFirstPhysicsBodyInReach();
	AActor *ActorHit = Result.GetActor();
	if (ActorHit)
	{
		auto ComponentToGrab = Result.GetComponent();
		PhysicsHandle->GrabComponentAtLocation( ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation());
	}
}

void UGrabber::Release()
{
	if (!PhysicsHandle)
		return;
	auto GrabbedComponent = PhysicsHandle->GetGrabbedComponent();
	if (GrabbedComponent)
		PhysicsHandle->ReleaseComponent();
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach(void)
{
	/// see what we hit
	FHitResult Result;
	FCollisionQueryParams TraceQParams(FName(TEXT("")), false, GetOwner());
	FCollisionObjectQueryParams ObjectQParams(ECollisionChannel::ECC_PhysicsBody);

	GetWorld()->LineTraceSingleByObjectType(Result, GetPlayerPos(), GetAttachedPos(), ObjectQParams, TraceQParams);
	return(Result);
}

FVector UGrabber::GetAttachedPos(void)
{
	FVector Pos;
	FRotator Rot;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Pos, Rot);
	FVector EndPos = Pos + Rot.Vector() * Reach;
	return(EndPos);
}

FVector UGrabber::GetPlayerPos(void)
{
	FVector Pos;
	FRotator Rot;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Pos, Rot);
	return(Pos);
}
