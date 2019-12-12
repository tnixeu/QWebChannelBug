#ifndef WEBCHANNEL_H
#define WEBCHANNEL_H

#include <QObject>
#include <helper.hpp>

class dummy_data : public QObject {
  Q_OBJECT
public:
  explicit dummy_data(QObject *parent = nullptr);

signals:
  void some_data_vector_changed(const some_data_vector &changed);

public slots:
  void set_some_data_vector(const some_data_vector &changed);
  void loaded();

public:
  Q_PROPERTY(some_data_vector some_data_vector MEMBER m_some_data_vector NOTIFY
                 some_data_vector_changed)
private:
  some_data_vector m_some_data_vector;
};

#endif // WEBCHANNEL_H
