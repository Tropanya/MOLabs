#include "GomoryAlgorithm/GomoryAlgorithm.h"
/*============================================================================*/
#include <SimplexMethod/Utils.h>
/*============================================================================*/
#include <iostream>
/*============================================================================*/
GomoryAlgorithm::GomoryAlgorithm(
  const SimplexTable& table):
  _table(table)
{  }
/*============================================================================*/
unsigned int GomoryAlgorithm::_findResolutionIndex() const
{
  unsigned int resIndex = 0;
  mpq_class cmpVal(0);
  bool isFirst = true;

  for (unsigned int i = 0; i < _table.GetRestrictionCount(); ++i)
  {
    auto it = std::find(_intSolutionVars.begin(), _intSolutionVars.end(),
                        _table.GetBasic()[i]);

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
          if (GetProperFraction(_table.GetData()[i].back()) >
              GetProperFraction(_table.GetData()[resIndex].back()))
            resIndex = i;
        }
      }
    }
  }

  return resIndex;
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
  _table.InvertRaw(_table.GetData().size() - 1);

  while (!_isOptimalSolution())
  {
    unsigned int index = 0;
    index = _findResolutionIndex();
    _createAdditionalRestriction(index);

    _table.DualSimplexMethod();
  }
}
/*============================================================================*/