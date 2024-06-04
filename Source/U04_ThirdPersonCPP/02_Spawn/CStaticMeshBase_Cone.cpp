// Fill out your copyright notice in the Description page of Project Settings.


#include "CStaticMeshBase_Cone.h"

ACStaticMeshBase_Cone::ACStaticMeshBase_Cone()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> meshAsset(TEXT("/Game/StaticMeshes/SM_Cone"));

	if (meshAsset.Succeeded())	
		MeshComp->SetStaticMesh(meshAsset.Object);
}
