#include "BranchAndBoundMethod/BranchAndBoundMethod.h"
/*============================================================================*/
#include <SimplexMethod/Utils.h>
#include <iostream>
/*============================================================================*/
BranchAndBoundMethod::BranchAndBoundMethod(
  const SimplexTable& table):
  _table(table)
{
  for (unsigned int i = 0; i < _table.GetSolutionVars().size(); ++i)
    _intSolutionVars.emplace_back(i);
}
/*============================================================================*/
bool BranchAndBoundMethod::_isOptimalSolution() const
{
  bool res = true;

  for (unsigned int i = 0; i < _intSolutionVars.size(); ++i)
    if (1 != _table.GetSolutionVars()[_intSolutionVars[i]].get_den())
      res &= false;

  return res;
}
/*============================================================================*/
void BranchAndBoundMethod::Compute()
{
  SimplexTable tmpTable = _table;
  _table.Rebuild();
  SimplexTable left = tmpTable;
  SimplexTable right = tmpTable;

  left.AddRaw(&(SimplexTableElement(
    { mpq_class(1), mpq_class(0), GetTotalPart(_table.GetData()[1].back()) })));
  right.AddRaw(&(SimplexTableElement(
    { mpq_class(-1), mpq_class(0),
      mpq_class(-1) * (GetTotalPart(_table.GetData()[1].back()) + mpq_class(1)) })));

  SimplexTable tmpLeft = left;
  SimplexTable tmpRight = right;

  std::cout << left << std::endl;
  left.Rebuild();
  std::cout << left << std::endl;
  right.Rebuild();
  std::cout << right << std::endl;

  tmpRight = tmpLeft;

  tmpLeft.AddRaw(&(SimplexTableElement(
    { mpq_class(0), mpq_class(1), GetTotalPart(left.GetData()[2].back()) })));
  tmpRight.AddRaw(&(SimplexTableElement(
    { mpq_class(0), mpq_class(-1),
      mpq_class(-1) * (GetTotalPart(left.GetData()[2].back()) + mpq_class(1)) })));

  left = tmpLeft;
  right = tmpRight;

  std::cout << left << std::endl;
  left.Rebuild();
  std::cout << left << std::endl;
  right.Rebuild();
  std::cout << right << std::endl;
}
/*============================================================================*/