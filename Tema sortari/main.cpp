#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>
//#include <cstdlib>

using namespace std;

ifstream in("date.in");


void bubble_sort(int n, int v[])
{
    int ok=0;
    while(ok==0)
    {
        ok=1;
        for(int i=1;i<n;i++)
            if(v[i]>v[i+1])
        {
            int aux = v[i];
            v[i] = v[i+1];
            v[i+1] = aux;
            ok = 0;
        }
    }
}

void count_sort(int n, int v[], int Max)
{
    int* fr = new int [Max+1];
    for(int i=0;i<=Max;i++)
        fr[i]=0;
    for(int i=1;i<=n;i++)
        fr[v[i]]++;
    n = 0;
    for(int i=0;i<=Max;i++)
        for(int j=1;j<=fr[i];j++)
            v[++n] = i;
    delete[] fr;
}

void count_for_radix(int n, int v[], int j)
{
    int fr[10];
    int* x = new int [n+1];
    for(int i = 0; i < 10; i++)
        fr[i] = 0;
    for(int i = 1; i <=n; i++)
        fr[v[i] / j % 10]++;
    for(int i = 1; i < 10; i++)
        fr[i] = fr[i] + fr[i-1];
    for(int i = n; i >= 1; i--)
        {x[fr[v[i] / j % 10]] = v[i]; fr[v[i] / j % 10]--;}
    for(int i = 1; i <= n; i++)
        v[i] = x[i];
    delete[] x;
}

void radix_sort(int n, int v[])
{
    int nr_max = v[1];
    for(int i=2;i<=n;i++)
        if(v[i] > nr_max)
            nr_max = v[i];

    for(int i=1; nr_max/i > 0; i=i*10)
        count_for_radix(n,v,i);
}

void interclasare_merge_sort(int n, int v[], int s, int d)
{
    int i=s,j=(s+d)/2+1,k=0;
    int* y = new int [n+1];
    while(i<=(s+d)/2 && j<=d)
       { k++;
         if(v[i]<v[j]) y[k]=v[i++];
         else y[k]=v[j++]; }
    for(int l=i;l<=(s+d)/2;l++) y[++k]=v[l];
    for(int l=j;l<=d;l++) y[++k]=v[l];
    for(int l=1;l<=k;l++) v[s+l-1]=y[l];
    delete[] y;
}

void merge_sort(int n, int v[], int s, int d)
{
    if(d - s <= 1)
        { if(v[s]>v[d])
            { int aux=v[s]; v[s]=v[d]; v[d]=aux; }
        }
      else
        { int j=(s+d)/2;
          merge_sort(n,v,s,j);
          merge_sort(n,v,j+1,d);
          interclasare_merge_sort(n,v,s,d);
        }
}

int poz(int n, int v[], int s, int d)
{ int i=s,j=d,m1=0,m2=-1;
  while(i<j)
       { if(v[i]>v[j])
           { int aux=v[i]; v[i]=v[j]; v[j]=aux;
             if(m1==0) { m1=1; m2=0; }
             else { m1=0; m2=-1; }
           }
         i+=m1; j+=m2;
       }
  return i;
}

void quick_sort(int n, int v[], int s, int d)
{ int k;
  if(s<d)
    { k=poz(n,v,s,d);
      quick_sort(n,v,s,k-1);
      quick_sort(n,v,k+1,d);
    }
}

int test_sort(int n, int v[])
{
    for(int i = 2; i <= n; i++)
        if(v[i] < v[i-1])
            return 0;
    return 1;
}

int main()
{
    int T;
    int N;
    int Max;
    in >> T; //Numarul total de teste
    srand((unsigned)time(0));
    for(int i = 1; i <= T; i++)
    {
        in >> N; // Lungimea vectorului de sortat
        in >> Max; // Maximul posibil din vector
        cout << "Testul " << i << ": N = " << N << "; Max = " << Max << "\n";

        int* v = new int[N+1]; // Vectorul care va fi sortat
        int* x = new int[N+1]; // Vectorul generat
        for(int j = 1; j <= N; j++)
        {
            x[j] = rand() % (Max + 1); // Generam vectorul
            v[j] = x[j];
        }

        for(int j = 1; j <= 6; j++)
        {
            time_t timp_start;
            time_t timp_end;

            if(j == 1)
                if(i <= 6)
                {
                    time(&timp_start);
                    bubble_sort(N,v);
                    time(&timp_end);
                    if(test_sort(N,v) == 1)
                        cout << "Bubble sort: " << timp_end - timp_start << "s; A sortat corect\n";
                    else
                        cout << "Bubble sort: " << timp_end - timp_start << "s; A sortat gresit\n";
                }
                else
                    cout << "Bubble sort nu poate sorta\n";
            else if(j == 2)
            {
                time(&timp_start);
                count_sort(N,v,Max);
                time(&timp_end);
                if(test_sort(N,v) == 1)
                    cout << "Count sort: " << timp_end - timp_start << "s; A sortat corect\n";
                else
                    cout << "Count sort: " << timp_end - timp_start << "s; A sortat gresit\n";
            }
            else if(j == 3)
            {
                time(&timp_start);
                radix_sort(N,v);
                time(&timp_end);
                if(test_sort(N,v) == 1)
                    cout << "Radix sort: " << timp_end - timp_start <<  "s; A sortat corect\n";
                else
                    cout << "Radix sort: " << timp_end - timp_start <<  "s; A sortat gresit\n";
            }
            else if(j == 4)
                if(i <= 9)
                {
                    time(&timp_start);
                    merge_sort(N,v,1,N);
                    time(&timp_end);
                    if(test_sort(N,v) == 1)
                        cout << "Merge sort: " << timp_end - timp_start <<  "s; A sortat corect\n";
                    else
                        cout << "Merge sort: " << timp_end - timp_start <<  "s; A sortat gresit\n";
                }
                else
                    cout << "Merge sort nu poate sorta\n";
            else if(j == 5)
                if(i <= 9)
                {
                    time(&timp_start);
                    quick_sort(N,v,1,N);
                    time(&timp_end);
                    if(test_sort(N,v) == 1)
                        cout << "Quick sort: " << timp_end - timp_start <<  "s; A sortat corect\n";
                    else
                        cout << "Quick sort: " << timp_end - timp_start <<  "s; A sortat gresit\n";
                }
                else
                    cout << "Quick sort nu poate sorta\n";
            else if(j == 6)
            {
                time(&timp_start);
                sort(v+1,v+N+1);
                time(&timp_end);
                if(test_sort(N,v) == 1)
                    cout << "Functia sort: " << timp_end - timp_start << "s; A sortat corect\n";
                else
                    cout << "Functia sort: " << timp_end - timp_start << "s; A sortat gresit\n";
            }

            for(int k = 1; k <= N; k++)
                v[k] = x[k];

        }
        delete[] v;
        delete[] x;
    }
    return 0;
}
