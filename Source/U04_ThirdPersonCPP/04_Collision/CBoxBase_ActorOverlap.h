#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBoxBase.h"
#include "CBoxBase_ActorOverlap.generated.h"


UCLASS()
class U04_THIRDPERSONCPP_API ACBoxBase_ActorOverlap : public ACBoxBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
