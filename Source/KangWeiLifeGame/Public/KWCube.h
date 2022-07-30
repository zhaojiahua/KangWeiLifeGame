// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KWCube.generated.h"

UCLASS()
class KANGWEILIFEGAME_API AKWCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKWCube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//公开的属性
	UPROPERTY(VisibleAnywhere, category = "zjhAddAttrs")
		class USceneComponent* rootSceneComp;
	UPROPERTY(VisibleAnywhere, category = "zjhAddAttrs")
		class UStaticMeshComponent* staticCubeComp;


};
