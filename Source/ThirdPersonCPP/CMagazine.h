// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CMagazine.generated.h"

class UStaticMeshComponent;

UCLASS()
class THIRDPERSONCPP_API ACMagazine : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ACMagazine();

	UStaticMeshComponent* GetMeshComp() { return MeshComp; }


protected:

private:
	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* MeshComp;

};
