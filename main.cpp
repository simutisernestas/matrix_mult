/* C++ matrix multiplication */

#include <iostream>
#include <fstream>
#include <iostream>
#include <chrono>
#include <string>

using std::cout, std::endl, std::ios, std::fstream;
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

    ~Matrix_d()
    {
        delete index;
    }
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
    fstream input("../matrix2.11.in", ios::in);

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

    MatrixD m2T;
    m2T.R = m2.R;
    m2T.C = m2.C;
    m2T.index = new int[m2.C * m2.R];

    // Transpose m2
    int i{0};
    for (size_t r = 0; r < m2.C; ++r)
    {
        for (size_t c = 0; c < m2.R; ++c)
        {
            m2T.index[i] = m2.index[r + c * m2.C];
            ++i;
        }
    }

    input.close();

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
    size_t nRows = m3.R, nCols = m3.C, nInner = m1.C;
    int sum{0};
    for (size_t r = 0; r < nRows; ++r)
    {
        for (size_t c = 0; c < nCols; ++c)
        {
            sum = 0;
            for (size_t i = 0; i < nInner; ++i)
            {
                sum += m1.index[i + r * nInner] * m2T.index[i + c * nInner];
            }
            m3.index[c + r * nCols] = sum;
        }
    }

    // Print result
    // for (int k = 0; k < m3.R * m3.C; ++k)
    // {
    //     cout << m3.index[k] << " ";
    //     if ((k + 1) % m2.C == 0)
    //         cout << endl;
    // }
}

int main()
{
    // Time the program
    Timer t{};

    // TODO: read matrix transpose and change product

    // staticProduct();

    dynamicProduct(); // ~2.5s

    return 0;
}