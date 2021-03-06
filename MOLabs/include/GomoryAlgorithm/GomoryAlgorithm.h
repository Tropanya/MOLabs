#ifndef GOMORY_ALGORITHM_H
#define GOMORY_ALGORITHM_H
/*============================================================================*/
#include <SimplexMethod/SimplexTable.h>
/*============================================================================*/
class GomoryAlgorithm
{
protected:
  VarIndices _intSolutionVars;
  SimplexTable _table;
private:
  virtual void _createAdditionalRestriction(
    unsigned int index) = 0;

  unsigned int _findResolutionIndex() const;
  bool _isIntSolution() const;
protected:
  GomoryAlgorithm(
    const SimplexTable& table);
public:
  virtual ~GomoryAlgorithm();

  void Compute();
};
/*============================================================================*/
#endif // GOMORY_ALGORITHM_H