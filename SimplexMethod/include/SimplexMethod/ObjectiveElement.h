#ifndef OBJECTIVE_ELEMENT_H
#define OBJECTIVE_ELEMENT_H
/*============================================================================*/
#include <SimplexMethod/ObjectiveElementType.h>
#include <SimplexMethod/SimplexTableElement.h>
/*============================================================================*/
class ObjectiveElement:
  public SimplexTableElement
{
private:
  ObjectiveElementType::ObjectiveElementType _type;
private:
  void _toCanonical() override;
public:
  ObjectiveElement(
    const std::vector<mpq_class>& data,
    ObjectiveElementType::ObjectiveElementType type);
};
/*============================================================================*/
#endif // OBJECTIVE_ELEMENT_H