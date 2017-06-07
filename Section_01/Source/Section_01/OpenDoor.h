// Copyright Spiral House Ltd 2017

#pragma once

#include "CoreMinimal.h"

#include "Engine.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenRequest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseRequest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SECTION_01_API UDoorEvent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorEvent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
private:

	float GetTotalMassOfActorsOnPlate(void);

	UPROPERTY(EditAnywhere)
	ATriggerVolume *PresurePlate = NULL;

	UPROPERTY(EditAnywhere)
	float TriggerMass = 30.0f;

	UPROPERTY(BlueprintAssignable)
	FOnOpenRequest OnOpen;

	UPROPERTY(BlueprintAssignable)
	FOnCloseRequest OnClose;

	//UPROPERTY( EditAnywhere )
	float LastDoorOpenTime = 0.0f;
	AActor *Owner = NULL;
	float OrigYaw = 0.0f;
};
