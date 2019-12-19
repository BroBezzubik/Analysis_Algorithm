#include <ctime>
#include <exception>
#include <iostream>
#include <random>
#include <stdint.h>


class Matrix {
public:
	Matrix(unsigned rows = 1, unsigned columns = 1);
	Matrix(int randMax, unsigned rows = 1, unsigned columns = 1);
	Matrix(const Matrix& other);
	~Matrix();

	Matrix classicMult(const Matrix& other, std::clock_t& time);
	Matrix classicBufferMult(const Matrix& other, std::clock_t& time);

	Matrix vinogradMult(const Matrix& other, std::clock_t& time);
	Matrix vinogradImprMult(const Matrix& other, std::clock_t& time);

	void outStream();
private:
	unsigned rows;
	unsigned columns;
	unsigned** data;
};