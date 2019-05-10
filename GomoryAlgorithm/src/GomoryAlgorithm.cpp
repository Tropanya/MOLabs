#include "GomoryAlgorithm/GomoryAlgorithm.h"
/*============================================================================*/
#include <SimplexMethod/Utils.h>
/*============================================================================*/
GomoryAlgorithm::GomoryAlgorithm(
  SimplexTable& table)
{
  table.InvertRaw(table.GetData().size() - 1);

  while (!_isOptimalSolution(table))
  {
    unsigned int index = 0;
    mpq_class cmpVal = GetProperFraction(table.GetData()[index].back());

    for (unsigned int i = 0; i < table.GetVariableCount(); ++i)
      if (GetProperFraction(table.GetData()[i].back()) > cmpVal)
        index = i;

    _createAdditionalRestriction(index, table);
    table.RebuildTable(_getResolutionElement(table));
  }
}
/*============================================================================*/
void GomoryAlgorithm::_createAdditionalRestriction(
  unsigned int index,
  SimplexTable& table) const
{
  const std::vector<mpq_class>& raw = table.GetRaw(index);

  std::vector<mpq_class> elementData;
  elementData.resize(raw.size());

  for (unsigned int i = 0; i < elementData.size() - 1; ++i)
  {
    if (raw[i] < mpq_class(0))
      elementData[i] = mpq_class(-1) *
        (GetProperFraction(raw[i]) - (GetTotalPart(raw[i]) - mpq_class(1)));
    else
      elementData[i] = mpq_class(-1) * GetProperFraction(raw[i]);
  }

  elementData.back() = mpq_class(-1) * GetProperFraction(raw.back());

  table.AddRaw(&(SimplexTableElement(elementData)));
}
/*============================================================================*/
ResolutionElement GomoryAlgorithm::_getResolutionElement(
  const SimplexTable& table) const
{
  ResolutionElement res;
  res.horIndex = 0;
  res.vertIndex = table.GetBasic().size() - 1;
  res.resolutionVal = mpq_class(-1);

  mpq_class cmpVal(0);
  bool isFirst = true;

  for (unsigned int i = 0; i < table.GetData()[res.vertIndex].size() - 1; ++i)
  {
    cmpVal = table.GetData().back()[i] / table.GetData()[res.vertIndex][i];

    if (isFirst)
    {
      res.horIndex = i;
      res.resolutionVal = cmpVal;
      isFirst = false;
    }
    else
    {
      if (cmpVal <= res.resolutionVal)
      {
        res.horIndex = i;
        res.resolutionVal = cmpVal;
      }
    }
  }

  res.resolutionVal = table.GetData()[res.vertIndex][res.horIndex];

  return res;
}
/*============================================================================*/
bool GomoryAlgorithm::_isOptimalSolution(
  const SimplexTable& table) const
{
  bool res = true;

  for (unsigned int i = 0; i < table.GetVariableCount(); ++i)
    if (1 != table.GetSolutionVars()[i].get_den())
      res &= false;

  return res;
}
/*============================================================================*/