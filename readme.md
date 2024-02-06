**Learning Outcomes:**

This program will cover the following topics:

*   Templates
*   Inheritance
*   Recursion
*   Sorting
*   Memory Management with dynamic allocated memory. 

While this contains many concepts, this assignment largely lets you mimic what has been shown previously. 

As you code this problem, make sure to keep checking back at the Help and Get Help discussion board to help others or get help programming this problem.

# K-way Merge Sort Overview

The merge sort is popular for two reasons: 1) its worst case is O(n log n), and 2) it has a property known as stable. Like all sorting algorithms, it has downsides. Here the downside requiring O(n) additional memory, and it doesn't perform quite as fast as some other O(n log n) sorts. The upsides are often highly desired. 

The merge sort algorithm has a faster approach compared to the standard approach: using a k-way merge process. Previously, the merge sort worked by merging together *two* already sorted smaller input subarrays into one larger sorted array. (Note, the term subarray is used because the two inputs are conceptually treated as two separate arrays, but in reality are just two parts of the same array.) The k-way merge sort works by merging together *k* already sorted smaller input subarrays into one larger sorted array. 

# Examples of Regular Merge Sort and K-way Merge Sort

Suppose the regular merge sort has progressed to the last merge step shown below, where the array is two sorted regions ready to be merged into one fully sorted array. Note that the first five sorted five elements  followed by the sorted second five elements:

`Array: | a f j k p b d g l m |`

For simplicity, this one array is just conceptually treated as though they are two separate arrays, split in half.

`Subarray 0: | a f j k p |   Subarray 1: | b d g l m |`

The regular merge sort looks at the first unsorted element of subarray 0 and subarray 1, which are `a` and `b`. It compares the two with `<`. `a` is smaller:

`Merged Array: | a `

The regular merge sort then looks at the first unsorted element of subarray 0 and subarray 1, which are `f` and `b`. It compares the two with `<`. `b` is smaller:

`Merged Array: | a b`

The regular merge sort then looks at the first unsorted element of subarray 0 and subarray 1, which are `f` and `d`. It compares the two with `<`. `d` is smaller:

`Merged Array: | a b d`

And so on, until:

`Merged Array: | a b d f g j k l m p |`

The k-way merge sort approach works by merging together *k* input arrays instead of two arrays. Implemented correctly, this yeilds performance speedups over the prior 2-way merge sort. For example, suppose *k* is 4, and the merge sort is running on the following array:

`Subarray 0: | a h k r y |   Subarray 1: | c g m n p |   Subarray 2: | e i j o t |   Subarray 3: | d q u v x |`

The k-way merge sort looks at the first unsorted element of each subarray, which are `a`, `c`, `e`, and `d`. Somehow all four must be compared to find the smallest, which is `a`:

`Merged Array: | a`

The k-way merge sort looks at the first unsorted element of each subarray, which are `h`, `c`, `e`, and `d`. Somehow all four must be compared to find the smallest, which is `c`:

`Merged Array: | a c`

And so on, until: 

`Merged Array: | a c d e g h i j k m n o p q r t u v x y |`

# How to Implement a K-way Merge Sort

As described earlier for the merging process: "Somehow all four must be compared to find the smallest". This "somehow" is not trivial. The naive approach is to simply perform a `<` check for each pair, remembering the mininum each time. For small *k*, this is fine. In fact, the homework assignment has this already implemented as an ArrayKMerge sort. Review the code. It is not pretty.

For large *k*, this will not work. For example, if *k* = 4, then 3 `<` comparisons are required to find the minimum. If *k* = 16, then 15 comparisons are required to find the minimum. **Those 15 comparisons make the naive k-way merge sort performance worse than the regular 2-way merge sort.**

One approach to efficiently find the minimum value of *k* items is using a min heap tree. In short, a heap tree works by making sure the parent is always smaller than its two children. For example, suppose *k* = 16, and thus 16 input arrays are used. Further suppose these array values are three digit numbers. An example min heap of the first value of 16 input arrays may look like the following:
```
              14
         /         \
      152             82
    /     \         /     \
   210    350      198     418
  /  \    /  \    /  \    /   \ 
 301 322 461 439 313 299 500 499
/
349
```
Note that each parent is smaller than its two children. A min heap tree itself is not ordered or sorted in any way, it only means that every parent is smaller than its children. That also means the root of the tree, 14, is the smallest of them all. This last characteristic is exactly what we can use for the k-way merge sort. Again recall that each of these 16 values represent the first value of the 16 input sorted arrays. Instead of performing 15 `<` comparisons to find the smallest, the k-way merge sort need only refer to the root of the min heap tree, 14, and copy that to the output array. Once 14 is pulled out of the tree, it needs to be replaced. Suppose the subarray contained `14 199 222 450 512`. Since the next value in the subarray is 199, the 14 in the heap tree is replaced by 199. 
```
              199
         /         \
      152             82
    /     \         /     \
   210    350      198     418
  /  \    /  \    /  \    /   \ 
 301 322 461 439 313 299 500 499
/
349
```
The tree is now no longer a heap tree, 199 is bigger than its children. This is fixed easily. First, compare 199 with its children 152 and 82. Two `<` comparisons yeild that 82 is the smallest. 82 is swapped up. 
```
              82
         /         \
      152             199
    /     \         /     \
   210    350      198     418
  /  \    /  \    /  \    /   \ 
 301 322 461 439 313 299 500 499
/
349
```
Better, but the tree is still not a heap tree. The parent 199 is not the smallest. Again compare 199 with 198 and 418. Two `<` comparisons yeild that 198 is the smallest. 198 is swapped up:
```
              82
         /         \
      152             198
    /     \         /     \
   210    350      199     418
  /  \    /  \    /  \    /   \ 
 301 322 461 439 313 299 500 499
/
349
```
Good. The tree is a min heap tree again. All parents are smaller than their children. **All it took was 4 operator `<`, and not 15 operator `<` like the prior naive k-way approach.**  Now the k-way merge sort can iterate again. The root, 82, is the smallest value. It is put into the output array (after 14 from earlier). This entire process repeats, sorting one value each iteration, ultimately using fewer operator `<` steps. This approach now allows the k-way merge performance to substantially improve over a 2-way merge sort and over the prior naive k-way approach.

Note that implementing a performant heap data structure isn't trivial as it requires using a single array and clever indexing math. Fortunately, this homework assignment provides this min heap data structure and its logic. You will not implement any heaping logic. You will only use min heap code already supplied.

The overview here is largely to assist you in explaining why the k-way merge sort works using a heap.

## Requirements:
Implement the k-way merge sort in the file `HeapKMergeSort.hpp`, as found in the `inc` directory.  

Code construction can be divided into two primary tasks, 1) declaring the class and 2) implementing the runSort() methods

### 1. **Preparing the class**

Create a class called `HeapKMerge`. Use the the prior `Merge` and `ArrayKMerge` classes as a guide. They are found in `inc\MergeSort.hpp` and `inc\ArrayKMergeSort.hpp`.
* The class requires two template variables: `template <typename T, unsigned int K>`
* The class is named `HeapKMerge`. It publicly inherits from BaseSort<T>.
* A public constructor has a const unsigned int capacity parameter. This constructor invokes `BaseSort`'s constructor, and for the first argument passes in the name of this sort algorithm, `"Heap - K-Way Merge"`, and for the second argument passes in the capacity. The `HeapKMerge`'s public consturctor itself has no code logic, and thus its code body can simply be `{}`.
* A `public void runSort()` method. Declare the method in the class, and also provide the definition of the method after the class.
    * The definition requires two template variables: `template <typename T, unsigned int K>`
    * The method returns void. The `runSort()` method should be prefixed with `HeapKMerge<T, K>::`. The method body itself should be `{}` for now.
* A `private void runSort()` method with two parameters. The first is an unsigned int called `firstIndex`, the second is an unsigned int called `lastIndex`. 
    * The definition requires two template variables: `template <typename T, unsigned int K>`
    * The method returns void. This `runSort()` method should be prefixed with `HeapKMerge<T, K>::`. Supply the two parameters. The method body itself should be `{}` for now.
* In `src\k-way-mergesort-test.cpp`, uncomment the tests for the k-way merge sort.

At this point, your code should at least compile. No k-way sort logic exists, but at least it compiles. Test that your program can build and run.

### 2. **Defining the methods**

The `HeapKMerge`'s public `runSort()` definition contains the same C++ logic the same as the `MergeSort`'s `runSort()` method. Change the currently empty method body so that it simply invokes the private method, passing in `0` for the first argument and `this->capacity` for the second argument. 

The `HeapKMerge`'s private `runSort()` definition is where the sorting logic occurs. The logic works through these steps:

1. Determine if recursion is done because the current working section of the array is only 1 item in size.
2. Recursively call `runSort()` *k* times, passing in indexes where each input subarray starts.
3. Create a copy of the current working section of the array.
4. Build the min heap tree using the array copy made in step 3.
5. Iterate.  For as long as there are values to sort
    1. obtain the smallest item on the min heap tree (the min heap object will rebuild its own heap tree correctly) and
    2. write that value to the correct spot in the current working section of the array

A full description is below:

1) The private `runSort()` method works only within one region of the array at a time. Each recursive call works on a different region. That region starts at firstIndex and ends at lastIndex. For example, suppose an array has 1000 items and one of the instances of the `runSort()` method has `firstIndex = 562` and `lastIndex = 625`. Thus, this method is currently working on an array region of size 625 - 562 = 63 items. 

You must compute the number of items in this array region and store it in a variable. For this part 1, check if the array region size is less than 2. If so, no more sorting is necessary and the method simply calls `return;`.  

2) Recursive calls. The goal here is to subdivide the current array region into *k* ways for *k* smaller array regions, then recurisvely repeat the process. This requires indexing math. Be warned, indexing math is often the hardest part.

As a simple example, suppose an instance of the `runSort()` method is at a point where the array region contains 22 items, `firstIndex = 22`, `lastIndex = 44`, and `k = 4`. Splitting these 22 items could be done by having the first group contain 5 items, the second group 6 items, the third group 5 items, and the fourth group 6 items, or a 5-6-5-6 approach. But a 6-5-6-5 is also valid. So is a 5-5-6-6, and a 6-6-5-5.  

In another example, suppose an instance of the `runSort()` method is at a point where the array region contains 63 items, `firstIndex = 562`, `lastIndex = 625`, and `k = 4`. That region of 63 needs to be split into *k* = 4 groups. One valid way is a 15-16-16-16 approach. The first group contains 15 items, the next contains of 16 items, the next contains of 16 items, and the final group of 16 itmes. Said another way, in the first iteration (*i* = 0) the arguments passed into a recursive runSort() call are 562 and 577. The second iteration (*i* = 1) the arguments for the recursive call are 577 and 593. The third itration (*i* = 2) the arguments for the recursive call are 593 and 609. The fourth iteration (*i* = 3) the arguments for the recursive call are 609 and 625. 

This can be seen in the table below.

```	
firstIndex |  lastIndex | Total values in array region | i | k |  The first index to compute | The second index to compute
562           625         63                             0   4    562                          577
562           625         63                             1   4    577                          593
562           625         63                             2   4    593                          609
562           625         63                             3   4    609                          625
```	

Indexing math often is often confusing, even for graduate students. Don't despair, just work at it out on paper until a solution is found. Note that all division math uses integer division. The prior table can be computed with simple arithmetic using only `firstIndex`, `k`, `i`, and the number of values in this array region. Try it out on paper before you write it in code. If you come up with a 16-16-16-15 approach, that will work. A 16-15-16-16 approach or a 16-16-15-16 approach also works.

Continuing with the example from the above table, `k = 4` recursive calls are needed.  Use a loop to call `runSort(562, 577);`, `runSort(577, 593);`, `runSort(593, 609);`, and `runSort(609, 625);`, but use variables holding indexes instead of hard coding these integer values.  

One final complication. The upcoming `MinHeap` class (step 5) must know how you split the region into `k = 4` segments. If you used a 16-16-16-15 approach instead of a 15-16-16-16 approach, the `MinHeap` object must know that. So create an int array, `int lastIndexesArray[k];`. As you compute the last indexes, copy the last indexes to the appropriate spot in this array. In the table example, `lastIndexesArray[0]` is assigned the value 577, `lastIndexesArray[1]` has 593, `lastIndexesArray[2]` has 609, and `lastIndexesArray[3]` has 625.  
 

3) Steps 1 and 2 have completed the prior recursion calls with the recursive base case. Step 3 now merges sorted subarrays into a larger array. The merge sort will start with merging subarrays of size 0 or 1 into larger subarrays. The recursive unwinding will ensure larger subarrays are merged into even larger subarrays, until it merges all.

For step 3, write the code after the for loop that called `runSort()`.  

First create a copy of the current array region. An array can be dynamically allocated with the following line of code:

`T* arrayCopy = new T[number_of_array_values];`

A good rule of thumb is that whenever C++'s new is used to create an array, write the line of code right now to reclaim it (programmers often forget this). So at the end of this `runSort()` method, write:

``delete[] arrayCopy;``

No code should be placed after that `delete[]` call.

After the C++ new call to create a new array, create for loop that iterates through the current array region. Copy each item to the arrayCopy. For example, if the current array region has `firstIndex = 562` and `lastIndex = 625`, then arrayCopy will be 63 items in size. The for loop must iterates 63 times. At `i = 0`, `this->arr` at index 562 is copied into `arrayCopy` at index 0. At `i = 1`, `this->arr` at index 563 is copied into `arrayCopy` at index 1. And so on, until `i = 62`, when `this->arr` at index 624 is copied into `arrayCopy` at index 62. Use simple indexing arithmetic to generalize these values.

4) Build the min heap tree using the array copy made in step 3, the number of array values from step 1, and the last indexes array from step 2. As this is a provided tool, only one line of code is required:

	``MinHeap<T, K> minHeap(arrayCopy, number_of_array_values, lastIndexesArray);``

(Note, this min heap doesn't physically build a tree with nodes. The object just conceptually tracks where the trees elements are throughout the array. Further, this object also knows that the arrayCopy is split *k* ways, and has logic to know when a kth region is fully used up for the purposes of a k-way merge sort.)

5) Iterate and sort one element per iteration. This loop iterates equal to the amount of elements in the array region. For example, if the array region is 63 elements in size, this loop iterates 63 times.

Use the minHeap object to get the smallest unused item of the *k* arrays. You can do this simply through `minHeap.getSmallest();`. This method returns the smallest value of all subarrays from step 4. Store that value in the next slot of `this->arr`. For example, with `firstIndex = 562`, `lastIndex = 625`, and iteration `i = 0`, then  `minHeap.getSmallest()` returns the smallest item in `arrayCopy`. Store that returned value in `this->arr` at index 562. At iteration `i = 1`, `minHeap.getSmallest()` returns the second smallest item in `arrayCopy`. Store that returned value in `this->arr` at index 563. And so on, until `i = 62`, then `minHeap.getSmallest()` returns the largest item in `arrayCopy`. Store that returned value in `this->arr` at index 624. Use simple indexing arithmetic to generalize these values.

This completes the algorithm. (Make sure the `delete[] arrayCopy;` line is still the last line of this method.)  The sort should now work. If it doesn't immediately work, try a test run with 8 array elements and `K = 2` with `runMySort(HeapKMerge<unsigned int, 2>(8));`. Use the debugger judiciously. Step in, step out, and step over where appropriate. Note that a step over on a recursive call will run all subsequent recursive calls, and so step into should usually be used on recursion. Consider also printing the arrays on the console as well as all the variable values for each `runSort()` call to help you see what the program is doing. Another helpful test run is a 22 element array and `K = 4`.


### 3. **Expected output**

The program's output should resemble the following (times will vary depending on the speed of your machine and compiler optimizations). Note that merge sort will run a bit slower than quick sort and heap sort, largely due to frequent dynamic memory allocations and deallocations (an optimized version of merge sort would utilize a memory pool to avoid this.). If your IDE easily supports running in an optimized release mode and without debug flags, your times will improve by several factors.
```
--------testPresuppliedSorts Tests--------
Running sort: Bubble with 20000 items
Sorted!
Sort completed in 375.876 milliseconds
Passed Test 1. Bubble sort

Running sort: Selection with 20000 items
Sorted!
Sort completed in 389.447 milliseconds
Passed Test 2. Selection sort

Running sort: Insertion with 20000 items
Sorted!
Sort completed in 123.546 milliseconds
Passed Test 3. Insertion sort

Running sort: Merge with 2000000 items
Sorted!
Sort completed in 377.836 milliseconds
Passed Test 4. Merge sort

Running sort: Quick with 2000000 items
Sorted!
Sort completed in 164.335 milliseconds
Passed Test 5. Quick sort

Running sort: Heap with 2000000 items
Sorted!
Sort completed in 408.465 milliseconds
Passed Test 6. Heap sort

Running sort: Array K-Way Merge with 2000000 items
Sorted!
Sort completed in 389.263 milliseconds
Passed Test 7. K-Way Array Merge: 2-Way sort

Running sort: Array K-Way Merge with 2000000 items
Sorted!
Sort completed in 362.048 milliseconds
Passed Test 8. K-Way Array Merge: 3-Way sort

Running sort: Array K-Way Merge with 2000000 items
Sorted!
Sort completed in 358.251 milliseconds
Passed Test 9. K-Way Array Merge: 4-Way sort

Running sort: Array K-Way Merge with 2000000 items
Sorted!
Sort completed in 336.603 milliseconds
Passed Test 10. K-Way Array Merge: 5-Way sort

Running sort: Array K-Way Merge with 2000000 items
Sorted!
Sort completed in 389.842 milliseconds
Passed Test 11. K-Way Array Merge: 6-Way sort

Running sort: Array K-Way Merge with 2000000 items
Sorted!
Sort completed in 418.333 milliseconds
Passed Test 12. K-Way Array Merge: 7-Way sort

Running sort: Array K-Way Merge with 2000000 items
Sorted!
Sort completed in 415.218 milliseconds
Passed Test 13. K-Way Array Merge: 8-Way sort

##########################################################
## Note, some prior tests may fail on GitHub, that's ok ##
##########################################################
--------testKWayMerge Tests--------
########################################
## Uncomment these when ready to test ##
########################################
Running sort: Heap - K-Way Merge with 8 items
5 2 8 4 3 7 1 6
1 2 3 4 5 6 7 8
Sorted!
Sort completed in 0.0094 milliseconds
Passed Test 1. Merge sort

Running sort: Heap - K-Way Merge with 20 items
11 5 19 2 10 15 12 8 20 4 3 17 18 7 1 16 14 13 6 9
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
Sorted!
Sort completed in 0.0057 milliseconds
Passed Test 2. Merge sort

Running sort: Heap - K-Way Merge with 22 items
11 22 19 2 10 15 12 8 20 4 3 17 18 7 21 16 14 13 6 9 1 5
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22
Sorted!
Sort completed in 0.0057 milliseconds
Passed Test 3. Merge sort

--------testKWayMerge Tests--------
########################################
## Uncomment these when ready to test ##
########################################
Running sort: Merge with 2000000 items
Sorted!
Sort completed in 388.454 milliseconds
Passed Test 1. Merge sort

For information, this Merge Sort time will be the baseline: 388.454 milliseconds

Running sort: Heap - K-Way Merge with 2000000 items
Sorted!
Sort completed in 373.739 milliseconds
Passed Test 2. K-Way Heap Merge: 2-Way sort

Running sort: Heap - K-Way Merge with 2000000 items
Sorted!
Sort completed in 304.704 milliseconds
Passed Test 3. K-Way Heap Merge: 3-Way sort

Running sort: Heap - K-Way Merge with 2000000 items
Sorted!
Sort completed in 294.761 milliseconds
Passed Test 4. K-Way Heap Merge: 4-Way sort

Running sort: Heap - K-Way Merge with 2000000 items
Sorted!
Sort completed in 251.939 milliseconds
Passed Test 5. K-Way Heap Merge: 5-Way sort

Running sort: Heap - K-Way Merge with 2000000 items
Sorted!
Sort completed in 249.533 milliseconds
Passed Test 6. K-Way Heap Merge: 6-Way sort

Running sort: Heap - K-Way Merge with 2000000 items
Sorted!
Sort completed in 279.419 milliseconds
Passed Test 7. K-Way Heap Merge: 7-Way sort

Running sort: Heap - K-Way Merge with 2000000 items
Sorted!
Sort completed in 239.15 milliseconds
Passed Test 8. K-Way Heap Merge: 8-Way sort

Running sort: Heap - K-Way Merge with 2000000 items
Sorted!
Sort completed in 243.768 milliseconds
Passed Test 9. K-Way Heap Merge: 9-Way sort

Running sort: Heap - K-Way Merge with 2000000 items
Sorted!
Sort completed in 293.043 milliseconds
Passed Test 10. K-Way Heap Merge: 10-Way sort

Running sort: Heap - K-Way Merge with 2000000 items
Sorted!
Sort completed in 250.236 milliseconds
Passed Test 11. K-Way Heap Merge: 11-Way sort

Running sort: Heap - K-Way Merge with 2000000 items
Sorted!
Sort completed in 231.337 milliseconds
Passed Test 12. K-Way Heap Merge: 12-Way sort

Running sort: Heap - K-Way Merge with 2000000 items
Sorted!
Sort completed in 242.576 milliseconds
Passed Test 13. K-Way Heap Merge: 13-Way sort

Running sort: Heap - K-Way Merge with 2000000 items
Sorted!
Sort completed in 267.108 milliseconds
Passed Test 14. K-Way Heap Merge: 14-Way sort

Running sort: Heap - K-Way Merge with 2000000 items
Sorted!
Sort completed in 287.479 milliseconds
Passed Test 15. K-Way Heap Merge: 15-Way sort

Running sort: Heap - K-Way Merge with 2000000 items
Sorted!
Sort completed in 350.941 milliseconds
Passed Test 16. K-Way Heap Merge: 31-Way sort

Running sort: Heap - K-Way Merge with 2000000 items
Sorted!
Sort completed in 274.057 milliseconds
Passed Test 17. K-Way Heap Merge: 63-Way sort


** Checking for speedup, one of these should have run significantly faster **

For information, the fastest sort was K-Way Heap Merge: 12-Way at 231.337 milliseconds,
which is a 40.4468 % speedup over the Merge Sort

Passed Test 18

##########################################################
## Note, some prior tests may fail on GitHub, that's ok ##
##########################################################
--------test_KWayTemplates Tests--------
########################################
## Uncomment these when ready to test ##
########################################
Running sort: Heap - K-Way Merge with 20 items
0.986198 0.269162 0.516577 0.395632 0.057553 0.845578 0.456795 0.23535 0.64572 0.46527 0.804842 0.322042 0.748446 0.279116 0.665502 0.785532 0.867011 0.791245 0.510095 0.117294
0.057553 0.117294 0.23535 0.269162 0.279116 0.322042 0.395632 0.456795 0.46527 0.510095 0.516577 0.64572 0.665502 0.748446 0.785532 0.791245 0.804842 0.845578 0.867011 0.986198
Sorted!
Sort completed in 0.0032 milliseconds
Passed Test 1. K-Way Heap Merge: 4-Way, doubles sort

Running sort: Heap - K-Way Merge with 20 items
opsv pwow lqqj lhxb zhjm uvnm okyv bicq ajvy udww zmuu lnur dsqp dnyt nckm geut lfod aiqd pfqk yxrl
aiqd ajvy bicq dnyt dsqp geut lfod lhxb lnur lqqj nckm okyv opsv pfqk pwow udww uvnm yxrl zhjm zmuu
Sorted!
Sort completed in 0.0321 milliseconds
Passed Test 2. K-Way Heap Merge: 4-Way, strings sort

----------------
Passed 4 out of 4 group tests
--End of tests--
```
