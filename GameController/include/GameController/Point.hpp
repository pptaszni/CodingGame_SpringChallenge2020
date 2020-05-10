#pragma once

namespace codingame
{
namespace gamecontroller
{

struct Point
{
  int x;
  int y;
};

inline int distance(const Point& p1, const Point& p2)
{
  return (p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y);
}

}  // namespace gamecontroller
}  // namespace codingame
