#ifndef __S21_MODEL_H__
#define __S21_MODEL_H__

#include "object.h"

namespace s21 {

class Model {
 private:
  std::string _filePath;
  Object _object;
  double _scale = 1;
  unsigned int _max_face_size = 0;
  unsigned int _ver_buf_size = 0;
  unsigned int _edge_buf_size = 0;
  bool _changed = false;
  bool _obj_changed = false;

 public:
  bool setted = false;
  bool setObject(const std::string& filePath);
  void transform(int operation, double value);
  const std::string& getFilePath() const;
  double getScale() const;
  unsigned int getNumberVertex() const;
  unsigned int getNumberFace() const;
  const Object& getObject() const;
  unsigned int getFaceSize(unsigned int index) const;
  void toNormal();
  float getVertex(int row, int col) const;
  std::pair<unsigned int, unsigned int> getBufSize();
  void loadBuffer(float* vertex_buffer, float* edge_buffer, bool load);
  Model();
  ~Model();
};
}  // namespace s21

#endif