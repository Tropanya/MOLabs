#include "GomoryAlgorithm/GomoryAlgorithm.h"
/*============================================================================*/
#include <SimplexMethod/Utils.h>
/*============================================================================*/
#include <cassert>
#include <iostream>
/*============================================================================*/
GomoryAlgorithm::GomoryAlgorithm(
  const SimplexTable& table):
  _table(table),
  _isExistSolution(true)
{  }
/*============================================================================*/
unsigned int GomoryAlgorithm::_findResolutionIndex() const
{
  unsigned int resIndex = 0;
  mpq_class cmpVal(0);
  bool isFirst = true;

  for (unsigned int i = 0; i < _table.GetRestrictionCount(); ++i)
  {
    auto it = std::find(
      _intSolutionVars.begin(), _intSolutionVars.end(), _table.GetBasic()[i]);

    if (it != _intSolutionVars.end())
    {
      if (1 != _table.GetData()[i].back().get_den())
      {
        if (isFirst)
        {
          resIndex = i;
          isFirst = false;
        }
        else
        {
          if (abs(GetProperFraction(_table.GetData()[i].back())) >
              abs(GetProperFraction(_table.GetData()[resIndex].back())))
            resIndex = i;
        }
      }
    }
  }

  return resIndex;
}
/*============================================================================*/
ResolutionElement GomoryAlgorithm::_getResolutionElement() const
{
  ResolutionElement res;
  res.horIndex = 0;
  res.vertIndex = _table.GetBasic().size() - 1;
  res.resolutionVal = mpq_class(-1);

  mpq_class cmpVal(0);
  bool isFirst = true;
  bool find = false;

  for (unsigned int i = 0; i < _table.GetData()[res.vertIndex].size() - 1; ++i)
  {
    if (_table.GetData()[res.vertIndex][i] != mpq_class(0))
      cmpVal = _table.GetData().back()[i] / _table.GetData()[res.vertIndex][i];
    else
      break;

    if (isFirst)
    {
      res.horIndex = i;
      res.resolutionVal = cmpVal;
      isFirst = false;
      find = true;
    }
    else
    {
      if (cmpVal < res.resolutionVal)
      {
        res.horIndex = i;
        res.resolutionVal = cmpVal;
        find = true;
      }
    }
  }

  if (find)
    res.resolutionVal = _table.GetData()[res.vertIndex][res.horIndex];
  else
  {
    std::cout << "Could not find resolution element.\n";
    _isExistSolution = false;
  }

  return res;
}
/*============================================================================*/
bool GomoryAlgorithm::_isOptimalSolution() const
{
  bool res = true;

  for (unsigned int i = 0; i < _intSolutionVars.size(); ++i)
    if (1 != _table.GetSolutionVars()[_intSolutionVars[i]].get_den())
      res &= false;

  return res;
}
/*============================================================================*/
void GomoryAlgorithm::Compute()
{
  ResolutionElement resElem;

  _table.InvertRaw(_table.GetData().size() - 1);

  while (!_isOptimalSolution())
  {
    unsigned int index = 0;
    index = _findResolutionIndex();

    _createAdditionalRestriction(index);

    resElem = _getResolutionElement();
    if (_isExistSolution)
      _table.RebuildTable(resElem);
    else
      break;
  }

  _isOptimal = _isOptimalSolution();
}
/*============================================================================*/