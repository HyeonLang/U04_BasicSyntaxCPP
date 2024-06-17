// Fill out your copyright notice in the Description page of Project Settings.


#include "CChest.h"
#include "CPlayer.h"
#include "DrawDebugHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

ACChest::ACChest()
{
	Lid = CreateDefaultSubobject<UStaticMeshComponent>("LID");
	Lid->SetupAttachment(RootComp);
	ConstructorHelpers::FObjectFinder<UStaticMesh> LidAsset(TEXT("StaticMesh'/Game/Assignment/Chest/SM_ChestTop.SM_ChestTop'"));
	if (LidAsset.Succeeded())
	{
		Lid->SetStaticMesh(LidAsset.Object);
	}

	Bottom = CreateDefaultSubobject<UStaticMeshComponent>("BOTTOM");
	Bottom->SetupAttachment(RootComp);
	ConstructorHelpers::FObjectFinder<UStaticMesh> BottomAsset(TEXT("StaticMesh'/Game/Assignment/Chest/SM_ChestBottom.SM_ChestBottom'"));
	if (BottomAsset.Succeeded())
	{
		Bottom->SetStaticMesh(BottomAsset.Object);
	}

	Lid->SetRelativeLocation(FVector(-140, 0, -30));
	Bottom->SetRelativeLocation(FVector(-140, 0, -30));

	Emissive = FLinearColor(1, 0, 0);
}


void ACChest::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	UMaterialInstanceConstant* materialAsset = Cast<UMaterialInstanceConstant>(StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("/Game/Assignment/Chest/MI_Chest")));

	if (materialAsset)
	{
		DynamicMaterial = UMaterialInstanceDynamic::Create(materialAsset, this);
		DynamicMaterial->SetVectorParameterValue("Emissive", Emissive);
		Lid->SetMaterial(0, DynamicMaterial);
		Bottom->SetMaterial(0, DynamicMaterial);
	}
}

void ACChest::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Super::ActorBeginOverlap(OverlappedActor, OtherActor);
	if (bIsOpened) return;
	DrawDebugString(GetWorld(), FVector(0, 0, 50), "press F key!", this, FColor::White, 2.0f);

	ACPlayer* player = Cast<ACPlayer>(OtherActor);
	if (player)
	{
		player->OtherActor = this;
	}
}

void ACChest::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Super::ActorEndOverlap(OverlappedActor, OtherActor);

	ACPlayer* player = Cast<ACPlayer>(OtherActor);
	if (player)
	{
		player->OtherActor = nullptr;
	}
}

void ACChest::Open(FName& OutKey)
{
	if (bIsOpened) return;
	Lid->SetRelativeRotation(FRotator(110, 0, 0));
	bIsOpened = true;
	OutKey = Key;
}
