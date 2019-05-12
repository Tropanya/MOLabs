#ifndef GOMORY_ALGORITHM_H
#define GOMORY_ALGORITHM_H
/*============================================================================*/
#include <SimplexMethod/SimplexTable.h>
/*============================================================================*/
class GomoryAlgorithm
{
private:
  bool _isOptimal;
  mutable bool _isExistSolution;
protected:
  std::vector<unsigned int> _intSolutionVars;
  SimplexTable _table;
private:
  virtual void _createAdditionalRestriction(
    unsigned int index) = 0;

  unsigned int _findResolutionIndex() const;
  ResolutionElement _getResolutionElement() const;
  bool _isOptimalSolution() const;
protected:
  GomoryAlgorithm(
    const SimplexTable& table);
public:
  void Compute();

  const SimplexTable& GetTable() const { return _table; }
  inline bool IsOptimal() const { return _isOptimal; }
  inline bool IsExistSolution() const { return _isExistSolution; }
};
/*============================================================================*/
#endif // GOMORY_ALGORITHM_H