// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "USDebugItem.generated.h"

UCLASS()
class ULTIMATESLASHER_API AUSDebugItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AUSDebugItem();

protected:
	virtual void BeginPlay() override;

};
