// Fill out your copyright notice in the Description page of Project Settings.


#include "DelegateHandler.h"

FMyDelegate DelegateHandler::MyDelegate;

FMyDelegate DelegateHandler::OnTimerStart;
FMyDelegate DelegateHandler::OnTimerReset;

FMyDelegate DelegateHandler::OnPlayerWin;
FMyDelegate DelegateHandler::OnPlayerLoose;

FMyDelegate DelegateHandler::OnRestartGame;

FMyDelegateOneParam DelegateHandler::OnTimerStop;

FMyNonDynamicDelegate DelegateHandler::MyDelegate2;

DelegateHandler::DelegateHandler()
{
}

DelegateHandler::~DelegateHandler()
{
}

void DelegateHandler::HandleDelegateCall()
{
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Delegate call handled by DelegateHandler!"));
}
