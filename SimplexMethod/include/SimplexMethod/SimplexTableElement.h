#ifndef SIMPLEX_TABLE_ELEMENT_H
#define SIMPLEX_TABLE_ELEMENT_H
/*============================================================================*/
#include <mpir.h>
#include <mpirxx.h>
/*============================================================================*/
#include <vector>
/*============================================================================*/
typedef std::vector<mpq_class> SimplexTableElementData;
/*============================================================================*/
class SimplexTableElement
{
protected:
  SimplexTableElementData _data;
private:
  virtual void _toCanonical() = 0;
protected:
  SimplexTableElement(const SimplexTableElementData& data);
public:
  virtual ~SimplexTableElement();
  inline const SimplexTableElementData& GetData() const { return _data; }
};
/*============================================================================*/
#endif // SIMPLEX_TABLE_ELEMENT_H