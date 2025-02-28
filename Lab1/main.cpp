#include <iostream>
#include <chrono>
#include <vector>
#include <cmath>

using namespace std;
using namespace std::chrono;

typedef unsigned long long int Integer;

Integer Recursive(int n)
{
    if(n<=1)
        return n;
    return Recursive(n-1)+Recursive(n-2);
}

Integer DynamicProgramming(int n)
{
    vector<Integer> array;
    array.push_back(0);
    array.push_back(1);
    for(int i=2; i<=n;i++)
    {
        int m = array.size();
        array.push_back(array[m-1]+array[m-2]);
    }
    return array[n];
}


void multiply(vector<vector<Integer>>& F,
              vector<vector<Integer>>& M)
{
    Integer x = F[0][0] * M[0][0] + F[0][1] * M[1][0];
    Integer y = F[0][0] * M[0][1] + F[0][1] * M[1][1];
    Integer z = F[1][0] * M[0][0] + F[1][1] * M[1][0];
    Integer w = F[1][0] * M[0][1] + F[1][1] * M[1][1];

    F[0][0]=x;
    F[0][1]=y;
    F[1][0]=z;
    F[1][1]=w;
}
void power(vector<vector<Integer>>& F, int n)
{
    vector<vector<Integer>> M={{1,1}, {1,0}};
    for(int i=2; i<=n;i++)
        multiply(F,M);
}

Integer MatrixPower(int n)
{
    if(n == 0 )
        return 0;
    vector<vector<Integer>> F={{1, 1}, {1, 0}};
    power(F,n-1);
    return F[0][0];
}


Integer BinetFormula(int n)
{
    float phi = (1+sqrt(5));
    float phi1= (1-sqrt(5));
    return (pow(phi, n)-pow(phi1,n))/(pow(2,n)*sqrt(5));
}

Integer Iterative(int n)
{
    if(n<=1)
        return n;
    Integer n1 = 0, n2=1, nr;
    for(int i=2;i<=n;i++)
    {
        nr=n1+n2;
        n1=n2;
        n2=nr;
    }
    return nr;
}

Integer Recursive_Iter(int n, Integer n1, Integer n2)
{
    if(n<1)
        return n1;
    else
        return Recursive_Iter(n-1, n1+n2, n1);
}

Integer Recursive2(int n)
{
    return Recursive_Iter(n, 0, 1);
}


void Doubling_Iter(int n, Integer arr[])
{
    if(n==0)
    {
        arr[0]=0;
        arr[1]=1;
        return;
    }
    Doubling_Iter((n/2),arr);
    Integer Fn = arr[0];
    Integer Fn_1 = arr[1];
    Integer F2n = Fn*(2*Fn_1 - Fn);
    Integer F2n_1 = Fn*Fn + Fn_1*Fn_1;
    if(n%2 == 0)
    {
        arr[0]=F2n;
        arr[1]=F2n_1;
    }
    else
    {
        arr[0]=F2n_1;
        arr[1]=F2n+F2n_1;
    }
}

Integer Doubling(int n)
{
    Integer arr[2]={0};
    Doubling_Iter(n, arr);
    return arr[0];
}



void GetDuration(int n, Integer (*function)(int))
{
    auto start = high_resolution_clock::now();
    function(n);
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

void Value(int n)
{
    //cout<<"Recursive Result: "<<Recursive(n)<<endl;
    cout<<"Dynamic Result: "<<DynamicProgramming(n)<<endl;
    cout<<"Matrix Power Result: "<<MatrixPower(n)<<endl;
    cout<<"Binet Formula Result: "<<BinetFormula(n)<<endl;
    cout<<"Iterative Result: "<<Iterative(n)<<endl;
    cout<<"Recursive2 Result: "<<Recursive2(n)<<endl;
    cout<<"Doubling Result: "<<Doubling(n)<<endl;
}

void Time(vector <int> input,Integer (*function)(int), string method)
{
    cout<<method<<" Method"<<endl;
    int i=1;
    for(auto n: input)
    {

        cout<<n<<": ";
        GetDuration(n, function);
        cout<<"\t";
        if(i%4==0)
            cout<<endl;
        i++;
    }
    cout<<endl<<endl;
}


int main(){

    vector<int> series1={5, 7, 10, 12, 15, 17, 20, 22, 25, 27, 30, 32, 35, 37, 40, 42, 45}
    ,series2={501, 631, 794, 1000, 1259, 1585, 1995, 2512, 3162, 3981, 5012, 6310, 7943, 10000, 12589, 15849};



    Time(series1, Recursive, "Recursive");
    Time(series1, Recursive2, "Improved Recursive");
    Time(series1, DynamicProgramming, "Dynamic Programming");
    Time(series1, Iterative, "Iterative");
    Time(series1, MatrixPower, "Matrix Power");
    Time(series1, Doubling, "Fast Doubling");
    Time(series1, BinetFormula, "Binet Formula");

    //Time(series2, Recursive, "Recursive");
    Time(series2, Recursive2, "Improved Recursive");
    Time(series2, DynamicProgramming, "Dynamic Programming");
    Time(series2, Iterative, "Iterative");
    Time(series2, MatrixPower, "Matrix Power");
    Time(series2, Doubling, "Fast Doubling");
    Time(series2, BinetFormula, "Binet Formula");

    return 0;
}