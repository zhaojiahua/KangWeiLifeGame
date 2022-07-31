#include "KWActor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "KWCube.h"
#include "Materials/MaterialInstance.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
AKWActor::AKWActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	rootSceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("rootSceneComp"));
	RootComponent = rootSceneComp;
}

// Called when the game starts or when spawned
void AKWActor::BeginPlay()
{
	Super::BeginPlay();
	GenerateGrid(gridXCount, gridYCount, gridSize);
}

// Called every frame
void AKWActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AKWCube* AKWActor::GenerateCube(FVector2D inLocal, float inSize)
{
	FVector spawnLocation = ChangeLocalLocationToWorld(inLocal, inSize);
	FActorSpawnParameters spawnPara;
	AKWCube* newCube = nullptr;
	if (kwCube)
	{
		newCube = GetWorld()->SpawnActor<AKWCube>(kwCube, spawnLocation, FRotator(0.0f), spawnPara);
		//死亡状态的材质
		forDeathDynMat = UMaterialInstanceDynamic::Create(matForCube_BP, this, "forDeathDynMat");
		forDeathDynMat->SetVectorParameterValue("color", FVector4(0.1f, 0.15f, 0.5f, 1.0f));
		forDeathDynMat->SetScalarParameterValue("opacity", 0.0f);
		forDeathDynMat->SetScalarParameterValue("emissive", 0.1f);
		if (forDeathDynMat)	newCube->staticCubeComp->SetMaterial(0, forDeathDynMat);
	}
	return newCube;
}

void AKWActor::RefreshGrid(float inSize)
{
	TMap<FVector2D, int> temp_gridMap;
	temp_gridMap.Empty();
	for (auto& item : gridMap)
	{
		if (WillBeLiving(item.Key))		temp_gridMap.Add(item.Key, 1);
		else temp_gridMap.Add(item.Key, 0);
	}

	for (auto& item : temp_gridMap)
	{
		AKWCube* newCube = Cast<AKWCube>(gridActorMap[item.Key]);
		if (item.Value)
		{
			if (forLiveDynMat)	newCube->staticCubeComp->SetMaterial(0, forLiveDynMat);
		}
		else
		{
			if (forDeathDynMat)	newCube->staticCubeComp->SetMaterial(0, forDeathDynMat);
		}
	}
	gridMap = temp_gridMap;
	UE_LOG(LogTemp, Warning, TEXT("刷新!"));
}

bool AKWActor::WillBeLiving(FVector2D inLocal)
{
	TArray <FVector2D>  temp2dArray = {
																	FVector2D(inLocal.X - 1, inLocal.Y),
																	FVector2D(inLocal.X + 1, inLocal.Y),
																	FVector2D(inLocal.X, inLocal.Y - 1),
																	FVector2D(inLocal.X, inLocal.Y + 1),
																	FVector2D(inLocal.X - 1, inLocal.Y - 1),
																	FVector2D(inLocal.X - 1, inLocal.Y + 1),
																	FVector2D(inLocal.X + 1, inLocal.Y + 1),
																	FVector2D(inLocal.X + 1, inLocal.Y - 1)
	};

	int tempInt = 0;
	for (FVector2D temp2d : temp2dArray)
	{
		if (temp2d.X < gridXCount && temp2d.Y < gridYCount)
		{
			tempInt += gridMap.FindRef(temp2d);
		}
	}
	if (gridMap[inLocal]==1)
	{
		if (tempInt == 2 || tempInt == 3) return true;
		return false;
	}
	else
	{
		if (tempInt == 3)	return true;
		return false;
	}
}

FVector2D AKWActor::SafeVector2D(FVector2D inVector2D)
{
	return FVector2D(int(inVector2D.X) % gridXCount, int(inVector2D.Y) % gridYCount);
}

FVector AKWActor::ChangeLocalLocationToWorld(FVector2D inLocation, float inSize)
{
	FVector actorLocation = GetActorLocation();
	FVector tempVector = FVector(actorLocation.X, actorLocation.Y + inLocation.X * inSize, actorLocation.Z + inLocation.Y * inSize);
	return tempVector;
}

FVector2D AKWActor::ChangeWorldLocationToLocal(FVector inLocation, float inSize)
{
	FVector actorLocation = GetActorLocation();
	inLocation -= actorLocation;
	int x = FMath::RoundToInt(inLocation.Y / inSize);
	int y = FMath::RoundToInt(inLocation.Z / inSize);
	return FVector2D(x, y);
}

void AKWActor::GenerateGrid(int inXCount, int inYCount, float inGridSize)
{
	gridMap.Empty();
	gridActorMap.Empty();
	FVector actorLocation = GetActorLocation();
	for (int x = 0; x < inXCount; x++)
	{
		for (int y = 0; y < inYCount; y++)
		{
			gridMap.Add(FVector2D(x, y), 0);
			AKWCube* newkwCube = GenerateCube(FVector2D(x, y), inGridSize);
			if (forDeathDynMat)	newkwCube->staticCubeComp->SetMaterial(0, forDeathDynMat);
			gridActorMap.Add(FVector2D(x, y), newkwCube);
		}
	}
}

void AKWActor::RestartGame(int inXCount, int inYCount, float inGridSize)
{
	for (int x = 0; x < inXCount; x++)
	{
		for (int y = 0; y < inYCount; y++)
		{
			gridMap.Add(FVector2D(x, y), 0);
			AKWCube* currentCube = Cast<AKWCube>(gridActorMap[FVector2D(x, y)]);
			if (forDeathDynMat)	currentCube->staticCubeComp->SetMaterial(0, forDeathDynMat);
			//gridActorMap[FVector2D(x, y)]->SetActorHiddenInGame(true);
		}
	}
}

void AKWActor::ChangeCubeMat(FVector2D inLocal, bool inLive)
{
	AKWCube* currentCube = Cast<AKWCube>(gridActorMap[inLocal]);
	if (inLive)
	{
		//激活状态的材质
		forLiveDynMat = UMaterialInstanceDynamic::Create(matForCube_BP, this, "forLiveDynMat");
		forLiveDynMat->SetVectorParameterValue("color", FVector4(0.95f, 0.3f, 0.1f, 1.0f));
		forLiveDynMat->SetScalarParameterValue("opacity", 1.0f);
		forLiveDynMat->SetScalarParameterValue("emissive", 0.02f);
		if (forLiveDynMat)	currentCube->staticCubeComp->SetMaterial(0, forLiveDynMat);
	}
	else
	{
		//死亡状态的材质
		forDeathDynMat = UMaterialInstanceDynamic::Create(matForCube_BP, this, "forDeathDynMat");
		forDeathDynMat->SetVectorParameterValue("color", FVector4(0.1f, 0.15f, 0.5f, 1.0f));
		forDeathDynMat->SetScalarParameterValue("opacity", 0.0f);
		forDeathDynMat->SetScalarParameterValue("emissive", 0.1f);
		if (forDeathDynMat)	currentCube->staticCubeComp->SetMaterial(0, forDeathDynMat);
	}
}

