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
  virtual void _toCanonical() {  };
public:
  SimplexTableElement(const SimplexTableElementData& data);
  virtual ~SimplexTableElement();

  inline const SimplexTableElementData& GetData() const { return _data; }
};
/*============================================================================*/
#endif // SIMPLEX_TABLE_ELEMENT_H