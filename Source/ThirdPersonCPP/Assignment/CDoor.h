// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBoxBase.h"
#include "CDoor.generated.h"

class UStaticMeshComponent;
class UMaterialInstanceDynamic;
class ACPlayer;

UCLASS()
class THIRDPERSONCPP_API ACDoor : public ACBoxBase
{
	GENERATED_BODY()
public:
	ACDoor();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
	virtual void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		UStaticMeshComponent* DoorFrame;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		UStaticMeshComponent* Door;

	UPROPERTY(EditInstanceOnly, Category = "MaterialParams")
		FLinearColor Emissive;
public:
	void Open(TArray<bool> InKeys);

public:
	UPROPERTY(EditInstanceOnly, Category = "MaterialParams")
	FName Key;

private:
	bool bIsOpened;
	UMaterialInstanceDynamic* FrameDynamicMaterial;
	UMaterialInstanceDynamic* DoorDynamicMaterial;
	ACPlayer* player;
	UCurveFloat* Curve;
};
