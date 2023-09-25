// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MainMenuStateEnum.h"
#include "MenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class XYZ_API AMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AMenuGameMode();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Handler")
		class ULoginHandler* LoginHandler;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Handler")
		class USessionHandler* SessionHandler;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Handler")
		class UUserStatRetriever* UserStatRetriever;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Handler")
		class UUserInfoRetriver* UserRetriever;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu State")
		EMainMenuStateEnum MenuState = EMainMenuStateEnum::PRE_LOGGING_IN;
	UFUNCTION(BlueprintCallable)
		void FindSession();
	UFUNCTION(BlueprintCallable)
		void CancelSession();
	UFUNCTION(BlueprintCallable)
		FString GetUsername();
	UFUNCTION(BlueprintCallable)
		FString GetStateToString();
private:
	bool bIsConnectingToSession;
	bool bIsFindingSession;
	bool bIsJoiningSession;
	bool bIsLoggingIn;
	bool bRetrievingStats;
};
