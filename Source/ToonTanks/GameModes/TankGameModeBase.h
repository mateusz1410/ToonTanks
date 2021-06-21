// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
private:
	int32 GetTargetTurretCount();
	void HandleGameStart();
	void HandleGameOver(bool bPlayerWon);

	class APawnTank* PlayerTank;
	int32 TargetTurrets;
	class APlayerControllerBase* PlayerControllerRef;
public:

	void ActorDied(AActor* DeadActor);
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category  = "Game Loop")
	int32 StartDelay = 3;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bPlayerWon);
};
