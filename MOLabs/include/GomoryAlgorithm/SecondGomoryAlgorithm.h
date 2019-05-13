#ifndef SECOND_GOMORY_ALGORITHM_H
#define SECOND_GOMORY_ALGORITHM_H
/*============================================================================*/
#include <GomoryAlgorithm/GomoryAlgorithm.h>
/*============================================================================*/
class SecondGomoryAlgorithm:
  public GomoryAlgorithm
{
private:
  void _createAdditionalRestriction(
    unsigned int index) override;
public:
  SecondGomoryAlgorithm(
    const VarIndices& intSolutionVars,
    const SimplexTable& table);
};
/*============================================================================*/
#endif // SECOND_GOMORY_ALGORITHM_H