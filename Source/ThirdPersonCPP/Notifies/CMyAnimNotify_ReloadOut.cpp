// Fill out your copyright notice in the Description page of Project Settings.


#include "CMyAnimNotify_ReloadOut.h"
#include "CWeaponInterface.h"
#include "CWeapon.h"

FString UCMyAnimNotify_ReloadOut::GetNotifyName_Implementation() const
{
	return "ReloadOut";
}


void UCMyAnimNotify_ReloadOut::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (MeshComp->GetOwner() == nullptr) return;

	ICWeaponInterface* ImplementedOwner = Cast<ICWeaponInterface>(MeshComp->GetOwner());
	if (ImplementedOwner == nullptr) return;

	ACWeapon* Weapon = ImplementedOwner->GetWeapon();
	if (Weapon == nullptr) return;

	Weapon->Out_Reload();
}
