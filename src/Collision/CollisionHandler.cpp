#include "CollisionHandler.h"

CollisionHandler* CollisionHandler::s_Instance = nullptr;


bool CollisionHandler::CheckCollision(SDL_Rect a, SDL_Rect b)
{
    bool x_overlaps = (a.x < b.x + b.w) && (a.x + a.w > b.x);
    bool y_overlaps = (a.y < b.y + b.h) && (a.y + a.h > b.y);
    return (x_overlaps && y_overlaps);
}

bool CollisionHandler::CheckPointInsideBox(Point2D point, SDL_Rect box)
{
    return (( point.X > box.x ) && ( point.X < box.x + box.w ) && ( point.Y > box.y ) && ( point.Y  < box.y + box.h ) );
}
