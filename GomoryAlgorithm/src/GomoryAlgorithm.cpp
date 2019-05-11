#include "GomoryAlgorithm/GomoryAlgorithm.h"
/*============================================================================*/
#include <SimplexMethod/Utils.h>
/*============================================================================*/
#include <cassert>
#include <iostream>
/*============================================================================*/
GomoryAlgorithm::GomoryAlgorithm(
  const SimplexTable& table):
  _table(table)
{
  _table.InvertRaw(_table.GetData().size() - 1);

  while (!_isOptimalSolution())
  {
    unsigned int index = 0;
    index = _findResolutionIndex();

    _createAdditionalRestriction(index);
    _table.RebuildTable(_getResolutionElement());
  }
}
/*============================================================================*/
unsigned int GomoryAlgorithm::_findResolutionIndex()
{
  unsigned int resIndex = 0;
  mpq_class cmpVal(0);
  bool isFirst = true;

  for (unsigned int i = 0; i < _table.GetSolutionVars().size(); ++i)
  {
    if (1 != _table.GetSolutionVars()[i].get_den())
    {
      if (isFirst)
      {
        resIndex = i;
        cmpVal = abs(GetProperFraction(_table.GetSolutionVars()[i]));
        isFirst = false;
      }
      else
      {
        if (abs(GetProperFraction(_table.GetSolutionVars()[i])) >
          abs(GetProperFraction(_table.GetSolutionVars()[resIndex])))
          resIndex = i;
      }
    }
  }

  auto it = std::find(
    _table.GetBasic().begin(), _table.GetBasic().end(), resIndex);

  if (it != _table.GetBasic().end())
    resIndex = std::distance(_table.GetBasic().begin(), it);
  else
    assert(false);

  return resIndex;
}
/*============================================================================*/
void GomoryAlgorithm::_createAdditionalRestriction(
  unsigned int index)
{
  const std::vector<mpq_class>& raw = _table.GetRaw(index);

  std::vector<mpq_class> elementData;
  elementData.resize(raw.size());

  for (unsigned int i = 0; i < elementData.size() - 1; ++i)
  {
    if (raw[i] < mpq_class(0))
      elementData[i] =
        mpq_class(-1) * (raw[i] - (GetTotalPart(raw[i]) - mpq_class(1)));
    else
      elementData[i] = mpq_class(-1) * GetProperFraction(raw[i]);
  }

  elementData.back() = mpq_class(-1) * GetProperFraction(raw.back());

  _table.AddRaw(&(SimplexTableElement(elementData)));
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
    assert(false);
  }

  return res;
}
/*============================================================================*/
bool GomoryAlgorithm::_isOptimalSolution() const
{
  bool res = true;

  for (unsigned int i = 0; i < _table.GetVariableCount(); ++i)
    if (1 != _table.GetSolutionVars()[i].get_den())
      res &= false;

  return res;
}
/*============================================================================*/