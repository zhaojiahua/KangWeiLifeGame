// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KWActor.generated.h"

UCLASS()
class KANGWEILIFEGAME_API AKWActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKWActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//公开的属性
	UPROPERTY(VisibleAnywhere, category = "zjhAddAttrs")
		class USceneComponent* rootSceneComp;
	UPROPERTY(EditAnywhere, category = "zjhAddAttrs")
		class UStaticMeshComponent* bgComp;
	UPROPERTY(BlueprintReadOnly, category = "zjhAddAttrs")
		TMap<FVector2D, int> gridMap;
	UPROPERTY(BlueprintReadOnly, category = "zjhAddAttrs")
		TMap<FVector2D, AActor*> gridActorMap;
	UPROPERTY(EditAnywhere, category = "zjhAddAttrs")
		TSubclassOf<class AKWCube> kwCube;

	UPROPERTY(EditAnywhere, category = "zjhAddAttrs")
		int gridXCount = 100;
	UPROPERTY(EditAnywhere, category = "zjhAddAttrs")
		int gridYCount = 100;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, category = "zjhAddAttrs")
		float gridSize = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "zjhAddAttrs")
		float evolveSpeed = 1.0f;
	float intervalTime = 0.0f;

public:
	//公开的函数
	UFUNCTION(BlueprintImplementableEvent, category = "zjhAddFuns")
		void DrawGrid();
	UFUNCTION(BlueprintCallable, category = "zjhAddFuns")
		AKWCube* GenerateCube(FVector2D inLocal, float inSize);

	void RefreshGrid(float inSize);
	bool WillBeLiving(FVector2D inLocal);
	FVector2D SafeVector2D(FVector2D inVector2D);

	FVector ChangeLocalLocationToWorld(FVector2D inLocation,float inSize);
	FVector2D ChangeWorldLocationToLocal(FVector inLocation, float inSize);

private:
	void GenerateGrid(int inXCount, int inYCount, float inGridSize);
};
