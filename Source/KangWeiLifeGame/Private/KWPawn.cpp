#include "KWPawn.h"
#include "Components/SceneComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "KWCube.h"
#include "KWActor.h"

// Sets default values
AKWPawn::AKWPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	rootComp = CreateAbstractDefaultSubobject<USceneComponent>(TEXT("rootComp"));
	cameraArmComp= CreateAbstractDefaultSubobject<USpringArmComponent>(TEXT("cameraArmComp"));
	cameraComp = CreateAbstractDefaultSubobject<UCameraComponent>(TEXT("cameraComp"));

	RootComponent = rootComp;
	cameraArmComp->SetupAttachment(rootComp);
	cameraComp->SetupAttachment(cameraArmComp);

}

// Called when the game starts or when spawned
void AKWPawn::BeginPlay()
{
	Super::BeginPlay();
	playerCtr = Cast<APlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (playerCtr)	playerCtr->bShowMouseCursor = true;
	if (kwActor_BP)
	{
		kwActor = Cast<AKWActor>(UGameplayStatics::GetActorOfClass(this, kwActor_BP));
	}
}

void AKWPawn::SetSpringArmLength(float inValue)
{
	cameraArmComp->TargetArmLength += inValue*-20;
}

// Called every frame
void AKWPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!gamePause)
	{
		intervalTime += DeltaTime;
		if (intervalTime > evolveSpeed)
		{
			kwActor->RefreshGrid(kwActor->gridSize);
			intervalTime = 0.0f;
		}
	}
}

// Called to bind functionality to input
void AKWPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("CameraPull", this, &AKWPawn::SetSpringArmLength);
	PlayerInputComponent->BindAction("MouseClick", IE_Pressed, this, &AKWPawn::MouseButtomClick);
}

void AKWPawn::MouseButtomClick()
{
	FHitResult hitresult;
	FVector mouseWorldLocation, mouseWorldDerection;
	playerCtr->DeprojectMousePositionToWorld(mouseWorldLocation, mouseWorldDerection);
	ECollisionChannel collisionchannel = ECollisionChannel::ECC_Pawn;
	GetWorld()->LineTraceSingleByChannel(hitresult, mouseWorldLocation, mouseWorldLocation + 10000 * mouseWorldDerection, collisionchannel);
	AKWCube* hitcube = Cast<AKWCube>(hitresult.GetActor());
	if (hitcube)
	{
		FVector hitWorldLocation = hitcube->GetActorLocation();
		FVector2D hitLocal = kwActor->ChangeWorldLocationToLocal(hitWorldLocation, kwActor->gridSize);
		if (kwActor)
		{
			if (kwActor->gridMap[hitLocal])
			{
				hitcube->SetActorHiddenInGame(true);
				kwActor->gridMap.Add(hitLocal, 0);
			}
			else
			{
				hitcube->SetActorHiddenInGame(false);
				kwActor->gridMap.Add(hitLocal, 1);
			}
		}
	}
}

void AKWPawn::StartGame()
{
	if (kwActor)	kwActor->StartGame(kwActor->gridXCount, kwActor->gridYCount, kwActor->gridSize);
}

