
#include "sortmanager.hpp"
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <cstring>
#include <string>

using std::cout;
using std::endl;
using std::out_of_range;
using std::strcmp;
using std::ostringstream;
using std::stoi;


void testSort(int testNum, int& correct, double& bestSortTime, string& bestSortName, string sortName, double baselineTime, double currentTime, double factorFudgeLower, double factorFudgeHigher) {

  if (baselineTime <= 0) {
    cout << "***Failed Test " << testNum << "***" << endl;
    cout << "The " << sortName << " sort did not sort correctly" << endl << endl;
    return;
  }

  double lowRange = baselineTime + baselineTime * factorFudgeLower;
  double highRange = baselineTime + baselineTime * factorFudgeHigher;
  if (currentTime < lowRange || currentTime > highRange) {
    cout << "***Failed Test " << testNum << "***" << endl;
    cout << "The " << sortName << " sort should have run between " << lowRange << " to " << highRange << " milliseconds. It ran in " << currentTime << " milliseconds." << endl << endl;
    return;
  }

  correct++;
  cout << "Passed Test " << testNum << ". " << sortName << " sort " << endl << endl;

  if (currentTime <= bestSortTime || bestSortTime == 0.0) {
    bestSortTime = currentTime;
    bestSortName = sortName;
  }
}

void testSpeedup(int testNum, int& correct, double actualSpeedup, double speedupMinimum, double speedupMaximum) {

  if (actualSpeedup < speedupMinimum || speedupMaximum < actualSpeedup) {

    cout << "***Failed Test " << testNum << "***" << endl;
    cout << "The speedup should have been between " << speedupMinimum << "% to " << speedupMaximum << "%. The speedup was " << actualSpeedup << "%" << endl << endl;
    return;
  }

  correct++;
  cout << "Passed Test " << testNum << endl << endl;
}


int test_PresuppliedSorts() {

  cout << "--------testPresuppliedSorts Tests--------" << endl;

  int testNum = 1;
  int correct = 0;

  double timeToSort = 0.0;

  double baselineTime = 0.0;
  double bestSortTime = 0.0;
  string bestSortName = "";


  baselineTime = runMySort(Bubble<unsigned int>(20000));
  testSort(testNum++, correct, bestSortTime, bestSortName, "Bubble", baselineTime, baselineTime, 0.0, 0.0); // 1

  timeToSort = runMySort(Selection<unsigned int>(20000));
  testSort(testNum++, correct, bestSortTime, bestSortName, "Selection", baselineTime, timeToSort, -0.5, 0.5); // 2

  // Due to speculative execution, Insertion Sort is typically faster than Bubble.
  timeToSort = runMySort(Insertion<unsigned int>(20000));
  testSort(testNum++, correct, bestSortTime, bestSortName, "Insertion", baselineTime, timeToSort, -2, 0.5); // 3

  // Make Merge the baseline for the upcoming O(n log n) sorts
  baselineTime = runMySort(Merge<unsigned int>(2000000));
  testSort(testNum++, correct, bestSortTime, bestSortName, "Merge", baselineTime, baselineTime, 0, 0);  // 4 

  timeToSort = runMySort(Quick<unsigned int>(2000000));
  testSort(testNum++, correct, bestSortTime, bestSortName, "Quick", baselineTime, timeToSort, -2, 0);  // 5

  timeToSort = runMySort(Heap<unsigned int>(2000000));
  testSort(testNum++, correct, bestSortTime, bestSortName, "Heap", baselineTime, timeToSort, -2, 2);  // 6

  timeToSort = runMySort(ArrayKMerge<unsigned int, 2>(2000000));
  testSort(testNum++, correct, bestSortTime, bestSortName, "K-Way Array Merge: 2-Way", baselineTime, timeToSort, -0.5, 2);  // 7

  timeToSort = runMySort(ArrayKMerge<unsigned int, 3>(2000000));
  testSort(testNum++, correct, bestSortTime, bestSortName, "K-Way Array Merge: 3-Way", baselineTime, timeToSort, -0.5, 2);  // 8

  timeToSort = runMySort(ArrayKMerge<unsigned int, 4>(2000000));
  testSort(testNum++, correct, bestSortTime, bestSortName, "K-Way Array Merge: 4-Way", baselineTime, timeToSort, -0.5, 2);  // 9

  timeToSort = runMySort(ArrayKMerge<unsigned int, 5>(2000000));
  testSort(testNum++, correct, bestSortTime, bestSortName, "K-Way Array Merge: 5-Way", baselineTime, timeToSort, -0.5, 2);  // 10

  timeToSort = runMySort(ArrayKMerge<unsigned int, 6>(2000000));
  testSort(testNum++, correct, bestSortTime, bestSortName, "K-Way Array Merge: 6-Way", baselineTime, timeToSort, -0.5, 2);  // 11

  timeToSort = runMySort(ArrayKMerge<unsigned int, 7>(2000000));
  testSort(testNum++, correct, bestSortTime, bestSortName, "K-Way Array Merge: 7-Way", baselineTime, timeToSort, -0.5, 2);  // 12

  timeToSort = runMySort(ArrayKMerge<unsigned int, 8>(2000000));
  testSort(testNum++, correct, bestSortTime, bestSortName, "K-Way Array Merge: 8-Way", baselineTime, timeToSort, -0.5, 2); // 13

  cout << "##########################################################" << endl;
  cout << "## Note, some prior tests may fail on GitHub, that's ok ##" << endl;
  cout << "##########################################################" << endl;

  // Allow up to 2 failed tests becase GitHub's processors aren't consistent.
  return (testNum - 1 + 2 >= correct && correct > 0);
}

int test_KWayMergeSmall() {

  int testNum = 1;
  int correct = 0;
  int speedupCorrect = 0;

  cout << "--------testKWayMerge Tests--------" << endl;
  cout << "########################################" << endl;
  cout << "## Uncomment these when ready to test ##" << endl;
  cout << "########################################" << endl;

   double timeToSort = 0.0;
   double bestSortTime = 0.0;
   string bestSortName = "";

   timeToSort = runMySort(HeapKMerge<int, 2>(8), {5, 2, 8, 4, 3, 7, 1, 6});  

   testSort(testNum++, correct, bestSortTime, bestSortName, "Merge", timeToSort + 0.001, timeToSort + 0.001, 0.0, 0.0); // 1

   timeToSort = runMySort(HeapKMerge<int, 3>(20), {11, 5, 19, 2, 10, 15, 12, 8, 20, 4, 3, 17, 18, 7, 1, 16, 14, 13, 6, 9});

   testSort(testNum++, correct, bestSortTime, bestSortName, "Merge", timeToSort + 0.001, timeToSort + 0.001, 0.0, 0.0); // 2

   timeToSort = runMySort(HeapKMerge<int, 4>(22), {11, 22, 19, 2, 10, 15, 12, 8, 20, 4, 3, 17, 18, 7, 21, 16, 14, 13, 6, 9, 1, 5});

   testSort(testNum++, correct, bestSortTime, bestSortName, "Merge", timeToSort + 0.001, timeToSort + 0.001, 0.0, 0.0); // 3

  return (testNum - 1 == correct);
}
    
int test_KWayMerge() {

  int testNum = 1;
  int correct = 0;
  int speedupCorrect = 0;

  cout << "--------testKWayMerge Tests--------" << endl;
  cout << "########################################" << endl;
  cout << "## Uncomment these when ready to test ##" << endl;
  cout << "########################################" << endl;

   double timeToSort = 0.0;
   double bestSortTime = 0.0;
   string bestSortName = "";

   double baselineMerge = runMySort(Merge<unsigned int>(2000000));

   testSort(testNum++, correct, bestSortTime, bestSortName, "Merge", baselineMerge, baselineMerge, 0.0, 0.0); // 1

   cout << "For information, this Merge Sort time will be the baseline: " << baselineMerge << " milliseconds" << endl << endl;

   timeToSort = runMySort(HeapKMerge<unsigned int, 2>(2000000));
   testSort(testNum++, correct, bestSortTime, bestSortName, "K-Way Heap Merge: 2-Way", baselineMerge, timeToSort, -0.75, 1); // 2

  timeToSort = runMySort(HeapKMerge<unsigned int, 3>(2000000));
  testSort(testNum++, correct, bestSortTime, bestSortName, "K-Way Heap Merge: 3-Way", baselineMerge, timeToSort, -0.75, 0.2); // 3

  timeToSort = runMySort(HeapKMerge<unsigned int, 4>(2000000));
  testSort(testNum++, correct, bestSortTime, bestSortName, "K-Way Heap Merge: 4-Way", baselineMerge, timeToSort, -0.75, 0.2); // 4

  timeToSort = runMySort(HeapKMerge<unsigned int, 5>(2000000));
  testSort(testNum++, correct, bestSortTime, bestSortName, "K-Way Heap Merge: 5-Way", baselineMerge, timeToSort, -0.75, 0.1); // 5

  timeToSort = runMySort(HeapKMerge<unsigned int, 6>(2000000));
  testSort(testNum++, correct, bestSortTime, bestSortName, "K-Way Heap Merge: 6-Way", baselineMerge, timeToSort, -0.75, -0.02); // 6

  timeToSort = runMySort(HeapKMerge<unsigned int, 7>(2000000));
  testSort(testNum++, correct, bestSortTime, bestSortName, "K-Way Heap Merge: 7-Way", baselineMerge, timeToSort, -0.75, -0.05); // 7

  timeToSort = runMySort(HeapKMerge<unsigned int, 8>(2000000));
  testSort(testNum++, correct, bestSortTime, bestSortName, "K-Way Heap Merge: 8-Way", baselineMerge, timeToSort, -0.75, -0.05); // 8

  timeToSort = runMySort(HeapKMerge<unsigned int, 9>(2000000));
  testSort(testNum++, correct, bestSortTime, bestSortName, "K-Way Heap Merge: 9-Way", baselineMerge, timeToSort, -0.75, -0.05); // 9

  timeToSort = runMySort(HeapKMerge<unsigned int, 10>(2000000));
  testSort(testNum++, correct, bestSortTime, bestSortName, "K-Way Heap Merge: 10-Way", baselineMerge, timeToSort, -0.75, -0.02); // 10

  timeToSort = runMySort(HeapKMerge<unsigned int, 11>(2000000));
  testSort(testNum++, correct, bestSortTime, bestSortName, "K-Way Heap Merge: 11-Way", baselineMerge, timeToSort, -0.75, -0.02); // 11

  timeToSort = runMySort(HeapKMerge<unsigned int, 12>(2000000));
  testSort(testNum++, correct, bestSortTime, bestSortName, "K-Way Heap Merge: 12-Way", baselineMerge, timeToSort, -0.75, -0.02); // 12

  timeToSort = runMySort(HeapKMerge<unsigned int, 13>(2000000));
  testSort(testNum++, correct, bestSortTime, bestSortName, "K-Way Heap Merge: 13-Way", baselineMerge, timeToSort, -0.75, -0.02); // 13

  timeToSort = runMySort(HeapKMerge<unsigned int, 14>(2000000));
  testSort(testNum++, correct, bestSortTime, bestSortName, "K-Way Heap Merge: 14-Way", baselineMerge, timeToSort, -0.75, -0.02); // 14

  timeToSort = runMySort(HeapKMerge<unsigned int, 15>(2000000));
  testSort(testNum++, correct, bestSortTime, bestSortName, "K-Way Heap Merge: 15-Way", baselineMerge, timeToSort, -0.75, -0.02); // 15

  timeToSort = runMySort(HeapKMerge<unsigned int, 31>(2000000));
  testSort(testNum++, correct, bestSortTime, bestSortName, "K-Way Heap Merge: 31-Way", baselineMerge, timeToSort, -0.75, 1); // 16

  timeToSort = runMySort(HeapKMerge<unsigned int, 63>(2000000));
  testSort(testNum++, correct, bestSortTime, bestSortName, "K-Way Heap Merge: 63-Way", baselineMerge, timeToSort, -0.75, 1); // 17


  cout << endl << "** Checking for speedup, one of these should have run significantly faster ** " << endl << endl;

  double percentSpeedup = 0.0;

  if (baselineMerge != 0.0) {
    percentSpeedup = (((bestSortTime - baselineMerge) / baselineMerge) * -1 * 100);
    cout << "For information, the fastest sort was " << bestSortName << " at " << bestSortTime << " milliseconds," << endl;
    cout << "which is a " << percentSpeedup << " % speedup over the Merge Sort" << endl << endl;
    testSpeedup(testNum++, speedupCorrect, percentSpeedup, 20, 75); // 18
  }

  cout << "##########################################################" << endl;
  cout << "## Note, some prior tests may fail on GitHub, that's ok ##" << endl;
  cout << "##########################################################" << endl;

  // Allow up to 4 failed tests becase GitHub's processors aren't consistent.
  return (testNum - 1 + 4 >= correct && correct > 0 && speedupCorrect == 1);
}

int test_KWayTemplates() {

  int testNum = 1;
  int correct = 0;

  cout << "--------test_KWayTemplates Tests--------" << endl;
  cout << "########################################" << endl;
  cout << "## Uncomment these when ready to test ##" << endl;
  cout << "########################################" << endl;

  double timeToSort = runMySort(HeapKMerge<double, 4>(20));
  double bestSortTime = 0.0;
  string bestSortName = "";

  testSort(testNum++, correct, bestSortTime, bestSortName, "K-Way Heap Merge: 4-Way, doubles", timeToSort + 0.001, timeToSort + 0.001, 0, 2.0); // 1

  timeToSort = runMySort(HeapKMerge<string, 4>(20));
  testSort(testNum++, correct, bestSortTime, bestSortName, "K-Way Heap Merge: 4-Way, strings", timeToSort + 0.001, timeToSort + 0.001, 0, 2.0); // 2

  return (testNum - 1 >= correct && correct > 0);
}

int main(int argc, char** argv) {


  int test = 0;
  int count = 0;

  if (argc > 1) {
    test = stoi(argv[1]);
  }
  switch (test) {
  case 0:
    if (test_PresuppliedSorts()) count++;
    if (test_KWayMergeSmall()) count++;
    if (test_KWayMerge()) count++;
    if (test_KWayTemplates()) count++;
    cout << "----------------" << endl;
    cout << "Passed " << count << " out of 4 group tests" << endl;
    cout << "--End of tests--" << endl;
    return count != 4;
  case 1:
    return !test_PresuppliedSorts();
  case 2:
    return !test_KWayMerge();
  case 3:
    return !test_KWayTemplates();
  }

  return 0;

}

