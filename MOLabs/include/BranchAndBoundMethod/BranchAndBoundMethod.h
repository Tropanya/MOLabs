#ifndef BRANCH_AND_BOUND_METHOD_H
#define BRANCH_AND_BOUND_METHOD_H
/*============================================================================*/
#include <SimplexMethod/SimplexTable.h>
/*============================================================================*/
enum BranchType
{
  LEFT = 0,
  RIGHT = 1
};
/*============================================================================*/
class BranchAndBoundMethod
{
private:
  VarIndices _intSolutionVars;
  SimplexTable _table;
private:
  unsigned int _findResolutionIndex(
    const SimplexTable& table) const;
  void _addRow(
    SimplexTable& destTable,
    const SimplexTable& rootTable,
    BranchType type,
    unsigned int index);
  SimplexTable _computeBranches(
    const SimplexTable& rootTable);
public:
  BranchAndBoundMethod(
    const SimplexTable& table);

  void Compute();
};
/*============================================================================*/
#endif // BRANCH_AND_BOUND_METHOD_H