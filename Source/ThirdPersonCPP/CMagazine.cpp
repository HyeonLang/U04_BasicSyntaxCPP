// Fill out your copyright notice in the Description page of Project Settings.


#include "CMagazine.h"

// Sets default values
ACMagazine::ACMagazine()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;

	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Weapons/Meshes/AR4/SM_AR4_Mag_Empty"));
	if (MeshAsset.Succeeded())
	{
		MeshComp->SetStaticMesh(MeshAsset.Object);
	}

	MeshComp->SetSimulatePhysics(true);
}