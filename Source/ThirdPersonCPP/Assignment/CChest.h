// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBoxBase.h"
#include "CChest.generated.h"

class UStaticMeshComponent;
class UMaterialInstanceDynamic;

UCLASS()
class THIRDPERSONCPP_API ACChest : public ACBoxBase
{
	GENERATED_BODY()

public:
	ACChest();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
	virtual void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
	
public:
	void Open(FName& OutKey);
protected:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components")
	UStaticMeshComponent* Lid;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components")
	UStaticMeshComponent* Bottom;

	UPROPERTY(EditInstanceOnly, Category = "MaterialParams")
	FLinearColor Emissive;

public:
	UPROPERTY(EditInstanceOnly, Category = "MaterialParams")
	FName Key;

private:
	bool bIsOpened;
	UMaterialInstanceDynamic* DynamicMaterial;
};
