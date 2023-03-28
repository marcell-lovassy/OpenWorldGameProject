#pragma once

#include "DrawDebugHelpers.h"

#define DRAW_DEBUG_SPHERE(location) if(GetWorld()) DrawDebugSphere(GetWorld(), location, 30, 12, FColor::Red);
#define DRAW_DEBUG_LINE(startLocation, endLocation) if(GetWorld()) DrawDebugLine(GetWorld(), startLocation, endLocation, FColor::Red, true, -1.f, 0, 1.f);
#define DRAW_DEBUG_POINT(location) if(GetWorld()) DrawDebugPoint(GetWorld(), location, 15.f, FColor::Green, true);
#define DRAW_VECTOR(startLocation, endLocation) if(GetWorld()) \
	{ \
		DrawDebugLine(GetWorld(), startLocation, endLocation, FColor::Red, true, -1.f, 0, 1.f); \
		DrawDebugPoint(GetWorld(), endLocation, 15.f, FColor::Green, true); \
	}