#ifndef FIRST_GOMORY_ALGORITHM_H
#define FIRST_GOMORY_ALGORITHM_H
/*============================================================================*/
#include <GomoryAlgorithm/GomoryAlgorithm.h>
/*============================================================================*/
class FirstGomoryAlgorithm:
  public GomoryAlgorithm
{
private:
  void _createAdditionalRestriction(
    unsigned int index) override;
public:
  FirstGomoryAlgorithm(
    const SimplexTable& table);
};
/*============================================================================*/
#endif // FIRST_GOMORY_ALGORITHM_H