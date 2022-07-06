// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ShooterPlayerController.h"
#include "Components/InputComponent.h"
#include "Blueprint/UserWidget.h"
#include "Player/ShooterPlayerCharacter.h"
#include "HAL/IConsoleManager.h"

AShooterPlayerController::AShooterPlayerController() 
{
	if (PlayerInputComponent == nullptr)
	{
		PlayerInputComponent = CreateDefaultSubobject<UInputComponent>(TEXT("Player Input"));
	}
}

void AShooterPlayerController::BeginPlay() 
{
	Super::BeginPlay();
	GetPawn()->InputComponent = PlayerInputComponent;

	FInputModeGameOnly InputMode = {};
	SetInputMode(InputMode);

	HUDWidget = CreateWidget<UUserWidget, AShooterPlayerController>(this, HUDUserWidget, TEXT("HUD Widget"));

	if (!HUDWidget)
	{
		return;
	}

	HUDWidget->AddToViewport();

}

void AShooterPlayerController::SetupInputComponent() 
{
	Super::SetupInputComponent();

	InputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterPlayerController::SendMoveForwardToCharacter);
	InputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterPlayerController::SendMoveRightToCharacter);
	InputComponent->BindAxis(TEXT("LookRight"), this, &AShooterPlayerController::SendLookAroundToCharacter);
	InputComponent->BindAxis(TEXT("LookUp"), this, &AShooterPlayerController::SendLookUpToCharacter);

	InputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AShooterPlayerController::Jump);
	InputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Released, this, &AShooterPlayerController::JumpEnd);

	InputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &AShooterPlayerController::Fire);
}

void AShooterPlayerController::SendMoveForwardToCharacter(float Value)
{
	AShooterPlayerCharacter* ActiveCharacter = GetPlayerCharacter();

	if (!ActiveCharacter)
	{
		return;
	}

	ActiveCharacter->ChangeInputAxis(EInputAxisChange::EMoveForwards, Value);
}

void AShooterPlayerController::SendMoveRightToCharacter(float Value)
{
	AShooterPlayerCharacter* ActiveCharacter = GetPlayerCharacter();

	if (!ActiveCharacter)
	{
		return;
	}

	ActiveCharacter->ChangeInputAxis(EInputAxisChange::EMoveSideways, Value);
}

void AShooterPlayerController::SendLookAroundToCharacter(float Value)
{
	AShooterPlayerCharacter* ActiveCharacter = GetPlayerCharacter();

	if (!ActiveCharacter)
	{
		return;
	}

	ActiveCharacter->ChangeInputAxis(EInputAxisChange::ELookX, Value);
}

void AShooterPlayerController::SendLookUpToCharacter(float Value)
{
	AShooterPlayerCharacter* ActiveCharacter = GetPlayerCharacter();

	if (!ActiveCharacter)
	{
		return;
	}

	ActiveCharacter->ChangeInputAxis(EInputAxisChange::ELookY, Value);
}

void AShooterPlayerController::Jump()
{
	AShooterPlayerCharacter* ActiveCharacter = GetPlayerCharacter();

	if (!ActiveCharacter)
	{
		return;
	}

	ActiveCharacter->CharacterJump();
}

void AShooterPlayerController::JumpEnd()
{
	AShooterPlayerCharacter* ActiveCharacter = GetPlayerCharacter();

	if (!ActiveCharacter)
	{
		return;
	}

	ActiveCharacter->CharacterJumpEnd();
}

void AShooterPlayerController::Fire()
{
	AShooterPlayerCharacter* ActiveCharacter = GetPlayerCharacter();

	if (!ActiveCharacter)
	{
		return;
	}

	ActiveCharacter->ShootGun();
}

void AShooterPlayerController::GameOver(const bool bWin)
{
	if (!LoseUserWidget || !WinUserWidget)
	{
		return;
	}

	if (bWin)
	{
		GameOverWidget = CreateWidget<UUserWidget, AShooterPlayerController>(this, WinUserWidget, TEXT("Win Widget"));
	}
	else
	{
		GameOverWidget = CreateWidget<UUserWidget, AShooterPlayerController>(this, LoseUserWidget, TEXT("Lose Widget"));
	}

	if (!GameOverWidget)
	{
		return;
	}

	GameOverWidget->AddToViewport();

	FInputModeUIOnly WinScreenInputMode = {};
	WinScreenInputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);

	SetInputMode(WinScreenInputMode);

	GetWorld()->GetTimerManager().SetTimer(RestartTimerHandle, this, &AShooterPlayerController::RestartLevel, 5.f, false);
}

AShooterPlayerCharacter* AShooterPlayerController::GetPlayerCharacter() const
{
	return Cast<AShooterPlayerCharacter>(GetPawn());
}