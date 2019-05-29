#include <SimplexMethod/SimplexTable.h>
#include <GomoryAlgorithm/FirstGomoryAlgorithm.h>
#include <GomoryAlgorithm/SecondGomoryAlgorithm.h>
#include <BranchAndBoundMethod/BranchAndBoundMethod.h>
#include <SimplexMethod/Utils.h>
/*============================================================================*/
#include <iostream>
#include <fstream>
/*============================================================================*/
int main()
{
  std::vector<SimplexTableRow*> data;
  std::vector<Point> points =
  {
    { Element(0), Element(83, 10) },
    { Element(113, 10), Element(172, 10) },
    { Element(83, 10), Element(0) },
    { Element(1), Element(5) },
    { Element(3), Element(1) }
  };

  //std::vector<Point> points =
  //{
  //  { Element(76, 10), Element(0) },
  //  { Element(0), Element(51, 10) },
  //  { Element(121, 10), Element(91, 10) },
  //  { Element(171, 10), Element(0) },
  //  { Element(2), Element(1) },
  //  { Element(3), Element(8) }
  //};

  //std::vector<SimplexTableElement*> data =
  //{
  //  new SimplexTableElement({ Element(5), Element(7), Element(21) }),
  //  new SimplexTableElement({ Element(-1), Element(3), Element(8) }),
  //  new SimplexTableElement({ Element(1), Element(2), Element(0) }),
  //};

  //std::vector<SimplexTableElement*> data =
  //{
  //  new SimplexTableElement({ Element(2), Element(4), Element(7) }),
  //  new SimplexTableElement({ Element(4), Element(-5), Element(9) }),
  //  new SimplexTableElement({ Element(1), Element(2), Element(0) }),
  //};

  //std::vector<SimplexTableElement*> data =
  //{
  //  new SimplexTableElement({ Element(1), Element(2), Element(3), Element(35) }),
  //  new SimplexTableElement({ Element(4), Element(3), Element(2), Element(45) }),
  //  new SimplexTableElement({ Element(3), Element(1), Element(1), Element(40) }),
  //  new SimplexTableElement({ Element(4), Element(5), Element(6), Element(0) })
  //};

  std::ofstream file("output.txt");

  data = CreateSimplexTableDataFromPoints(data, points);

  SimplexTable table(2, 3, data);
  std::cout << table << std::endl;
  table.Rebuild();
  std::cout << table << std::endl;

  std::cout << "First Gomory:\n";
  GomoryAlgorithm* firstGomory = new FirstGomoryAlgorithm(table);
  firstGomory->Compute();
  std::cout << firstGomory->GetTable() << std::endl;

  std::cout << "Second Gomory:\n";
  GomoryAlgorithm* secondGomory = new SecondGomoryAlgorithm({ 0, 1 }, table);
  secondGomory->Compute();
  std::cout << secondGomory->GetTable() << std::endl;

  std::cout << "Branch and bound method:\n";
  SimplexTable table2(2, 3, data);
  BranchAndBoundMethod branchAndBound(table2);
  branchAndBound.Compute();
  std::cout << branchAndBound.GetTable() << std::endl;

  return 0;
}
/*============================================================================*/