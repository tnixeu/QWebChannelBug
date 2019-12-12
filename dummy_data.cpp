#include "dummy_data.hpp"

dummy_data::dummy_data(QObject *parent) : QObject(parent) {
  connect(this, &dummy_data::some_data_vector_changed, this,
          &dummy_data::set_some_data_vector);
}

void dummy_data::set_some_data_vector(const some_data_vector &changed) {
  m_some_data_vector = changed;
}

void dummy_data::loaded() {
  for (int i = 0; i < 10; i++) {
    m_some_data_vector.emplace_back(QString("Data %1").arg(i), i % 2 == 0);
  }

  emit some_data_vector_changed(m_some_data_vector);
}
