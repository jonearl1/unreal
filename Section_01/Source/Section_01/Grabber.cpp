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

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty"));

	///Look for physics handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
		UE_LOG(LogTemp, Error, TEXT("Physics Handle not found on Actor %s"), *(GetOwner()->GetName() ) );

	PawnInput = GetOwner()->FindComponentByClass<UInputComponent>();
	if (PawnInput)
	{
		PawnInput->BindAction(TEXT("Grab"), IE_Pressed, this, &UGrabber::Grab);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Pawn Input not found on Actor %s"), *(GetOwner()->GetName()));
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/// Get player viewpoint this tick
	FVector Pos;
	FRotator Rot;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Pos, Rot);

	/// UE_LOG(LogTemp, Warning, TEXT("PlayerPos %s, PlayerRot %s"), *Pos.ToString(), *Rot.ToString());
	/// Ray - cast out to reach distance

	FVector EndPos = Pos + Rot.Vector() * Reach;
	DrawDebugLine(GetWorld(), Pos, EndPos, FColor(255, 0, 0), false, 0.0f, 0, 10.0f );
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"));
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
		AActor *ActorHit = Result.GetActor();
		if (ActorHit)
		{
			UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *(ActorHit->GetName()));
		}
	}
}

