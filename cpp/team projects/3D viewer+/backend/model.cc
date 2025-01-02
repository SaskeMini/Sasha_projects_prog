#include "model.h"

namespace s21 {

Model::Model() : _filePath(""), _object(), _scale(1) {}  // default constructor

bool Model::setObject(const std::string& filePath) {
  _filePath = filePath;
  setted = _object.readObject(filePath);
  _obj_changed = true;
  if (setted) {
    _object.center();
    _object.normalize();
    _max_face_size = _object.getMaxFaceSize();
  }
  return setted;
}

void Model::transform(int operation, double value) {
  switch (operation) {
    case 0:
      _object.translate(value, 0, 0);
      break;
    case 1:
      _object.translate(0, value, 0);
      break;
    case 2:
      _object.translate(0, 0, value);
      break;
    case 3:
      _object.scale(value / _scale);
      _scale = value;
      break;
    case 4:
      _object.rotateX(value);
      break;
    case 5:
      _object.rotateY(value);
      break;
    case 6:
      _object.rotateZ(value);
      break;
  }
  _changed = true;
}

Model::~Model() {}  // destructor

void Model::toNormal() {
  if (_object.readObject(_filePath)) {
    _scale = 1;
    _object.normalize();
    _object.center();
    _changed = true;
  }
}

float Model::getVertex(int row, int col) const {
  return _object.vertices(row, col);
}

const std::string& Model::getFilePath() const { return _filePath; }

double Model::getScale() const { return _scale; }

unsigned int Model::getNumberVertex() const { return _object.number_vertex; }

unsigned int Model::getNumberFace() const { return _object.number_face; }

unsigned int Model::getFaceSize(unsigned int index) const {
  return _object.faces[index]->size() * 3;
}

const Object& Model::getObject() const { return _object; }

std::pair<unsigned int, unsigned int> Model::getBufSize() {
  if (setted) {
    if (_obj_changed) {
      _ver_buf_size = getNumberVertex() * 3;
      _edge_buf_size = 0;
      for (unsigned int i = 0; i < getNumberFace(); i++) {
        _edge_buf_size += getFaceSize(i);
      }
      _obj_changed = false;
    }
  } else {
    _ver_buf_size = 0;
    _edge_buf_size = 0;
    _obj_changed = false;
  }
  return std::make_pair(_ver_buf_size, _edge_buf_size);
}

void Model::loadBuffer(float* vertex_buffer, float* edge_buffer, bool load) {
  if (setted) {
    if (_changed || load) {
      for (unsigned int i = 0; i < getNumberVertex(); ++i) {
        vertex_buffer[i * 3] = _object.vertices(i, 0);
        vertex_buffer[i * 3 + 1] = _object.vertices(i, 1);
        vertex_buffer[i * 3 + 2] = _object.vertices(i, 2);
      }
      unsigned int index = 0;
      for (unsigned int i = 0; i < getNumberFace() && index < _edge_buf_size;
           ++i) {
        for (unsigned int j = 0;
             j < _object.faces[i]->size() && index < _edge_buf_size; ++j) {
          edge_buffer[index++] = _object.vertices(_object.faces[i]->at(j), 0);
          edge_buffer[index++] = _object.vertices(_object.faces[i]->at(j), 1);
          edge_buffer[index++] = _object.vertices(_object.faces[i]->at(j), 2);
        }
      }
      _changed = false;
    }
  }
}

}  // namespace s21