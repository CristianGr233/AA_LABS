#include <iostream>
#include <chrono>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace std::chrono;

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void merge(vector<int> &array,int l, int m, int r)
{
    int n1=m-l+1;
    int n2=r-m;
    int left[n1], right[n2];

    for(int i=0;i<n1;i++)
        left[i]=array[l+i];
    for(int i=0;i<n2;i++)
        right[i]=array[m+1+i];

    int i=0,j=0,k=l;
    while(i<n1&&j<n2)
    {
        if(left[i]<=right[j])
        {
            array[k]=left[i];
            i++;
        }
        else
        {
            array[k]=right[j];
            j++;
        }
        k++;
    }
    while(i<n1)
    {
        array[k]=left[i];
        i++;
        k++;
    }
    while(j<n2)
    {
        array[k]=right[j];
        j++;
        k++;
    }
}

void divide(vector<int> &array,int left, int right)
{
    int middle;
    if(left<right)
    {
        middle=(left+right)/2;
        divide(array, left, middle);
        divide(array,middle+1,right);
        merge(array, left, middle, right);
    }

}

int partition(vector <int> &array, int left, int right) {
    int pivot = array[right];
    int i = (left - 1);

    for (int j = left; j <= right - 1; j++) {
        if (array[j] < pivot) {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[right]);
    return (i + 1);
}

void QuickSort(vector <int> &array, int l, int h) {

    if (l < h) {
        int pivot = partition(array, l, h);
        QuickSort(array, l, pivot - 1);
        QuickSort(array, pivot + 1, h);
    }

}

void heapify(vector<int>& array, int n, int i)
{
    int largest = i;
    int left = 2*i+1;
    int right = 2*i+2;

    if (left < n && array[left] > array[largest])
        largest = left;
    if (right < n && array[right] > array[largest])
        largest = right;
    if (largest != i) {
        swap(&array[i], &array[largest]);
        heapify(array, n, largest);
    }
}

void HeapSort(vector<int>& array, int left, int n)
{
    n++;
    for (int i = n/2-1; i>=0; i--)
        heapify(array, n, i);
    for (int i = n-1; i>=0; i--) {
        swap(array[0], array[i]);
        heapify(array,  i, 0);
    }
}


struct Node
{
    int n;
    struct Node* right;
    struct Node* left;

};

struct Node* newNode(int data)
{
    struct Node* tr=new Node();
    tr->n = data;
    tr->left=NULL;
    tr->right= NULL;
    return tr;
};

void Output(struct Node *r, vector<int> *result)
{

    if (r != NULL)
    {
        Output(r->left, result);
        result->push_back(r->n);
        Output(r->right, result);

    }

}

struct Node* insertion(struct Node* node, int data)
{
    if (node == NULL)
        return newNode(data);
    if (data <= node->n)
        node->left  = insertion(node->left, data);
    else if (data > node->n)
        node->right = insertion(node->right, data);

    return node;
}

void TreeSort(vector<int>& array, int left, int n)
{
    n++;
    struct Node *root = NULL;

    root = insertion(root, array[0]);
    for (int i=1; i<n; i++)
        root = insertion(root, array[i]);

    vector <int> *result = new vector<int>();
    Output(root, result);
    array=*result;
    delete result;
}

void GetDuration(vector<int> array, void (*function)(vector<int>&, int, int))
{
    auto start = high_resolution_clock::now();
    function(array, 0, array.size()-1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    float n_duration = duration.count();
    string unit = "ms";

    n_duration/=1000;
    if(n_duration > 1000)
    {
        n_duration/=1000;
        unit = "s";
    }
    cout<<(float)n_duration<<" "<<unit<<" ";
}

void Time(vector<vector<int>> arrays, vector<void (*)(vector<int>&, int, int)> sort_methods, vector<string> array_t)
{
    for(int k=0;k<sort_methods.size();k++){
    string name;
    switch(k)
    {
        case 0: name = "MergeSort";
            break;
        case 1: name = "QuickSort";
            break;
        case 2: name = "HeapSort";
            break;
        case 3: name = "TreeSort";
            break;
    }
    cout<<name<<endl;
    for(int i=0;i<arrays.size();i++)
    {
        vector<int> array = arrays[i];
        cout<<array_t[i]<<": ";
        GetDuration(array, sort_methods[k]);
        cout<<"  ";
    }
    cout<<endl<<endl;
    }
}

int main()
{
    string input;
    cout<<"0 for predetermined inputs, 1 for user-generated, 2 for randomised"<<endl;
    cin>>input;

    vector<void (*)(vector<int>&, int, int)> sort_methods;
    sort_methods.push_back(divide);
    sort_methods.push_back(QuickSort);
    sort_methods.push_back(HeapSort);
    sort_methods.push_back(TreeSort);
    if(input=="0")
    {
        vector<int> array1(100);
        for(int i=0;i<100;i++)
            array1[i] = i+1;
        vector<int> array2(100);
        for(int i=0;i<100;i++)
            array2[i] = 100-i;

        vector<int> array3 = {1, 2, 2, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11,
                              12, 12, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18, 18, 19, 19, 20, 20,
                              21, 21, 22, 22, 23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29,
                              30, 30, 31, 31, 32, 32, 33, 33, 34, 34, 35, 35, 36, 36, 37, 37, 38, 38,
                              39, 39, 40, 40, 41, 41, 42, 42, 43, 43, 44, 44, 45, 45, 46, 46, 47, 47,
                              48, 48, 49, 49, 50, 50};
        vector <int> array4(100, 7);
        vector <int> array5
        ,array6 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 11, 13, 14, 17, 16, 15, 18, 19, 20,
                   21, 23, 22, 25, 24, 27, 26, 29, 28, 30, 32, 31, 34, 33, 35, 37, 36, 39,
                   38, 40, 41, 42, 44, 43, 45, 46, 48, 47, 49, 50, 51, 53, 52, 54, 56, 55,
                   57, 58, 60, 59, 61, 62, 63, 65, 64, 66, 68, 67, 69, 70, 71, 73, 72, 74,
                   75, 76, 78, 77, 79, 80, 81, 83, 82, 84, 86, 85, 87, 88, 89, 91, 90, 92,
                   93, 94, 96, 95, 97, 98, 99, 100}
        ,array7 = {22, 19, 3, 34, 17, 40, 14, 12, 8, 36, 38, 24, 18, 31, 28, 4, 37, 35, 5, 10,
                   39, 7, 29, 20, 16, 1, 13, 27, 21, 15, 26, 11, 6, 25, 30, 2, 9, 33, 23, 32,
                   45, 42, 51, 47, 56, 59, 50, 63, 66, 54, 73, 41, 49, 60, 64, 72, 46, 61, 70,
                   58, 53, 68, 67, 43, 52, 48, 62, 57, 65, 69, 55, 44, 71, 74, 76, 75, 78, 77,
                   80, 79, 82, 81, 83, 84, 85, 87, 86, 88, 90, 89, 91, 92, 93, 95, 94, 96, 98,
                   97, 100, 99};
        for(int i=0;i<10000;i++)
            array5.push_back(i%5);
        vector<vector<int>> arrays{array1, array2, array3, array4, array5, array6, array7};
        vector<string> array_types= {"Sorted", "Reverse Sorted", "Duplicates", "Identical Elements", "Large Array",
                           "Partially Sorted", "Shuffled"};
        Time(arrays, sort_methods, array_types);
    }
    else if(input == "1" || input == "2")
    {
        vector<int> array;
        cout<<"Input array size"<<endl;
        int size;
        cin>>size;
        if(input == "1")
            for(int i=0; i<size; i++)
            {
                int nr;
                cin>>nr;
                array.push_back(nr);
            }
        else if(input == "2")
        {
            srand(time(0));
            for (int i = 0; i < size; i++)
                array.push_back(rand() % 1000 + 1);
        }
        for(int k=0;k<sort_methods.size();k++){
            string name;
            switch(k)
            {
                case 0: name = "MergeSort";
                    break;
                case 1: name = "QuickSort";
                    break;
                case 2: name = "HeapSort";
                    break;
                case 3: name = "TreeSort";
                    break;
            }
            cout<<name<<": ";
            GetDuration(array, sort_methods[k]);
            cout<<endl;
        }
    }

    return 0;
}