#include "KWPawn.h"
#include "Components/SceneComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

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
	
}

void AKWPawn::SetSpringArmLength(float inValue)
{
	cameraArmComp->TargetArmLength += inValue*-10;
}

// Called every frame
void AKWPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AKWPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("CameraPull", this, &AKWPawn::SetSpringArmLength);
}

