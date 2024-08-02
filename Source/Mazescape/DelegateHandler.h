// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

DECLARE_DELEGATE(FMyDelegate);

class MAZESCAPE_API DelegateHandler
{
public:
	DelegateHandler();
	~DelegateHandler();

	static FMyDelegate MyDelegate;

	static void HandleDelegateCall();
};
