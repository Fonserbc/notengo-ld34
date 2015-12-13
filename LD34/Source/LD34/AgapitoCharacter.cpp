// MIT

#include "LD34.h"
#include "AgapitoCharacter.h"

// Sets default values
AAgapitoCharacter::AAgapitoCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(100.0f, 100.0f);
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 300.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 2000.0f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = true;
	CameraBoom->TargetArmLength = 2000.0f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.0f, 0.f);
	CameraBoom->bDoCollisionTest = false;

	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false;

	//GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	//GetMesh()->SetRelativeScale3D(FVector(10.0f));
}

// Called when the game starts or when spawned
void AAgapitoCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAgapitoCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

// Called to bind functionality to input
void AAgapitoCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAxis("MoveX", this, &AAgapitoCharacter::MoveXAxis);
	InputComponent->BindAxis("MoveY", this, &AAgapitoCharacter::MoveYAxis);
}

void AAgapitoCharacter::MoveXAxis(float AxisValue) {
	FVector dir = FVector(FMath::Clamp(AxisValue, -1.0f, 1.0f),0.f,0.f);
	// add movement in that direction
	AddMovementInput(dir, 10.0f);
}

void AAgapitoCharacter::MoveYAxis(float AxisValue) {
	FVector dir = FVector(0.f,FMath::Clamp(AxisValue, -1.0f, 1.0f), 0.f);
	// add movement in that direction
	AddMovementInput(dir, 10.0f);
}

