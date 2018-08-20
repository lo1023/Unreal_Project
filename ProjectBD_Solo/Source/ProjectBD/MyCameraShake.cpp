// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCameraShake.h"

UMyCameraShake::UMyCameraShake()
{
	OscillationDuration = 0.1f;
	OscillationBlendInTime = 0.05f;
	OscillationBlendOutTime = 0.05f;
	
	RotOscillation.Pitch.Amplitude = 10.f;
	RotOscillation.Pitch.Frequency = 1.0f;
	RotOscillation.Pitch.InitialOffset = EInitialOscillatorOffset::EOO_OffsetZero;

	//RotOscillation.Yaw.Amplitude = 2.0f;
	//RotOscillation.Yaw.Frequency = 1.0f;
	//RotOscillation.Yaw.InitialOffset = EInitialOscillatorOffset::EOO_OffsetRandom;
}


