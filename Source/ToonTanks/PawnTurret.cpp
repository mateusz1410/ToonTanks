// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "PawnTank.h"
#include "Kismet/GameplayStatics.h"

APawnTurret::APawnTurret()
{
	FireRate = 2.0f;
	FireRange = 700.f;
}

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!PlayerPawn || ReturnDistanceToPlayer() > FireRange)
	{
		return;
	}

	RotateTurret(PlayerPawn->GetActorLocation());

}
void APawnTurret::CheckFireCondition()
{

	if (!PlayerPawn || !PlayerPawn->GetIsPlayerAlive())
	{
		return;
	}
	if (ReturnDistanceToPlayer() <= FireRange)
	{

		Fire();
	}

}

float APawnTurret::ReturnDistanceToPlayer()
{
	if (!PlayerPawn)
	{
		return 0.0f;
	}
	float  Distance = FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
	//UE_LOG(LogTemp, Warning, TEXT("Size %f"),(PlayerPawn->GetActorLocation() - GetActorLocation()).Size());
	//UE_LOG(LogTemp, Warning, TEXT("Size %f"), Distance);

	return Distance;
}

void APawnTurret::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();

}