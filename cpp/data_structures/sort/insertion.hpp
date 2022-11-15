#ifndef SORT_INSERTION_HPP_
#define SORT_INSERTION_HPP_

static void insertAtIthPosition(int *arr, int arrSize, int i)
{
    int j = i - 1;
    int key = arr[i];
    while ((j >= 0) && (arr[j] > key))
    {
        // keep shifting elements before the insertion line down one until you find
        //  the spot where you can "insert" the key
        arr[j + 1] = arr[j];
        j--;
    }
    // found the spot just prior to where the key goes or j is -1
    arr[j + 1] = key;
}

//                               j=-1
//                 +---+    +---+                          +---+
//       j=i-1=0   | 3 |    | 3 |j=0                       | 1 |j+1
// insertion point>+---+    +---+ v                        +---+
//           i=1   | 1 |    | 3 |j+1                       | 3 |
//                 +---+    +---+                          +---+
//                 | 5 |    | 5 |                          | 5 |
//                 +---+    +---+                          +---+
//                 | 2 |    | 2 |                          | 2 |
//                 +---+    +---+                          +---+
//            key=a[i]=1    a[j]>key                       a[j+1]=key
//                          keep moving elements
//                          above the insertion line
//                          down till you go below 0 or
//                          you find an a[j]<key
void Sort_insertion(int *arr, int arrSize)
{
    // start from index 1
    int i = 1;
    while (i < arrSize)
    {
        insertAtIthPosition(arr, arrSize, i);
        i++;
    }
}

#endif /* SORT_INSERTION_HPP_ */