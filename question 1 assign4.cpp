#include <iostream>
#include <stdexcept>

class DoubleSubscriptedArray {
public:
    explicit DoubleSubscriptedArray(int = 10, int = 10); // default constructor
    DoubleSubscriptedArray(const DoubleSubscriptedArray&); // copy constructor
    ~DoubleSubscriptedArray(); // destructor
    DoubleSubscriptedArray& operator=(const DoubleSubscriptedArray&); // assignment operator
    bool operator==(const DoubleSubscriptedArray&) const; // equality operator
    bool operator!=(const DoubleSubscriptedArray& right) const {
        return !(*this == right);
    }

    int& operator()(int, int); // returns modifiable lvalue
    int operator()(int, int) const; // returns rvalue

private:
    size_t rows; // number of rows
    size_t columns; // number of columns
    int* ptr; // pointer to first element of pointer-based array
};

// constructor
DoubleSubscriptedArray::DoubleSubscriptedArray(int rows, int columns)
    : rows(rows > 0 ? rows : throw std::invalid_argument("Number of rows must be greater than 0")),
      columns(columns > 0 ? columns : throw std::invalid_argument("Number of columns must be greater than 0")),
      ptr(new int[rows * columns]) {
    for (size_t i = 0; i < rows * columns; ++i)
        ptr[i] = 0; // initialize pointer-based array elements to 0
}

// copy constructor
DoubleSubscriptedArray::DoubleSubscriptedArray(const DoubleSubscriptedArray& arrayToCopy)
    : rows(arrayToCopy.rows), columns(arrayToCopy.columns), ptr(new int[arrayToCopy.rows * arrayToCopy.columns]) {
    for (size_t i = 0; i < rows * columns; ++i)
        ptr[i] = arrayToCopy.ptr[i]; // copy into object
}

// destructor
DoubleSubscriptedArray::~DoubleSubscriptedArray() {
    delete[] ptr; // release pointer-based array space
}

// assignment operator
DoubleSubscriptedArray& DoubleSubscriptedArray::operator=(const DoubleSubscriptedArray& right) {
    if (&right != this) { // avoid self-assignment
        if (rows != right.rows || columns != right.columns) { // for Arrays of different sizes
            delete[] ptr; // deallocate original left-side Array
            rows = right.rows; // resize this object
            columns = right.columns;
            ptr = new int[rows * columns]; // create space for Array copy
        }

        for (size_t i = 0; i < rows * columns; ++i)
            ptr[i] = right.ptr[i]; // copy array into object
    }

    return *this; // enables x = y = z
}

// equality operator
bool DoubleSubscriptedArray::operator==(const DoubleSubscriptedArray& right) const {
    if (rows != right.rows || columns != right.columns)
        return false; // arrays of different sizes

    for (size_t i = 0; i < rows * columns; ++i)
        if (ptr[i] != right.ptr[i])
            return false; // Array contents are not equal

    return true; // Arrays are equal
}

// overloaded subscript operator for non-const Arrays
int& DoubleSubscriptedArray::operator()(int row, int column) {
    if (row < 0 || row >= rows || column < 0 || column >= columns)
        throw std::out_of_range("Subscript out of range");

    return ptr[row * columns + column]; // reference return
}

// overloaded subscript operator for const Arrays
int DoubleSubscriptedArray::operator()(int row, int column) const {
    if (row < 0 || row >= rows || column < 0 || column >= columns)
        throw std::out_of_range("Subscript out of range");

    return ptr[row * columns + column]; // returns copy of this element
}

int main() {
    DoubleSubscriptedArray array(3, 4);

    // Initialize array elements
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            array(i, j) = i + j; // Accessing elements using () operator
        }
    }

    // Display array elements
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << array(i, j) << " "; // Accessing elements using () operator
        }
        std::cout << std::endl;
    }

    return 0;
}
