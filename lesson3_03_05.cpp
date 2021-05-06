#include <iostream>
#include <list>
#include <iterator>
#include <numeric>
#include <vector>

// Task 1. Написать функцию, добавляющую в конец списка вещественных чисел элемент, значение которого равно среднему арифметическому всех его элементов.
double listInsert(std::list<double> &listing)
{
    double tmp;
    if (listing.empty())
    return 0;
    else tmp = (std::accumulate(listing.begin(), listing.end(), 0.0)) / listing.size();
    listing.push_back(tmp);
    return tmp;
}

 
// Task 2. Создать класс, представляющий матрицу. Реализовать в нем метод, вычисляющий определитель матрицы.

class Matrix
{
private:
	int n, m;
	
public:
	int** arr;
	Matrix()
	{ 
		n = m = 1;
		arr = new int* [n];
		for (int i = 0; i < 1; i++) 
		{ 
			arr[i] = new int[m];
		};
	}

	Matrix(int n_size, int m_size) 
	{
		n = n_size; m = m_size;
		arr = new int* [n];
		for (int i = 0; i < n; i++) 
		{
			arr[i] = new int[m];
		};
	}
	~Matrix() { for (int i = 0; i < n; i++) delete arr[i]; delete[]arr; }

	void create() 
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				arr[i][j] = rand() % 5 + 2;
	}

	void print()
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				std::cout << arr[i][j] << '\t';
			}
			std::cout << std::endl;
		}
	}

	void getMatrixStripped(int** matrix, int size, int row, int col, int** newMatrix) {
		int offsetRow = 0; 
		int offsetCol = 0; 
		for (int i = 0; i < size - 1; i++) {
			if (i == row) {
				offsetRow = 1; 
			}

			offsetCol = 0; 
			for (int j = 0; j < size - 1; j++) {
				if (j == col) {
					offsetCol = 1; 
				}

				newMatrix[i][j] = matrix[i + offsetRow][j + offsetCol];
			}
		}
	}

	
	int matrixDet(int** matrix, int size) {
		int det = 0;
		int degree = 1; 


	
	if (size == 1) {
		return matrix[0][0];
	}
	
	else if (size == 2) {
		return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	}
	else {
		
		int** newMatrix = new int* [size - 1];
		for (int i = 0; i < size - 1; i++) {
			newMatrix[i] = new int[size - 1];
		}

		
		for (int j = 0; j < size; j++) {
			getMatrixStripped(matrix, size, 0, j, newMatrix);
			det = det + (degree * matrix[0][j] * matrixDet(newMatrix, size - 1));
			degree = -degree;
		}

		for (int i = 0; i < size - 1; i++) {
			delete[] newMatrix[i];
		}
		delete[] newMatrix;
	}

		return det;
	}

};




// Task 3. Реализовать собственный класс итератора, с помощью которого можно будет проитерироваться по диапазону целых чисел в цикле for-range-based.
class RangeCycle
{
private:
	const std::vector<int>& m_values;
	class Impl
	{
	private:
		size_t m_index;
		const std::vector<int>& m_values;
	public:
		using value_type = int;
		using const_reference = const int&;
		Impl(const size_t v, const std::vector<int>& values) : m_index(v), m_values(values) {}
		const_reference operator*() const { return m_values[m_index]; }
		Impl& operator++()
		{
			++m_index;
			return *this;
		}
		bool operator!=(const Impl& rhs) { return m_index != rhs.m_index; }
	};

public:
	RangeCycle(const std::vector<int>& values) : m_values(values) {}
	typedef Impl iterator;
	iterator begin() const { return Impl(0, m_values); }
	iterator end() const { return Impl(m_values.size(), m_values); }
};



int main()
{
	srand(time(0)); // рандомайз для матрицы


    // Задание 1.
	std::cout << "Task 1." << '\n'<<std::endl;
    std::list<double> listOriginal{ 1.2, 2.8, 1.55, 2.45, 7.00 };
    std::cout << "Original list" << '\t';
    copy(listOriginal.begin(), listOriginal.end(), std::ostream_iterator<double>(std::cout, " "));
    std::cout << std::endl;
    std::cout << "Average  " << listInsert(listOriginal) << std::endl;
    std::cout << "New list" << '\t';
    copy(listOriginal.begin(), listOriginal.end(), std::ostream_iterator<double>(std::cout, " "));
	std::cout << '\n'<< '\n'<< std::endl;


	// Задание 2.
	
	std::cout << "Task 2." << '\n' << std::endl;
	Matrix Task2 (3, 3);
	Task2.create();
	std::cout << "Matrix Task2:\n";
	Task2.print();
	int det = Task2.matrixDet(Task2.arr, 3);
	std::cout << "Determinant is " << det << std::endl;
	std::cout << '\n' << '\n' << std::endl;


    // Задание 3.
	std::cout << "Task 3." << '\n' << std::endl;
	const std::vector<int> values = { 4, 3, 2, 1 };
	for (const int& n : RangeCycle(values))
	{
		std::cout << n << std::endl;
	}

	return 0;
}
