#ifndef PARAMETRIC_METHOD_H
#define PARAMETRIC_METHOD_H
/*============================================================================*/
#include <climits>
/*============================================================================*/
#include <SimplexMethod/SimplexTable.h>
/*============================================================================*/
enum Range:
  long long
{
  MIN = LLONG_MIN,
  MAX = LLONG_MAX
};
/*============================================================================*/
struct Interval
{
  long long min;
  long long max;
};
/*============================================================================*/
class ParametricMethod
{
private:
  SimplexTable _table;
  Interval _interval;
public:
  ParametricMethod(
    const SimplexTable& table,
    const Interval& interval = { MIN, MAX });
};
/*============================================================================*/
#endif // PARAMETRIC_METHOD_H