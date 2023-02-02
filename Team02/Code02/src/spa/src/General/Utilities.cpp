#include "Utilities.h"

template<typename Base, typename T>
bool utilities::InstanceOf(const T *ptr) {
  return dynamic_cast<const Base*>(ptr) != nullptr;
}