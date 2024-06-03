// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CProperty.generated.h"

UCLASS()
class U04_THIRDPERSONCPP_API ACProperty : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACProperty();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere)
	int NumA;

	UPROPERTY(EditInstanceOnly)
	int NumB;

	UPROPERTY(EditDefaultsOnly)
	int NumC;

	UPROPERTY(VisibleAnywhere)
	float RealA;

	UPROPERTY(VisibleInstanceOnly)
	float RealB;

	UPROPERTY(VisibleDefaultsOnly)
	float RealC;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float RealD = 3.14f;

};
