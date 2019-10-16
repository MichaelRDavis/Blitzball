// Fill out your copyright notice in the Description page of Project Settings.


#include "FWeap_Shotgun.h"

AFWeap_Shotgun::AFWeap_Shotgun()
{

}

void AFWeap_Shotgun::Fire()
{
	for (int32 i = 0; i < AmmoCost; i++)
	{
		FireInstantHit();
	}
}
