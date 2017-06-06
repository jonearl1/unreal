// Copyright Spiral House Ltd 2017

#pragma once

#include "Engine.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SECTION_01_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();
	// Called when the game starts
	virtual void BeginPlay() override;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	//RayCast and grab what's in reach
	void Grab(void);
	// release the grabbed object
	void Release(void);

	void FindPhysicsHandleComponent(void);

	void SetupInputComponent(void);
	FHitResult GetFirstPhysicsBodyInReach(void);
	FVector GetAttachedPos(void);
	FVector GetPlayerPos(void);

	float Reach = 100.0f;
	UPhysicsHandleComponent *PhysicsHandle = nullptr;
	UInputComponent *PawnInput = nullptr;
};
