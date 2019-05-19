#ifndef BRANCH_AND_BOUND_METHOD_H
#define BRANCH_AND_BOUND_METHOD_H
/*============================================================================*/
#include <SimplexMethod/SimplexTable.h>
/*============================================================================*/
class BranchAndBoundMethod
{
private:
  VarIndices _intSolutionVars;
  SimplexTable _table;
private:
  bool _isOptimalSolution() const;
public:
  BranchAndBoundMethod(
    const SimplexTable& table);

  void Compute();

  const SimplexTable& GetTable() const { return _table; }
};
/*============================================================================*/
#endif // BRANCH_AND_BOUND_METHOD_H