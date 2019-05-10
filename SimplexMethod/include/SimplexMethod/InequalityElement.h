#ifndef INEQUALITY_ELEMENT_H
#define INEQUALITY_ELEMENT_H
/*============================================================================*/
#include <SimplexMethod/InequalitySignType.h>
#include <SimplexMethod/SimplexTableElement.h>
/*============================================================================*/
class InequalityElement:
  public SimplexTableElement
{
private:
  InequalitySignType::InequalitySignType _type;
private:
  void _toCanonical() override;
public:
  InequalityElement(
    const std::vector<mpq_class>& data,
    InequalitySignType::InequalitySignType type);
};
/*============================================================================*/
#endif // INEQUALITY_ELEMENT_H