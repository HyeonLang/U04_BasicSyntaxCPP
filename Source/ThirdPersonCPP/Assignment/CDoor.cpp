// Fill out your copyright notice in the Description page of Project Settings.


#include "CDoor.h"
#include "CPlayer.h"
#include "Components/TimeLineComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

ACDoor::ACDoor()
{
	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>("DOORFRAME");
	DoorFrame->SetupAttachment(RootComp);
	ConstructorHelpers::FObjectFinder<UStaticMesh> DoorFrameAsset(TEXT("StaticMesh'/Game/Assignment/Door/Props/SM_DoorFrame.SM_DoorFrame'"));
	if (DoorFrameAsset.Succeeded())
	{
		DoorFrame->SetStaticMesh(DoorFrameAsset.Object);
	}

	Door = CreateDefaultSubobject<UStaticMeshComponent>("DOOR");
	Door->SetupAttachment(RootComp);
	ConstructorHelpers::FObjectFinder<UStaticMesh> DoorAsset(TEXT("StaticMesh'/Game/Assignment/Door/Props/SM_Door.SM_Door'"));
	if (DoorAsset.Succeeded())
	{
		Door->SetStaticMesh(DoorAsset.Object);
	}
	Door->SetRelativeLocation(FVector(0, 45, 0));

	Emissive = FLinearColor(1, 0, 0);
}

void ACDoor::OnConstruction(const FTransform& Transform)
{

	Super::OnConstruction(Transform);
	
	UMaterialInstanceConstant* DoorFrameMaterialAsset = Cast<UMaterialInstanceConstant>(StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("MaterialInstanceConstant'/Game/Assignment/Door/Materials/MI_Frame.MI_Frame'")));
	UMaterialInstanceConstant* DoorMaterialAsset = Cast<UMaterialInstanceConstant>(StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("MaterialInstanceConstant'/Game/Assignment/Door/Materials/MI_Door.MI_Door'")));

	if (DoorFrameMaterialAsset)
	{
		FrameDynamicMaterial = UMaterialInstanceDynamic::Create(DoorFrameMaterialAsset, this);
		FrameDynamicMaterial->SetVectorParameterValue("Color", Emissive);
		DoorFrame->SetMaterial(0, FrameDynamicMaterial);
	}

	if (DoorMaterialAsset)
	{
		DoorDynamicMaterial = UMaterialInstanceDynamic::Create(DoorMaterialAsset, this);
		DoorDynamicMaterial->SetVectorParameterValue("Color", Emissive);
		Door->SetMaterial(0, DoorDynamicMaterial);
	}
}

void ACDoor::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Super::ActorBeginOverlap(OverlappedActor, OtherActor);
	if (bIsOpened) return;

	player = Cast<ACPlayer>(OtherActor);
	if (player)
	{
		player->OtherActor = this;
	}
}

void ACDoor::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Super::ActorEndOverlap(OverlappedActor, OtherActor);
	
	if (player)
	{
		player->OtherActor = nullptr;
	}
	player = nullptr;
}

void ACDoor::Open(TArray<bool> InKeys)
{
	if (bIsOpened) return;
	
	if (Key == "RED" && InKeys[0] == true)
	{
		bIsOpened = true;
		Door->SetRelativeRotation(FRotator(0, -90, 0));
		return;
	}
	if (Key == "GREEN" && InKeys[1] == true)
	{
		bIsOpened = true;
		Door->SetRelativeRotation(FRotator(0, -90, 0));
		return;
	}
	if (Key == "BLUE" && InKeys[2] == true)
	{
		bIsOpened = true;
		Door->SetRelativeRotation(FRotator(0, -90, 0));
		return;
	}

	DrawDebugString(GetWorld(), FVector(0, 0, 50), "You don't have Key!", this, FColor::White, 2.0f);
}
