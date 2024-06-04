// Fill out your copyright notice in the Description page of Project Settings.


#include "CStaticMeshBase_Cylinder.h"

ACStaticMeshBase_Cylinder::ACStaticMeshBase_Cylinder()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> meshAsset(TEXT("/Game/StaticMeshes/SM_Cylinder"));

	if (meshAsset.Succeeded())	
		MeshComp->SetStaticMesh(meshAsset.Object);
}
