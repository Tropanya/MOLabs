#include "BranchAndBoundMethod/BranchAndBoundMethod.h"
/*============================================================================*/
#include <SimplexMethod/Utils.h>
/*============================================================================*/
BranchAndBoundMethod::BranchAndBoundMethod(
  const SimplexTable& table):
  _table(table)
{
  for (std::size_t i = 0; i < _table.GetSolutionVars().size(); ++i)
    _intSolutionVars.emplace_back(i);
}
/*============================================================================*/
unsigned int BranchAndBoundMethod::_findResolutionIndex(
  const SimplexTable& table) const
{
  for (std::size_t i = 0; i < _intSolutionVars.size(); ++i)
  {
    auto it = std::find(table.GetBasic().begin(), table.GetBasic().end(),
                        _intSolutionVars[i]);

    if (it != table.GetBasic().end())
    {
      unsigned int tmpIndex = std::distance(table.GetBasic().begin(), it);

      if (1 != table.GetData()[tmpIndex].back().get_den())
        return tmpIndex;
    }
  }

  return -1;
}
/*============================================================================*/
void BranchAndBoundMethod::_addRow(
  SimplexTable& destTable,
  const SimplexTable& rootTable,
  BranchType type,
  unsigned int index)
{
  SimplexTableElementData data(rootTable.GetData().back().size());

  switch (type)
  {
    case LEFT:
    {
      data[rootTable.GetBasic()[index]] = mpq_class(1);
      data.back() = GetTotalPart(rootTable.GetData()[index].back());
      destTable.AddRow(&(SimplexTableElement(data)));
    }
    break;

    case RIGHT:
    {
      data[rootTable.GetBasic()[index]] = mpq_class(-1);
      data.back() = mpq_class(-1) *
        (GetTotalPart(rootTable.GetData()[index].back()) + mpq_class(1));
      destTable.AddRow(&(SimplexTableElement(data)));
    }
    break;
  }
}
/*============================================================================*/
SimplexTable BranchAndBoundMethod::_computeBranches(
  const SimplexTable& rootTable)
{
  SimplexTable res = rootTable;
  res.Rebuild();

  if (!res.isIntSolution())
  {
    unsigned int index = _findResolutionIndex(res);

    SimplexTable left = rootTable;
    _addRow(left, res, LEFT, index);
    SimplexTable leftRoot = left;

    SimplexTable right = rootTable;
    _addRow(right, res, RIGHT, index);
    SimplexTable rightRoot = right;

    left.Rebuild();
    right.Rebuild();

    if (left.isExistSolution() && right.isExistSolution())
    {
      if (!left.isIntSolution() && !right.isIntSolution())
      {
        if (left.GetData().back().back() >= right.GetData().back().back())
          res = _computeBranches(leftRoot);
        else
          res = _computeBranches(rightRoot);
      }
      else
      {
        if (left.isIntSolution())
        {
          if (left.GetData().back().back() >= right.GetData().back().back())
            res = left;
          else
            res = _computeBranches(rightRoot);
        }
        else if (right.isIntSolution())
        {
          if (right.GetData().back().back() >= left.GetData().back().back())
            res = right;
          else
            res = _computeBranches(leftRoot);
        }
      }
    }
    else if (!left.isExistSolution())
    {
      if (right.isIntSolution())
        res = right;
      else
        res = _computeBranches(rightRoot);
    }
    else if (!right.isExistSolution())
    {
      if (left.isIntSolution())
        res = left;
      else
        res = _computeBranches(leftRoot);
    }
  }

  return res;
}
/*============================================================================*/
void BranchAndBoundMethod::Compute()
{
  _table = _computeBranches(_table);
}
/*============================================================================*/