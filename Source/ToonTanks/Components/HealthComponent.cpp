// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "ToonTanks/GameModes/TankGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	DefaultHealth = 100.0f;
	Health = 0.0f;
	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = DefaultHealth;
	GameModeBaseRef = Cast<ATankGameModeBase>(UGameplayStatics::GetGameMode(this));
	GetOwner()->OnTakeAnyDamage.AddDynamic(this,&UHealthComponent::TakeDamage);
	// ...
	
}

void UHealthComponent::TakeDamage(AActor * DamagedActor, float Damage, const UDamageType * Damagetype, AController * InstigatedBy, AActor * DamageCauser)
{
	if (Damage == 0 || Health <= 0)
	{
		return;
	}

	Health = FMath::Clamp(Health-Damage, 0.0f, DefaultHealth);
	UE_LOG(LogTemp, Error, TEXT("Health: %f"), Health);

	if (Health <= 0)
	{
		if (GameModeBaseRef)
		{
			GameModeBaseRef->ActorDied(GetOwner());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Health Component not valid GameModeBaseRef"));
		}
	}
}


//
//// Called every frame
//void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}

