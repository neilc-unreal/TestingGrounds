// Fill out your copyright notice in the Description page of Project Settings.

#include "TestingGrounds.h"
#include "SuperGun.h"


// Sets default values
ASuperGun::ASuperGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASuperGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASuperGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

