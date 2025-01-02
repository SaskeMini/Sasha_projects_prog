#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() {
  rows_ = 3;
  cols_ = 3;
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = 0;
    }
  }
}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows <= 0 || cols <= 0) {
    throw exception();
  }
  matrix_ = new double *[rows];
  for (int i = 0; i < rows; i++) {
    matrix_[i] = new double[cols];
    for (int j = 0; j < cols; j++) {
      matrix_[i][j] = 0;
    }
  }
  rows_ = rows;
  cols_ = cols;
}

S21Matrix::~S21Matrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

S21Matrix::S21Matrix(const S21Matrix &other) {
  cols_ = other.cols_;
  rows_ = other.rows_;
  matrix_ = new double *[other.rows_] { nullptr };
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[other.cols_];
  }
  for (int i = 0; i < other.rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix &&other) {
  swap(rows_, other.rows_);
  swap(cols_, other.cols_);
  swap(matrix_, other.matrix_);
  other.matrix_ = nullptr;
}

int S21Matrix::getrows() { return rows_; }

int S21Matrix::getcols() { return cols_; }

double **S21Matrix::getmatrix() { return matrix_; }

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool res = true;
  if (matrix_ == nullptr || other.matrix_ == nullptr) {
    throw exception();
  } else if (getcols() != other.cols_ || getrows() != other.rows_) {
    res = false;
  }
  if (res == 1) {
    for (int i = 0; i < getrows(); i++) {
      for (int j = 0; j < getcols(); j++) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-7) {
          res = false;
        }
      }
    }
  }
  return res;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (matrix_ == nullptr || other.matrix_ == nullptr) {
    throw exception();
  } else if (cols_ != other.cols_ || rows_ != other.rows_) {
    throw exception();
  }
  for (int i = 0; i < getrows(); i++) {
    for (int j = 0; j < getcols(); j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (matrix_ == nullptr || other.matrix_ == 0) {
    throw exception();
  } else if (getcols() != other.cols_ || getrows() != other.rows_) {
    throw exception();
  }
  for (int i = 0; i < getrows(); i++) {
    for (int j = 0; j < getcols(); j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  if (matrix_ == nullptr) {
    throw exception();
  }
  for (int i = 0; i < getrows(); i++) {
    for (int j = 0; j < getcols(); j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (matrix_ == nullptr || other.matrix_ == 0) {
    throw exception();
  } else if (getcols() != other.rows_) {
    throw exception();
  }
  S21Matrix res(rows_, other.cols_);
  for (int i = 0; i < getrows(); i++) {
    for (int j = 0; j < getcols(); j++) {
      for (int x = 0; x < getcols(); x++) {
        res.matrix_[i][j] += matrix_[i][x] * other.matrix_[x][j];
      }
    }
  }
  if (rows_ > 0 && cols_ > 0 && matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      if (matrix_[i] != nullptr) {
        delete[] matrix_[i];
      }
    }
    delete[] matrix_;
  }
  cols_ = res.cols_;
  rows_ = res.rows_;
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = res.matrix_[i][j];
    }
  }
}

S21Matrix S21Matrix::Transpose() {
  if (matrix_ == nullptr) {
    throw exception();
  }
  S21Matrix res(getcols(), getrows());
  for (int i = 0; i < getrows(); i++) {
    for (int j = 0; j < getcols(); j++) {
      res.matrix_[i][j] = matrix_[j][i];
    }
  }
  return res;
}

S21Matrix S21Matrix::CalcComplements() {
  if (matrix_ == nullptr) {
    throw exception();
  }
  if (cols_ != rows_) {
    throw exception();
  }
  S21Matrix result(rows_, cols_);
  if (cols_ == 1) {
    result.matrix_[0][0] = matrix_[0][0];
  } else {
    for (int j = 0; j < rows_; j++) {
      for (int i = 0; i < cols_; i++) {
        S21Matrix xz(rows_ - 1, cols_ - 1);
        double res_minor = 0;
        int check_z = 0;
        for (int x = 0; x < rows_; x++) {
          if (x == j) {
            check_z = 1;
          } else {
            int check = 0;
            for (int y = 0; y < cols_; y++) {
              if (y == i) {
                check = 1;
              } else {
                xz.matrix_[x - check_z][y - check] = matrix_[x][y];
              }
            }
          }
        }
        res_minor = xz.Determinant();
        if ((j + i) % 2 != 0) {
          result.matrix_[j][i] += -1 * res_minor;
        } else {
          result.matrix_[j][i] += res_minor;
        }
      }
    }
  }
  return result;
}

double S21Matrix::Determinant() {
  double result = 0;
  if (matrix_ == nullptr) {
    throw exception();
  }
  if (cols_ != rows_) {
    throw exception();
  }
  if (cols_ == 2) {
    result = matrix_[0][0] * matrix_[1][1] - matrix_[1][0] * matrix_[0][1];
  } else if (cols_ == 1) {
    result = matrix_[0][0];
  } else {
    for (int i = 0; i < cols_; i++) {
      S21Matrix B(rows_ - 1, cols_ - 1);
      double res_minor = 0;
      for (int x = 1; x < rows_; x++) {
        int check = 0;
        for (int y = 0; y < cols_; y++) {
          if (y == i) {
            check = 1;
          } else {
            B.matrix_[x - 1][y - check] = matrix_[x][y];
          }
        }
      }
      res_minor = B.Determinant();
      if (i % 2 != 0) {
        result += matrix_[0][i] * -1 * res_minor;
      } else {
        result += matrix_[0][i] * res_minor;
      }
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (matrix_ == nullptr) {
    throw exception();
  }
  if (cols_ != rows_) {
    throw exception();
  }
  double temp = Determinant();
  if (temp == 0) {
    throw exception();
  }
  temp = 1 / temp;
  S21Matrix B(this->CalcComplements());
  B.Transpose();
  B.MulNumber(temp);
  return B;
}

const S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this == &other) {
    return *this;
  }
  if (this->matrix_) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  this->matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    this->matrix_[i] = new double[cols_];
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
  return *this;
}

double S21Matrix::operator()(int i, int j) {
  if (matrix_ == nullptr) {
    throw exception();
  }
  if (i >= rows_ || j >= cols_) {
    throw exception();
  }
  return matrix_[i - 1][j - 1];
}

const S21Matrix operator+(const S21Matrix &my, const S21Matrix &other) {
  if (my.matrix_ == nullptr || other.matrix_ == nullptr) {
    throw exception();
  } else if (my.cols_ != other.cols_ || my.rows_ != other.rows_) {
    throw exception();
  }
  S21Matrix res(my);
  res.SumMatrix(other);
  return res;
}

const S21Matrix operator-(const S21Matrix &my, const S21Matrix &other) {
  if (my.matrix_ == nullptr || other.matrix_ == nullptr) {
    throw exception();
  } else if (my.cols_ != other.cols_ || my.rows_ != other.rows_) {
    throw exception();
  }
  S21Matrix res(my);
  res.SubMatrix(other);
  return res;
}

const S21Matrix operator*(S21Matrix &my, const S21Matrix &other) {
  if (my.matrix_ == nullptr || other.matrix_ == nullptr) {
    throw exception();
  } else if (my.cols_ != other.cols_ || my.rows_ != other.rows_) {
    throw exception();
  }
  S21Matrix res(my);
  res.MulMatrix(other);
  return res;
}

const S21Matrix operator*(const S21Matrix &other, const double num) {
  if (other.matrix_ == nullptr) {
    throw exception();
  }
  S21Matrix res(other);
  res.MulNumber(num);
  return res;
}

bool operator==(S21Matrix &my, const S21Matrix &other) {
  if (my.matrix_ == nullptr || other.matrix_ == 0) {
    throw exception();
  }
  bool res = my.EqMatrix(other);
  return res;
}

S21Matrix &operator+=(S21Matrix &my, const S21Matrix &other) {
  if (my.matrix_ == nullptr || other.matrix_ == 0) {
    throw exception();
  } else if (my.cols_ != other.cols_ || my.rows_ != other.rows_) {
    throw exception();
  }
  my.SumMatrix(other);
  return my;
}

S21Matrix &operator-=(S21Matrix &my, const S21Matrix &other) {
  if (my.matrix_ == nullptr || other.matrix_ == 0) {
    throw exception();
  } else if (my.cols_ != other.cols_ || my.rows_ != other.rows_) {
    throw exception();
  }
  my.SubMatrix(other);
  return my;
}

S21Matrix &operator*=(S21Matrix &my, const S21Matrix &other) {
  if (my.matrix_ == nullptr || other.matrix_ == 0) {
    throw exception();
  } else if (my.cols_ != other.rows_) {
    throw exception();
  }
  my.MulMatrix(other);
  return my;
}

S21Matrix &operator*=(S21Matrix &my, const double num) {
  if (my.matrix_ == nullptr) {
    throw exception();
  }
  my.MulNumber(num);
  return my;
}

// int main() {
//   S21Matrix A(3, 3);
//   S21Matrix B(3, 3);
//   for (int i = 0; i < 3; i++) {
//     for (int j = 0; j < 3; j++) {
//       A.getmatrix()[i][j] = i + j;
//       B.getmatrix()[i][j] = i + j;
//     }
//   }
//   A.getmatrix()[2][2] = 333;
//   A += B;
//   A -= B;
//   A *= 5.1;
//   A *= B;
//   S21Matrix C(A.InverseMatrix());
//   double res = A.Determinant();
//   cout << res << '\n';
//   bool rs = A.EqMatrix(B);
//   cout << rs << '\n';
//   for (int i = 0; i < 3; i++) {
//     for (int j = 0; j < 3; j++) {
//       cout << A.getmatrix()[i][j];
//       cout << " ";
//     }
//     cout << '\n';
//   }
//   for (int i = 0; i < 3; i++) {
//     for (int j = 0; j < 3; j++) {
//       cout << C.getmatrix()[i][j];
//       cout << " ";
//     }
//     cout << '\n';
//   }
//   return 0;
// }