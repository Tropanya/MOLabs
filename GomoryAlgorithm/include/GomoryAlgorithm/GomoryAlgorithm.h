#ifndef GOMORY_ALGORITHM_H
#define GOMORY_ALGORITHM_H
/*============================================================================*/
#include <SimplexMethod/SimplexTable.h>
/*============================================================================*/
class GomoryAlgorithm
{
private:
  void _createAdditionalRestriction(
    unsigned int index,
    SimplexTable& table) const;
  ResolutionElement _getResolutionElement(
    const SimplexTable& table) const;
  bool _isOptimalSolution(
    const SimplexTable& table) const;
public:
  GomoryAlgorithm(
    SimplexTable& table);
};
/*============================================================================*/
#endif // GOMORY_ALGORITHM_H