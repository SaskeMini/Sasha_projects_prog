#include "controller.h"

namespace s21 {

Controller::Controller() { _model = Model(); }

Controller::~Controller() {}

const std::string& Controller::getFilePath() const {
  return _model.getFilePath();
}

void Controller::transformObject(int operation, double value) {
  _model.transform(operation, value);
}

double Controller::getScale() const { return _model.getScale(); }

unsigned int Controller::getNumberVertex() const {
  return _model.getNumberVertex();
}

unsigned int Controller::getNumberFace() const {
  return _model.getNumberFace();
}

unsigned int Controller::getFaceSize(unsigned int index) const {
  return _model.getFaceSize(index);
}

const Object& Controller::getObject() const { return _model.getObject(); }

void Controller::toNormal() { _model.toNormal(); }

bool Controller::setObject(const std::string& filePath) {
  return _model.setObject(filePath);
}

float Controller::getVertex(int row, int col) const {
  return _model.getVertex(row, col);
}

bool Controller::isSetted() const { return _model.setted; }

std::pair<unsigned int, unsigned int> Controller::getBufSize() {
  return _model.getBufSize();
}

void Controller::loadBuffer(float* vertex_buffer, float* edge_buffer,
                            bool load) {
  return _model.loadBuffer(vertex_buffer, edge_buffer, load);
}

}  // namespace s21