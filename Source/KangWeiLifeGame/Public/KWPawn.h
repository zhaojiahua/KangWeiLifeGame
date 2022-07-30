﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "KWPawn.generated.h"

UCLASS()
class KANGWEILIFEGAME_API AKWPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AKWPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetSpringArmLength(float inValue);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//公开的变量
	UPROPERTY(VisibleAnywhere,category="zjhAddAttrs")
		class USceneComponent* rootComp;
	UPROPERTY(VisibleAnywhere,  category = "zjhAddAttrs")
		class USpringArmComponent* cameraArmComp;
	UPROPERTY(VisibleAnywhere,  category = "zjhAddAttrs")
		class UCameraComponent* cameraComp;

	class APlayerController* playerCtr;
	UPROPERTY(EditAnywhere, category = "zjhAddAttrs")
		TSubclassOf<AActor> kwActor_BP;
	class AKWActor* kwActor;

	//公开的函数
	UFUNCTION(BlueprintCallable, category = "zjhAddFuns")
		void MouseButtomClick();
};
