#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <tuple>
#include <sstream>
#include <numeric>
// Unfortunately the std::reference_wrapper does not work as expected.
// So we will build our own one
// 还是不太懂？？？？    为自己的类构造以迭代器
class IntRef
{
    // Here we will store the reference
    std::tuple<int&> t;
public:
    // Constructor. Take reference and store it in tuple
    IntRef(int&& intV) : t(intV) {}     

    // Assignment to the referenced value
    int operator =(const int i) { std::get<0>(t) = i; return i; }      

    // Explicit type cast to int&
    operator int& () { return std::get<0>(t); }                        

    // And, return the reference
    decltype(&std::get<0>(t)) operator&() { return &std::get<0>(t); }  
};


// Some definitions to make reading easier
using IntRefV = std::vector<IntRef>;
using MatrixCIterator = std::vector<IntRef>::iterator;
using Columns = std::vector<int>;
using MatrixRIterator = Columns::iterator;


// The matrix
class Matrix
{
public:
    // Constructor defines the matrix size
    Matrix(size_t numberOfRows, size_t numberOfColumns);

    // Iterators for rows are simple, becuase we have vectors of columns. Use unterlying iterator
    MatrixRIterator rowIterBegin(size_t row) { return data[row].begin(); }
    MatrixRIterator rowIterEnd(size_t row) { return data[row].end(); }  

    // Column iterator is complicated. Retzurn iterator to vevtor of references to column values
    MatrixCIterator columnIterBegin(size_t column) { return columnReferences[column].begin(); }
    MatrixCIterator columnIterEnd(size_t column) { return columnReferences[column].end(); }

    // Access data of matrix
    std::vector<int>& operator [] (const size_t row) { return data[row]; }

    // And, for debug purposes. Output all data
    friend std::ostream& operator << (std::ostream& os, const Matrix& m) {
        std::for_each(m.data.begin(), m.data.end(), [&os](const Columns& columns) {std::copy(columns.begin(), columns.end(), std::ostream_iterator<int>(os, " ")); std::cout << '\n'; });
        return os;
    }
protected:
    //The matrix, vector of vector of int
    std::vector<Columns> data; 

    // The references to columns in data
    std::vector<IntRefV> columnReferences{};    
};

// Constructor. Build basic matrix and then store references to columns in data 
Matrix::Matrix(size_t numberOfRows, size_t numberOfColumns) : data(numberOfRows, std::vector<int>(numberOfColumns)), columnReferences(numberOfColumns)
{
    for (size_t column = 0; column < numberOfColumns; ++column) 
        for (size_t row = 0; row < numberOfRows; ++row)
            columnReferences[column].emplace_back(IntRef(std::move(data[row][column]))); // Std::move creates a rvalue reference (needed for constructor, nothing will be moved)
}



// Some test data for the istream_iterator
std::istringstream testData("1 2 10");



// Test the matrix
int main()
{
    // Define a matrix with 3 rows and 4 columns
    Matrix matrix(3, 4);
    // Test 1: Fill all values in column 2 with 42
    for (MatrixCIterator ci = matrix.columnIterBegin(2); ci != matrix.columnIterEnd(2); ++ci) {
        *ci = 42;
    }
    std::cout << matrix << "Column 2 filled with 42\n\n";

    // Test 2: Read input from istream and copy put that in column 1
    std::copy_n(std::istream_iterator<int>(testData), 3, matrix.columnIterBegin(1));
    std::cout << matrix << "Column 1 filled with testData '"<< testData.str() << "'\n\n";

    // Test 3: Copy column 2 to cout (Print column 2)
    std::copy(matrix.columnIterBegin(2), matrix.columnIterEnd(2), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "This is column 2\n\n";

    // Test 4: Sum up the first 2 values of column 1 and show result
    std::cout << "\nSum of first 2 values of column 1:  " << std::accumulate(matrix.columnIterBegin(1), matrix.columnIterBegin(1)+2, 0) << "\n\n";

    // Test 5: Fill all values in row 0 with 33
    std::for_each(matrix.rowIterBegin(0), matrix.rowIterEnd(0), [](int& i) { i = 33; });
    std::cout << matrix << "Row 0 filled with 33\n\n";

    return 0;
}