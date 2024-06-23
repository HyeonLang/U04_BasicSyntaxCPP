#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CWeapon.generated.h"

class USkeletalMeshComponent;
class ACharacter;
class UAnimMontage;
class ACBullet;
class UParticleSystem;
class USoundCue;
class UMaterialInstanceConstant;
class ACMagazine;

UCLASS()
class THIRDPERSONCPP_API ACWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ACWeapon();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	FORCEINLINE bool IsEquipped() { return bEquipped; }
	FORCEINLINE bool IsEquipping() { return bEquipping; }
	FORCEINLINE bool IsAiming() { return bAiming; }
	FORCEINLINE USkeletalMeshComponent* GetMesh() { return MeshComp; }

	FORCEINLINE bool IsFireing() { return bFiring; }
	FORCEINLINE bool IsAutoFire() { return bAutoFire; }
	FORCEINLINE bool IsReloading() { return bReloading; }
	FORCEINLINE int32 GetCurrentBullet() { return CurrentBullet; }

	void ToggleAutoFire();

	void Begin_Aiming();
	void End_Aiming();

	void Begin_Fire();
	void End_Fire();

	UFUNCTION()
	void Firing();

	void Reloading();
	void Begin_Reload();
	void Out_Reload();
	void End_Reload();

	void Equip();
	void Begin_Equip();
	void End_Equip();

	void Unequip();
	void Begin_Unequip();
	void End_Unequip();

private:
	UPROPERTY(EditDefaultsOnly, Category = "BulletClass")
	TSubclassOf<ACBullet> BulletClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "MagClass")
	TSubclassOf<ACMagazine> MagClass;

	UPROPERTY(EditDefaultsOnly, Category = "AutoFire")
	float FireInterval;

	UPROPERTY(EditDefaultsOnly, Category = "AutoFire")
	float PitchSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Socket")
	FName HolsterSocket;

	UPROPERTY(EditDefaultsOnly, Category = "Socket")
	FName HandSocket;

	UPROPERTY(EditDefaultsOnly, Category = "Montage")
	UAnimMontage* EquipMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montage")
	UAnimMontage* UnequipMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montage")
	UAnimMontage* ReloadMontage;

	UPROPERTY(EditDefaultsOnly, Category = "CameraShake")
	TSubclassOf<UCameraShake> CameraShakeClass;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* MuzzleParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* EjectParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* ImpactParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	USoundCue* FireSound;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UMaterialInstanceConstant* DecalMaterial;

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Bullet")
	int32 MaxBullet;

	UPROPERTY(BlueprintReadOnly)
	int32 CurrentBullet;
	
private:
	UPROPERTY(VisibleDefaultsOnly)
	USkeletalMeshComponent* MeshComp;

	ACharacter* OwnerCharacter;

	bool bEquipped;
	bool bEquipping;
	bool bAiming;
	bool bFiring;
	bool bAutoFire;
	bool bReloading;

	float CurrentPitch;
	FTimerHandle AutoTimerHandle;
	ACMagazine* Magazine;
};
