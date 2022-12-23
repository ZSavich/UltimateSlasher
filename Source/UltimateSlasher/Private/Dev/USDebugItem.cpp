// Fill out your copyright notice in the Description page of Project Settings.

#include "Dev/USDebugItem.h"
#include "DebugMacros.h"

AUSDebugItem::AUSDebugItem()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AUSDebugItem::BeginPlay()
{
	Super::BeginPlay();
	
	const FVector Location = GetActorLocation();
	const FVector ForwardLocation = GetActorForwardVector() * 10.f;

	DRAW_SPHERE(Location, FColor::Red);
	DRAW_LINE(Location, ForwardLocation);
	DRAW_POINT(ForwardLocation);

	DRAW_VECTOR(Location, ForwardLocation * -1.f);
	DRAW_BOX(ForwardLocation * -1.f);
}

