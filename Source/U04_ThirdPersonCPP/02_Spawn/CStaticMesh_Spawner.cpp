
#include "CStaticMeshBase.h"
#include "CStaticMesh_Spawner.h"

ACStaticMesh_Spawner::ACStaticMesh_Spawner()
{
 

}

void ACStaticMesh_Spawner::BeginPlay()
{
	Super::BeginPlay();
	
	FVector location = GetActorLocation();

	for (int32 i = 0; i < 4; i++)
	{
		FTransform transform;
		SpawnedObjects[i] = GetWorld()->SpawnActor<ACStaticMeshBase>(SpawnClasses[i], transform);

		SpawnedObjects[i]->SetActorLocation(FVector(location.X, location.Y + i * 200, location.Z));
	}
}



