// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugAPI.h"
#include "DrawDebugHelpers.h"
#include "Components/LineBatchComponent.h"

DebugAPI::DebugAPI()
{
}

DebugAPI::~DebugAPI()
{
}

ULineBatchComponent* DebugAPI::GetDebugLineBatcher(const UWorld* InWorld, bool bPersistentLines, float LifeTime, bool bDepthIsForeground)
{
	return (InWorld ? (bDepthIsForeground ? InWorld->ForegroundLineBatcher : ((bPersistentLines || (LifeTime > 0.f)) ? InWorld->PersistentLineBatcher : InWorld->LineBatcher)) : NULL);
}

float DebugAPI::GetDebugLineLifeTime(ULineBatchComponent* LineBatcher, float LifeTime, bool bPersistent)
{
	return bPersistent ? -1.0f : ((LifeTime > 0.f) ? LifeTime : LineBatcher->DefaultLifeTime);
}

void DebugAPI::DrawRadial(const UWorld* _InWorld, const FMatrix& _TransformMatrix, float _Radius, float _Angle, const FColor& _Color, int32 _Segments, float _LifeTime, bool _bPersistentLines, uint8 _DepthPriority, float _Thickness)
{// no debug line drawing on dedicated server
	if (GEngine->GetNetMode(_InWorld) != NM_DedicatedServer)
	{
		ULineBatchComponent* const LineBatcher = GetDebugLineBatcher(_InWorld, _bPersistentLines, _LifeTime, (_DepthPriority == SDPG_Foreground));
		if (LineBatcher != NULL)
		{
			const float LineLifeTime = GetDebugLineLifeTime(LineBatcher, _LifeTime, _bPersistentLines);

			// Need at least 4 segments
			float Segments = FMath::Max(_Segments, 4);
			const float AngleStep = FMath::DegreesToRadians(_Angle) / float(Segments);

			const FVector Center = _TransformMatrix.GetOrigin();
			const FVector AxisY = _TransformMatrix.GetScaledAxis(EAxis::Y);
			const FVector AxisX = _TransformMatrix.GetScaledAxis(EAxis::X);

			TArray<FBatchedLine> Lines;
			Lines.Empty(Segments);

			float StartAngle = FMath::DegreesToRadians(90.0f - _Angle / 2.0f);
			float EndAngle = FMath::DegreesToRadians(_Angle);

			float Angle = StartAngle;
			while (Segments--)
			{
				const FVector Vertex1 = Center + _Radius * (AxisY * FMath::Cos(Angle) + AxisX * FMath::Sin(Angle));
				Angle += AngleStep;
				const FVector Vertex2 = Center + _Radius * (AxisY * FMath::Cos(Angle) + AxisX * FMath::Sin(Angle));
				Lines.Add(FBatchedLine(Vertex1, Vertex2, _Color, LineLifeTime, _Thickness, _DepthPriority));
			}
			FVector FirsetVertex = Lines[0].Start;
			FVector LastVertext = Lines.Last().End;

			Lines.Add(FBatchedLine(Center, FirsetVertex, _Color, LineLifeTime, _Thickness, _DepthPriority));
			Lines.Add(FBatchedLine(Center, LastVertext, _Color, LineLifeTime, _Thickness, _DepthPriority));

			LineBatcher->DrawLines(Lines);
		}
	}
}
