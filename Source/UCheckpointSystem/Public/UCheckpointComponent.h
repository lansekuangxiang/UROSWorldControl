// Copyright 2020, Institute for Artificial Intelligence - University of Bremen
// Author: Michael Neumann


#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CheckpointEventBroadcaster.h"
#include "UCheckpointComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UCHECKPOINTSYSTEM_API UCheckpointComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCheckpointComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


        UPROPERTY(BlueprintAssignable, Category = "Checkpoint")
          FSetCheckpointEvent OnSetCheckpointEvent;

        UPROPERTY(BlueprintAssignable, Category = "Checkpoint")
          FGetCheckpointEvent OnGetCheckpointEvent;

};