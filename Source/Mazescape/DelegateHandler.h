// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

DECLARE_DELEGATE(FMyDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FMyNonDynamicDelegate, AActor*);

class MAZESCAPE_API DelegateHandler : public AActor
{
public:
	DelegateHandler();
	~DelegateHandler();

	static FMyDelegate MyDelegate;

	static FMyDelegate OnTimerStart;
	static FMyDelegate OnTimerStop;
	static FMyDelegate OnTimerReset;

	static FMyNonDynamicDelegate MyDelegate2;

	static void HandleDelegateCall();

};
