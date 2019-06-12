#include "GomoryAlgorithm/GomoryAlgorithm.h"
/*============================================================================*/
#include <SimplexMethod/Utils.h>
/*============================================================================*/
#include <iostream>
/*============================================================================*/
GomoryAlgorithm::GomoryAlgorithm(
  const SimplexTable& table):
  _table(table)
{
  std::cout << _table << std::endl;
  _table.Rebuild(true);
  std::cout << _table << std::endl;
}
/*============================================================================*/
GomoryAlgorithm::~GomoryAlgorithm()
{  }
/*============================================================================*/
unsigned int GomoryAlgorithm::_findResolutionIndex() const
{
  unsigned int resIndex = 0;

  bool isFirst = true;
  for (std::size_t i = 0; i < _table.GetRestrictionCount(); ++i)
  {
    auto it = std::find(_intSolutionVars.begin(), _intSolutionVars.end(),
                        _table.GetBasic()[i]);

    if (it != _intSolutionVars.end())
    {
      if (1 != _table.GetData()[i].back().GetFree().get_den())
      {
        if (isFirst)
        {
          resIndex = i;
          isFirst = false;
        }
        else
        {
          if (GetProperFraction(_table.GetData()[i].back().GetFree()) >
              GetProperFraction(_table.GetData()[resIndex].back().GetFree()))
            resIndex = i;
        }
      }
    }
  }

  return resIndex;
}
/*============================================================================*/
void GomoryAlgorithm::Compute()
{
  _table.InvertRow(_table.GetData().size() - 1);

  while (!_table.isIntSolution())
  {
    _createAdditionalRestriction(_findResolutionIndex());
    _table.DualSimplexMethod(true);
  }

  std::cout << _table << std::endl;
}
/*============================================================================*/