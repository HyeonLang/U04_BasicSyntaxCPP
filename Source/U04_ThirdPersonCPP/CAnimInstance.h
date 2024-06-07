#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance.generated.h"


UCLASS()
class U04_THIRDPERSONCPP_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeBeginPlay() override;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character")
	float Speed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character")
	float Direction;
private:
	APawn* OnwerPawn;
	
	
};
