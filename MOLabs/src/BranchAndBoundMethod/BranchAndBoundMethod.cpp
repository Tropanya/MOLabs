#include "BranchAndBoundMethod/BranchAndBoundMethod.h"
/*============================================================================*/
#include <SimplexMethod/Utils.h>
/*============================================================================*/
#include <iostream>
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

      if (1 != table.GetData()[tmpIndex].back().GetFree().get_den())
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
  SimplexTableRowData data(rootTable.GetData().back().size());

  switch (type)
  {
    case LEFT:
    {
      data[rootTable.GetBasic()[index]] = Element(1);
      data.back() = Element(
        GetTotalPart(rootTable.GetData()[index].back().GetFree()));
      destTable.AddRow(&(SimplexTableRow(data)));
    }
    break;

    case RIGHT:
    {
      data[rootTable.GetBasic()[index]] = Element(-1);
      data.back() = Element(-1) * (Element(
        GetTotalPart(
          rootTable.GetData()[index].back().GetFree())) + Element(1));
      destTable.AddRow(&(SimplexTableRow(data)));
    }
    break;
  }
}
/*============================================================================*/
SimplexTable BranchAndBoundMethod::_computeBranches(
  const SimplexTable& rootTable)
{
  std::cout << "Root table:\n" << rootTable << std::endl;
  SimplexTable res = rootTable;
  res.Rebuild(false);

  if (!res.isIntSolution())
  {
    unsigned int index = _findResolutionIndex(res);

    SimplexTable left = rootTable;
    _addRow(left, res, LEFT, index);
    SimplexTable leftRoot = left;
    std::cout << "Left branch:\n";
    std::cout << leftRoot << std::endl;

    SimplexTable right = rootTable;
    _addRow(right, res, RIGHT, index);
    SimplexTable rightRoot = right;
    std::cout << "Right branch:\n";
    std::cout << rightRoot << std::endl;

    left.Rebuild(false);
    right.Rebuild(false);

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
      std::cout << "[Left branch] Not exist solution.\n";
      if (right.isIntSolution())
        res = right;
      else
        res = _computeBranches(rightRoot);
    }
    else if (!right.isExistSolution())
    {
      std::cout << "[Right branch] Not exist solution.\n";
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

  std::cout << _table << std::endl;
}
/*============================================================================*/