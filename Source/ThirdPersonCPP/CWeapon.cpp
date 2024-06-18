#include "CWeapon.h"
#include "CWeaponInterface.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "Global.h"
#include "CPlayer.h"

static TAutoConsoleVariable<bool> CVarDebugLine(TEXT("Tore.DrawDebugLine"), false, TEXT("Enable Draw Aim Line"), ECVF_Cheat);

ACWeapon::ACWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	HolsterSocket = "Holster_AR4";
	HandSocket = "Hand_AR4";

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>("MeshComp");
	RootComponent = MeshComp;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Game/Weapons/Meshes/AR4/SK_AR4"));
	if (MeshAsset.Succeeded())
	{
		MeshComp->SetSkeletalMesh(MeshAsset.Object);
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> EquipMontageAsset(TEXT("/Game/Character/Animations/AR4/Equip_Montage"));
	if (EquipMontageAsset.Succeeded())
	{
		EquipMontage = EquipMontageAsset.Object;
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> UnequipMontageAsset(TEXT("/Game/Character/Animations/AR4/Unequip_Montage"));
	if (UnequipMontageAsset.Succeeded())
	{
		UnequipMontage = UnequipMontageAsset.Object;
	}

	ConstructorHelpers::FClassFinder<UCameraShake> CameraShakeClassAsset(TEXT("/Game/BP_FireShake"));
	if (UnequipMontageAsset.Succeeded())
	{
		CameraShakeClass = CameraShakeClassAsset.Class;
	}
}

void ACWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (OwnerCharacter)
	{
		AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HolsterSocket);
	}
}

void ACWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bAiming == false) return;

	ICWeaponInterface* ImplementedActor = Cast<ICWeaponInterface>(OwnerCharacter);
	if (ImplementedActor == nullptr) return;

	FVector Start, End, Direction;
	ImplementedActor->GetAimInfo(Start, End, Direction);

	bool bDrawDebug = CVarDebugLine.GetValueOnGameThread();
	if (bDrawDebug)
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, -1, 0, 2.f);
	}

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(OwnerCharacter);
	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Visibility, Params))
	{
		if (Hit.Component->IsSimulatingPhysics())
		{
			ImplementedActor->OnTarget();
			return;
		}
	}
	ImplementedActor->OffTarget();
}

void ACWeapon::Begin_Aiming()
{
	bAiming = true; 
}

void ACWeapon::End_Aiming()
{
	bAiming = false;
}

void ACWeapon::Begin_Fire()
{
	if (bEquipped == false) return;
	if (bEquipping == true) return;
	if (bAiming == false) return;
	if (bFiring == true) return;

	bFiring = true;

	Firing();
}

void ACWeapon::End_Fire()
{
	bFiring = false;
}

void ACWeapon::Firing()
{
	ACPlayer* Player = Cast<ACPlayer>(OwnerCharacter);
	if (Player)
	{
		APlayerController* PC = OwnerCharacter->GetController<APlayerController>();

		if (CameraShakeClass)
		{
			PC->PlayerCameraManager->PlayCameraShake(CameraShakeClass);
		}
	}

	ICWeaponInterface* ImplementedActor = Cast<ICWeaponInterface>(OwnerCharacter);
	if (ImplementedActor == nullptr) return;

	FVector Start, End, Direction;
	ImplementedActor->GetAimInfo(Start, End, Direction);

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(OwnerCharacter);
	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Visibility, Params))
	{
		if (Hit.Component->IsSimulatingPhysics())
		{
			Direction = Hit.Actor->GetActorLocation() - OwnerCharacter->GetActorLocation();
			Direction.Normalize();

			Hit.Component->AddImpulseAtLocation(Direction * 1500.f, OwnerCharacter->GetActorLocation());
		}
	}
}

void ACWeapon::Equip()
{
	if (bEquipping) return;
	if (bEquipped) return;

	bEquipping = true;
	OwnerCharacter->PlayAnimMontage(EquipMontage);
}

void ACWeapon::Begin_Equip()
{
	bEquipped = true;
	AttachToComponent
	(
		OwnerCharacter->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		HandSocket
	);
}

void ACWeapon::End_Equip()
{
	bEquipping = false;
}


void ACWeapon::Unequip()
{
	if (bEquipping) return;
	if (!bEquipped) return;
	bEquipping = true;
	OwnerCharacter->PlayAnimMontage(UnequipMontage);
}

void ACWeapon::Begin_Unequip()
{
	bEquipped = false;
	AttachToComponent
	(
		OwnerCharacter->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		HolsterSocket
	);
}

void ACWeapon::End_Unequip()
{
	bEquipping = false;

}

