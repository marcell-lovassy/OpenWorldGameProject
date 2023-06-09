#pragma once

#include "DrawDebugHelpers.h"

#define DRAW_DEBUG_SPHERE(location) if(GetWorld()) DrawDebugSphere(GetWorld(), location, 30, 12, FColor::Red, true, -1);
#define DRAW_DEBUG_SPHERE_TIME(location, color, time) if(GetWorld()) DrawDebugSphere(GetWorld(), location, 10.f, 12, color, false, time);
#define DRAW_DEBUG_SPHERE_SINGLE_FRAME(location) if(GetWorld()) DrawDebugSphere(GetWorld(), location, 30, 12, FColor::Red, false, -1);
#define DRAW_DEBUG_LINE(startLocation, endLocation) if(GetWorld()) DrawDebugLine(GetWorld(), startLocation, endLocation, FColor::Red, true, -1.f, 0, 1.f);
#define DRAW_DEBUG_LINE_SINGLE_FRAME(startLocation, endLocation) if(GetWorld()) DrawDebugLine(GetWorld(), startLocation, endLocation, FColor::Red, false, -1.f, 0, 1.f);
#define DRAW_DEBUG_POINT(location) if(GetWorld()) DrawDebugPoint(GetWorld(), location, 15.f, FColor::Green, true);
#define DRAW_DEBUG_POINT_SINGLE_FRAME(location) if(GetWorld()) DrawDebugPoint(GetWorld(), location, 15.f, FColor::Green, false, -1);
#define DRAW_VECTOR(startLocation, endLocation) if(GetWorld()) \
	{ \
		DrawDebugLine(GetWorld(), startLocation, endLocation, FColor::Red, true, -1.f, 0, 1.f); \
		DrawDebugPoint(GetWorld(), endLocation, 15.f, FColor::Green, true); \
	}
#define DRAW_VECTOR_SINGLE_FRAME(startLocation, endLocation) if(GetWorld()) \
	{ \
		DrawDebugLine(GetWorld(), startLocation, endLocation, FColor::Red, false, -1.f, 0, 1.f); \
		DrawDebugPoint(GetWorld(), endLocation, 15.f, FColor::Green, false, -1); \
	}