/* C++ matrix multiplication */

#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

#define MAXN 300
typedef struct Matrix_s
{
    size_t R, C;
    int index[MAXN][MAXN];
} Matrix;

int main()
{
    fstream input("matrix.2.in", ios::in);

    // Read matrix 
    Matrix m1;
    input >> m1.R;
    input >> m1.C;
    for (size_t i = 0; i < m1.R * m1.C; i++)
        input >> m1.index[i / m1.C][i % m1.C];

    // Read matrix 
    Matrix m2;
    input >> m2.R;
    input >> m2.C;
    for (size_t i = 0; i < m2.R * m2.C; i++)
        input >> m2.index[i / m2.C][i % m2.C];

    if (m1.C != m2.R)
    {
        cout << "Error: matrices cannot be multiplied!" << endl;
        return 0;
    }

    // Product
    Matrix m3;
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
        cout << m3.index[(i-1) / m3.C][(i-1) % m3.C] << '\t';
        if (i % 5 == 0) cout << endl;
    }

    input.close();
    
    return 0;
}