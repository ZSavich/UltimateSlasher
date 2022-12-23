#pragma once

#define DRAW_SPHERE(Location, Color) if (const auto World = GetWorld()) \
	DrawDebugSphere(World, Location, 24.f, 12.f, Color, true, -1, 0, 1.f);

#define DRAW_LINE(StartLocation, EndLocation) if (const auto World = GetWorld()) \
	DrawDebugLine(World, StartLocation, EndLocation, FColor::Red, true, -1, 0, 1.f);

#define DRAW_POINT(Location) if (const auto World = GetWorld()) \
	DrawDebugPoint(World, Location, 12.f, FColor::Red, true);

#define DRAW_VECTOR(StartLocation, EndLocation) if (const auto World = GetWorld()) \
	{ \
		DrawDebugLine(World, StartLocation, EndLocation, FColor::Blue, true, -1, 0, 1.f); \
		DrawDebugPoint(World, EndLocation, 12.f, FColor::Blue, true); \
	};

#define DRAW_BOX(Location) if (const auto World = GetWorld()) \
	DrawDebugBox(World, Location, FVector(15.f), FColor::Yellow, true);