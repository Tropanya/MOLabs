#include <SimplexMethod/SimplexTable.h>
#include <GomoryAlgorithm/FirstGomoryAlgorithm.h>
#include <GomoryAlgorithm/SecondGomoryAlgorithm.h>
#include <BranchAndBoundMethod/BranchAndBoundMethod.h>
#include <ParametricMethod/ParametricMethod.h>
#include <SimplexMethod/Utils.h>
/*============================================================================*/
#include <iostream>
/*============================================================================*/
int main()
{
  std::vector<SimplexTableRow*> data;
  std::vector<Point> points =
  {
    { Element({ 0 }), Element({ 83, 10 }) },
    { Element({ 113, 10 }), Element({ 172, 10 }) },
    { Element({ 83, 10 }), Element({ 0 }) }
  };

  data = CreateSimplexTableDataFromPoints(
    data, points, { Element({ 8 }), Element({ 1 }) },
    { Element({ 1 }), Element({ 5 }) }, { Element({ 3 }), Element({ 1 }) }, TargetType::MAX);

  //std::vector<Point> points =
  //{
  //  { Element({ 76, 10 }), Element({ 0 }) },
  //  { Element({ 0 }), Element({ 51, 10 }) },
  //  { Element({ 121, 10 }), Element({ 91, 10 }) },
  //  { Element({ 171, 10 }), Element({ 0 }) }
  //};

  //data = CreateSimplexTableDataFromPoints(
  //  data, points, { Element({ 8 }), Element({ 1 }) },
  //  { Element({ 3 }), Element({ 8 }) }, { Element({ 2 }), Element({ 1 }) }, TargetType::MAX);

  SimplexTable table(2, data.size() - 1, data);

  std::cout << "First Gomory:\n";
  GomoryAlgorithm* firstGomory = new FirstGomoryAlgorithm(table);
  firstGomory->Compute();
  std::cout << "\n";

  std::cout << "Second Gomory:\n";
  GomoryAlgorithm* secondGomory = new SecondGomoryAlgorithm({ 0, 1 }, table);
  secondGomory->Compute();
  std::cout << "\n";

  std::cout << "Branch and bound method:\n";
  BranchAndBoundMethod branchAndBound(table);
  branchAndBound.Compute();
  std::cout << "\n";

  std::vector<SimplexTableRow*> data2;
  std::vector<Point> points2 =
  {
    { Element({ 0 }), Element({ 83, 10 }) },
    { Element({ 113, 10 }), Element({ 172, 10 }) },
    { Element({ 83, 10 }), Element({ 0 }) }
  };

  data2 = CreateSimplexTableDataFromPoints(data2, points2, { Element({ 8 }), Element({ 1 }) });
  data2.emplace_back(new SimplexTableRow({ Element({ 4 }),  Element({ 2 },{ -1 }),  Element({ 0 }) }));

  std::cout << "Parametric method:\n";
  SimplexTable table2(2, data2.size() - 1, data2);
  ParametricMethod parametricMethod(table2, { 2, 10 });
  parametricMethod.Compute();
  std::cout << "\n";

  return 0;
}
/*============================================================================*/