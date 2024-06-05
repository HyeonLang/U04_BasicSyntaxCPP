#include "CLogActor.h"
#include "Global.h"

ACLogActor::ACLogActor()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACLogActor::BeginPlay()
{
	Super::BeginPlay();

	CLog::Print(1);
	CLog::Print(2, 1);
	CLog::Print(3, 2, 20.f);
	CLog::Print(4, 2, 20.f, FColor::Orange);
	CLog::Print("Hellp C++ World");
	CLog::Print(GetActorLocation());
	CLog::Print(GetActorRotation());

	CLog::Log(777);
	CLog::Log(PI);
	CLog::Log("Hello");
	CLog::Log(GetActorLocation());
	CLog::Log(GetActorRotation());
	CLog::Log(this);
	CLog::Log(__FILE__);
	CLog::Log(__FUNCTION__, __LINE__);	// ACLogActor::BeginPlay(), 29
	PrintLine()	// ACLogActor::BeginPlay(), 29
}

void ACLogActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//RunningTime += DeltaTime; 
	RunningTime = GetWorld()->TimeSeconds;
	CLog::Print(RunningTime, 100);

}

