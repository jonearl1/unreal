// Copyright Spiral House Ltd 2017

#pragma once

#include "CoreMinimal.h"

#include "Engine.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenRequest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SECTION_01_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor(void);
	void CloseDoor(void);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
private:

	float GetTotalMassOfActorsOnPlate(void);

	UPROPERTY(EditAnywhere)
	float	OpenAngle = -90.0f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume *PresurePlate = NULL;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 1.0f;

	UPROPERTY(BlueprintAssignable)
	FOnOpenRequest OnOpenRequest;

	//UPROPERTY( EditAnywhere )
	float LastDoorOpenTime = 0.0f;
	AActor *Owner = NULL;
	float OrigYaw = 0.0f;
};
