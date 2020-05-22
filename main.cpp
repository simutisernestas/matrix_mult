/* C++ matrix multiplication */

#include <iostream>
#include <fstream>
#include <iostream>
#include <chrono>
#include <string>
using namespace std;
using namespace std::chrono;

struct Timer
{
    std::chrono::time_point<std::chrono::high_resolution_clock> start;

    Timer()
    {
        start = high_resolution_clock::now();
    }

    ~Timer()
    {
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(stop - start);

        cout << "Time taken : " << duration.count() << " microseconds" << endl;
    }
};

// static matrix
#define MAXN 300
typedef struct Matrix_s
{
    size_t R, C;
    int index[MAXN][MAXN];
} MatrixS;

// dynamic matrix
typedef struct Matrix_d
{
    size_t R, C;
    // Indexing - arr[i*sizeY+j] == arr[i][j]
    int *index;
    // ~Matrix_d()
    // {
    //     delete index;
    // }
} MatrixD;

void staticProduct()
{
    fstream input("matrix.2.in", ios::in);

    // Read matrix
    MatrixS m1;
    input >> m1.R;
    input >> m1.C;
    for (size_t i = 0; i < m1.R * m1.C; i++)
        input >> m1.index[i / m1.C][i % m1.C];

    // Read matrix
    MatrixS m2;
    input >> m2.R;
    input >> m2.C;
    for (size_t i = 0; i < m2.R * m2.C; i++)
        input >> m2.index[i / m2.C][i % m2.C];

    if (m1.C != m2.R)
    {
        cout << "Error: matrices cannot be multiplied!" << endl;
        return;
    }

    // Product
    MatrixS m3;
    m3.R = m1.R;
    m3.C = m2.C;
    int sum{};
    for (size_t i = 0; i < m3.R * m3.C; i++)
    {
        sum = 0;
        for (size_t j = 0; j < m1.C; j++)
        {
            sum += m1.index[i / m3.C][j % m1.C] * m2.index[j][i % m3.C];
        }
        m3.index[i / m3.C][i % m3.C] = sum;
    }

    // Print matrix
    for (size_t i = 1; i <= m3.R * m3.C; i++)
    {
        cout << m3.index[(i - 1) / m3.C][(i - 1) % m3.C] << '\t';
        if (i % 5 == 0)
            cout << endl;
    }

    input.close();
}

void dynamicProduct()
{
    fstream input("matrix.2.in", ios::in);

    // Read matrix
    MatrixD m1;
    input >> m1.R;
    input >> m1.C;
    m1.index = new int[m1.C * m1.R];
    for (size_t i = 0; i < m1.R * m1.C; i++)
        input >> m1.index[i];

    // Read matrix
    MatrixD m2;
    input >> m2.R;
    input >> m2.C;
    m2.index = new int[m2.C * m2.R];
    for (size_t i = 0; i < m2.R * m2.C; i++)
        input >> m2.index[i];

    if (m1.C != m2.R)
    {
        cout << "Error: matrices cannot be multiplied!" << endl;
        return;
    }

    // Product
    MatrixD m3;
    m3.R = m1.R;
    m3.C = m2.C;
    m3.index = new int[m3.C * m3.R];
    int sum{};
    for (size_t i = 2; i < m3.R * m3.C; i++)
    {
        sum = 0;
        for (size_t j = 0; j < m1.C; j++)
        {
            // arr[i*sizeY+j] == arr[i][j]
            // cout << m3.R * m3.C << endl;
            // cout << (i / m3.C) * m3.R + (j % m1.C) << " " << j * m3.R + (i % m3.C) << endl;
            // sum += m1.index[i * m1.C + j] * m2.index[j * m1.C + j];
            sum += m1.index[(i % m1.R) * m1.C + j] * m2.index[j * m2.C + (i % m2.C)];
            // cout << m1.index[i * m1.C + j] << " " << m2.index[j * m2.C + i] << endl;
            // cout << (i % m1.R) * m1.C + j << " " << j * m2.C + (i % m2.C) << endl;
            cout << m1.index[i] << endl;
        }
        // m3.index[i / m3.C][i % m3.C]
        // cout << (i / m3.C) * m3.R + (i % m3.C) << endl;
        // m3.index[(i / m3.C) * m3.R + (i % m3.C)] = sum;
        m3.index[i] = sum;
        // cout << sum << endl;
        return;
    }

    // for (size_t i = 0; i < 10; i++)
    // {
    //     cout << i;
    // }

    input.close();
}

int main()
{
    // Time the program
    Timer t{};

    // staticProduct();
    dynamicProduct();

    return 0;
}