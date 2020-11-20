/* Project Checklist
   Acquire Counts [x]
   Allocate Space [x]
   Read Files Properly [x]
   Store Data[x]
   Merge Sort (ascensing/lexicographically)[x]
   Print Shared[x]

	*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

bool existsIn(int x, int searchArray[], int size)
{
  for (int i = 0; i < size; i++){
    if (x == searchArray[i]){
      //cout << x << " is in both arrays" << endl;
      return true;
    }
  }
  return false;
}

bool isDupe(int x, int checkArray[], int size, int& openSpot)
{
  int i = 0;
  bool flag = false;

  while (i < openSpot){
    if (x == checkArray[i]){
      flag = true;
      break;
    }
    i++;
  }
  if (flag == false){
    //cout << x << " is not a duplicate" << endl;
    checkArray[openSpot] = x;
    openSpot++;
  }
return flag;
}

bool StringexistsIn(string x, string searchArray[], int size)
{
  for (int i = 0; i < size; i++){
    if (x == searchArray[i]) return true;
  }
return false;
}

bool StringisDupe(string x, string checkArray[], int size, int& openSpot)
{
  int i = 0;
  bool flag = false;

  while (i < openSpot){
    if (x == checkArray[i]){
      flag = true;
      break;
    }
    i++;
  }
  if (flag == false){
    checkArray[openSpot] = x;
    openSpot++;
  }
return flag;
}

void CountElements(char const *argv[], int& firstCount, int& secondCount)
{
  string argv1 = argv[1];
  ifstream firstFile;
  ifstream secondFile;
  firstFile.open(argv[2]);
  secondFile.open(argv[3]);

  if (argv1 == "i"){
    int extracted;
      while(firstFile >> extracted){
        //cout << "Value : " << extracted << endl;
        firstCount++;
      }
      while(secondFile >> extracted){
        secondCount++;
      }
    }//end of int counter

    else if (argv1 == "s"){
      string extracted;
          while(firstFile >> extracted){
            firstCount++;
          }
          while(secondFile >> extracted){
            secondCount++;
          }
    }//end of string counter

firstFile.close();
secondFile.close();
//cout << "First: " << firstCount << endl << "Second: " << secondCount << endl;
return;
}//end of function

void Stringmerge(string arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    //temp arrays
    string L[n1], R[n2];

    //copies
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void StringmergeSort(string arr[], int l, int r)
{
    if (l < r)
    {
        int m = l+(r-l)/2;
        StringmergeSort(arr, l, m);
        StringmergeSort(arr, m+1, r);

        Stringmerge(arr, l, m, r);
    }
}
///
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    /* create temp arrays */
    int L[n1], R[n2];
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l+(r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}
///
int main(int argc, char const *argv[]) {

  int firstCount = 0; //way to "dynamically" allocate
  int secondCount = 0;
  CountElements(argv, firstCount, secondCount);
  ifstream firstFile;
  ifstream secondFile;

  firstFile.open(argv[2]);
  secondFile.open(argv[3]);
  string argv1 = argv[1];



  if (argv1 == "i"){
    int firstArray[firstCount];
    int secondArray[secondCount];

    int extracted;

    for (int i = 0; i < firstCount; i++){//going through each value of the file
        firstFile >> extracted;
        firstArray[i] = extracted;
    }//end of first file check

    for (int i = 0; i < secondCount; i++){
        secondFile >> extracted;
        secondArray[i] = extracted;
    }

    mergeSort(firstArray, 0, firstCount - 1);
    mergeSort(secondArray, 0, secondCount - 1);
    //for (int i = 0; i < firstCount; i++) cout << "Sorted First: " << firstArray[i] << endl;
    //for (int i = 0; i < secondCount; i++) cout << "Sorted Second: " << secondArray[i] << endl;

    if (firstCount <= secondCount){
      int openSpot = 0;
      int storage[firstCount];
      //for (int i = 0; i < firstCount; i++) cout << "Original Storage " << storage[i] << endl;
        for (int i = 0; i < firstCount; i++){
          if ((existsIn(firstArray[i], secondArray, secondCount) == true) && (isDupe(firstArray[i], storage, firstCount, openSpot) == false)){
            cout << firstArray[i] << endl;
            }
          }
          //for (int i = 0; i < firstCount; i++) cout << storage[i] << " is in storage"<< endl;
          return 0;
        }

    if (secondCount <= firstCount){
      int openSpot = 0;
      int storage[secondCount];
      //for (int i = 0; i < secondCount; i++) cout << "Original Storage " << storage[i] << endl;
        for (int i = 0; i < secondCount; i++){
          if ((existsIn(secondArray[i], firstArray, firstCount) == true) && (isDupe(secondArray[i], storage, secondCount, openSpot) == false)){
            cout << secondArray[i] << endl;
            }
         }
         //for (int i = 0; i < firstCount; i++) cout << storage[i] << " is in storage"<< endl;
         return 0;
      }
    }//end of integer case

  if (argv1 == "s"){
    string firstArray[firstCount];
    string secondArray[secondCount];

    string extracted;

    for (int i = 0; i < firstCount; i++){
        firstFile >> extracted;
        firstArray[i] = extracted;
    }

    for (int i = 0; i < secondCount; i++){
        secondFile >> extracted;
        secondArray[i] = extracted;
    }
    StringmergeSort(firstArray, 0, firstCount - 1);
    StringmergeSort(secondArray, 0, secondCount - 1);
    //for (int i = 0; i < firstCount; i++) cout << "Sorted First: " << firstArray[i] << endl;
    //for (int i = 0; i < secondCount; i++) cout << "Sorted Second: " << secondArray[i] << endl;

    if (firstCount <= secondCount){
      int openSpot = 0;
      string storage[firstCount];
        for (int i = 0; i < firstCount; i++){
          if ((StringexistsIn(firstArray[i], secondArray, secondCount) == true) && (StringisDupe(firstArray[i], storage, firstCount, openSpot) == false)){
            cout << firstArray[i] << endl;
            }
          }
          return 0;
        }

    if (secondCount <= firstCount){
      int openSpot = 0;
      string storage[secondCount];
        for (int i = 0; i < secondCount; i++){
          if ((StringexistsIn(secondArray[i], firstArray, firstCount) == true) && (StringisDupe(secondArray[i], storage, secondCount, openSpot) == false)){
            cout << secondArray[i] << endl;
            }
          }
          return 0;
      }
  }//end of string case
return 0;
}//end of program
