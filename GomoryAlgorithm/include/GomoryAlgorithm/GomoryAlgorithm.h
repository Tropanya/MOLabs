#ifndef GOMORY_ALGORITHM_H
#define GOMORY_ALGORITHM_H
/*============================================================================*/
#include <SimplexMethod/SimplexTable.h>
/*============================================================================*/
class GomoryAlgorithm
{
private:
  SimplexTable _table;
private:
  unsigned int _findResolutionIndex();
  void _createAdditionalRestriction(
    unsigned int index);
  ResolutionElement _getResolutionElement() const;
  bool _isOptimalSolution() const;
public:
  GomoryAlgorithm(
    const SimplexTable& table);

  const SimplexTable& GetTable() const { return _table; }
};
/*============================================================================*/
#endif // GOMORY_ALGORITHM_H