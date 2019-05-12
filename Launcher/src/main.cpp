#include <SimplexMethod/SimplexTable.h>
#include <GomoryAlgorithm/GomoryAlgorithm.h>
#include <GomoryAlgorithm/FirstGomoryAlgorithm.h>
#include <SimplexMethod/Utils.h>
/*============================================================================*/
#include <iostream>
/*============================================================================*/
int main()
{
  std::vector<SimplexTableElement*> data;
  std::vector<Point> points =
  {
    { mpq_class(0), mpq_class(83, 10) },
    { mpq_class(113, 10), mpq_class(172, 10) },
    { mpq_class(83, 10), mpq_class(0) },
    { mpq_class(1), mpq_class(5) },
    { mpq_class(3), mpq_class(1) }
  };

  //std::vector<Point> points =
  //{
  //  { mpq_class(76, 10), mpq_class(0) },
  //  { mpq_class(0), mpq_class(51, 10) },
  //  { mpq_class(121, 10), mpq_class(91, 10) },
  //  { mpq_class(171, 10), mpq_class(0) },
  //  { mpq_class(2), mpq_class(1) },
  //  { mpq_class(3), mpq_class(8) }
  //};

  //std::vector<SimplexTableElement*> data =
  //{
  //  new SimplexTableElement({ mpq_class(5), mpq_class(7), mpq_class(21) }),
  //  new SimplexTableElement({ mpq_class(-1), mpq_class(3), mpq_class(8) }),
  //  new SimplexTableElement({ mpq_class(1), mpq_class(2), mpq_class(0) }),
  //};

  //std::vector<SimplexTableElement*> data =
  //{
  //  new SimplexTableElement({ mpq_class(1), mpq_class(2), mpq_class(3), mpq_class(35) }),
  //  new SimplexTableElement({ mpq_class(4), mpq_class(3), mpq_class(2), mpq_class(45) }),
  //  new SimplexTableElement({ mpq_class(3), mpq_class(1), mpq_class(1), mpq_class(40) }),
  //  new SimplexTableElement({ mpq_class(4), mpq_class(5), mpq_class(6), mpq_class(0) })
  //};

  data = CreateSimplexTableDataFromPoints(data, points);

  SimplexTable table(2, 3, data);
  std::cout << table << std::endl;

  GomoryAlgorithm* firstGomory = new FirstGomoryAlgorithm(table);
  firstGomory->Compute();
  std::cout << firstGomory->GetTable() << std::endl;

  return 0;
}
/*============================================================================*/