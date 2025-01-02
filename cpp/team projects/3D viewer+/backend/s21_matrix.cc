#include "s21_matrix.h"

// Constructors/Destructors

S21Matrix::S21Matrix() noexcept
    : rows_(0), cols_(0), matrix_(nullptr) {}  // Default constructor

S21Matrix::S21Matrix(int rows, int cols) : rows_{rows}, cols_{cols} {
  if (rows_ < 0 || cols_ < 0)
    throw std::length_error("Matrix size must be non-negative");  // exception
  matrix_ = new float[rows_ * cols_]{};
}  // matrix rows*cols size

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_{other.rows_}, cols_{other.cols_} {
  matrix_ = new float[rows_ * cols_];
  std::copy(other.matrix_, other.matrix_ + rows_ * cols_, matrix_);
}  // copy

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_{other.rows_}, cols_{other.cols_}, matrix_{other.matrix_} {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}  // move

S21Matrix::~S21Matrix() noexcept { Free(); }  // Destructor

// getters

int S21Matrix::getRows() const noexcept { return rows_; }  // getter/accessor

int S21Matrix::getCols() const noexcept { return cols_; }  // getter/accessor

// setters

void S21Matrix::setRow(int row) {
  if (row < 0) throw std::length_error("Matrix size must be non-negative");
  if (row != rows_) {
    S21Matrix temp(row, cols_);
    int min = std::min(rows_, row);
    for (int i = 0; i < min; i++)
      for (int j = 0; j < cols_; j++) temp(i, j) = (*this)(i, j);
    *this = std::move(temp);
  }
}  // setter/mutator

void S21Matrix::setCol(int col) {
  if (col < 0) throw std::length_error("Matrix size must be non-negative");
  if (col != cols_) {
    S21Matrix temp(rows_, col);
    int min = std::min(cols_, col);
    for (int i = 0; i < rows_; i++)
      for (int j = 0; j < min; j++) temp(i, j) = (*this)(i, j);
    *this = std::move(temp);
  }
}  // setter/mutator

// Public methods

bool S21Matrix::EqMatrix(const S21Matrix& other) const noexcept {
  bool result = false;
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    result = true;
    for (int i = 0; i < rows_ && result; i++)
      for (int j = 0; j < cols_ && result; j++)
        if (std::abs(other(i, j) - (*this)(i, j)) > 1e-7) result = false;
  }
  return result;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (!(rows_ == other.rows_ && cols_ == other.cols_))
    throw std::out_of_range("Different matrix sizes");
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) (*this)(i, j) += other(i, j);
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (!(rows_ == other.rows_ && cols_ == other.cols_))
    throw std::out_of_range("Different matrix sizes");
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) (*this)(i, j) -= other(i, j);
}

void S21Matrix::MulNumber(const float num) noexcept {
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) (*this)(i, j) *= num;
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_)
    throw std::out_of_range("Incorrect matrixes size for multiplication");
  S21Matrix temp(rows_, other.cols_);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < other.cols_; j++)
      for (int k = 0; k < cols_; k++) temp(i, j) += (*this)(i, k) * other(k, j);
  *this = std::move(temp);
}

S21Matrix S21Matrix::Transpose() noexcept {
  S21Matrix res(cols_, rows_);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) res(j, i) = (*this)(i, j);
  return res;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) throw std::out_of_range("Matrix isn't square");
  S21Matrix res(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      res(i, j) = Minor(i, j);
      if ((i + j) % 2) res(i, j) = -res(i, j);
    }
  }
  return res;
}

// Gauss method
float S21Matrix::Determinant() const {
  if (rows_ != cols_) throw std::out_of_range("Matrix isn't square");
  float res = 1;
  S21Matrix tmp(*this);
  int size = rows_;
  for (int i = 0; i < size; i++) {
    int pivoting = i;
    for (int j = i + 1; j < size; j++)
      if (std::abs(tmp(j, i)) > std::abs(tmp(pivoting, i))) pivoting = j;

    if (std::abs(tmp(pivoting, i)) < 1e-7) {
      res = 0;
      break;
    }
    if (i != pivoting) {
      res = -res;
      for (int j = 0; j < cols_; j++) std::swap(tmp(i, j), tmp(pivoting, j));
    }
    res *= tmp(i, i);
    for (int j = i + 1; j < size; j++) {
      float koef = tmp(j, i) / tmp(i, i);
      for (int k = i; k < size; k++) tmp(j, k) -= tmp(i, k) * koef;
    }
  }
  return res;
}

S21Matrix S21Matrix::InverseMatrix() const {
  if (rows_ != cols_) throw std::out_of_range("Matrix isn't square");
  float det = Determinant();
  if (std::abs(det) < 1e-7)
    throw std::out_of_range("Determinant must be non-zero");
  return CalcComplements().Transpose() * (1.0 / det);
}

// operators

bool S21Matrix::operator==(const S21Matrix& other) const {
  return EqMatrix(other);
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix tmp(*this);
  tmp.SumMatrix(other);
  return tmp;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix tmp(*this);
  tmp.SubMatrix(other);
  return tmp;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*(float num) const noexcept {
  S21Matrix tmp(*this);
  tmp.MulNumber(num);
  return tmp;
}

S21Matrix operator*(float num, const S21Matrix& matrix) noexcept {
  S21Matrix tmp = matrix * num;
  return tmp;
}

S21Matrix& S21Matrix::operator*=(float num) {
  MulNumber(num);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix tmp(*this);
  tmp.MulMatrix(other);
  return tmp;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  setRow(other.rows_);
  setCol(other.cols_);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) (*this)(i, j) = other(i, j);
  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) {
  if (this != &other) {
    Free();
    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
    std::swap(matrix_, other.matrix_);
  }
  return *this;
}

float& S21Matrix::operator()(int row, int col) & {
  return const_cast<float&>(GetElem(row, col));
}

const float& S21Matrix::operator()(int row, int col) const& {
  return GetElem(row, col);
}

// Private methods

const float& S21Matrix::GetElem(int row, int col) const {
  if (!(row < rows_ && col < cols_ && row >= 0 && col >= 0)) {
    std::cout << row << ' ' << col << std::endl;
    throw std::out_of_range("Index is out of range this matrix");
  }
  return matrix_[row * cols_ + col];
}

void S21Matrix::Free() noexcept {
  delete[] matrix_;
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

float S21Matrix::Minor(int row, int col) const {
  S21Matrix temp(rows_ - 1, rows_ - 1);
  int shift_i = 0;
  for (int i = 0; i < rows_ - 1; i++) {
    if (i == row) shift_i = 1;
    int shift_j = 0;
    for (int j = 0; j < cols_ - 1; j++) {
      if (j == col) shift_j = 1;
      temp(i, j) = (*this)(i + shift_i, j + shift_j);
    }
  }
  return temp.Determinant();
}