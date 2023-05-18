// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Practies.h"

/**
 * 
 */
class PRACTIES_API DebugAPI
{
public:
	DebugAPI();
	~DebugAPI();

	static ULineBatchComponent* GetDebugLineBatcher(const UWorld* InWorld, bool bPersistentLines, float LifeTime, bool bDepthIsForeground);
	static float GetDebugLineLifeTime(ULineBatchComponent* LineBatcher, float LifeTime, bool bPersistent);


	static void DrawRadial(const UWorld* _InWorld,
		const FMatrix& _TransformMatrix,
		float _Radius,
		float _Angle,
		const FColor& _Color,
		int32 _Segments,
		float _LifeTime,
		bool _bPersistentLines,
		uint8 _DepthPriority,
		float _Thickness);
};
