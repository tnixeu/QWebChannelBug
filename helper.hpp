#pragma once
#include <QString>
#include <QVariantMap>
#include <vector>
struct some_data {

public:
  QString name = "";
  bool even;
  int view_type = 0;
  some_data() = default;

  some_data(const QString &name, bool even) : name(name), even(even) {}

  some_data(const some_data &other) : name(other.name), even(other.even) {}

  some_data(const QVariantMap &map)
      : name(map["name"].toString()), even(map["even"].toBool()) {}

  QVariantMap to_map() const {

    QVariantMap temp;
    temp["name"] = name;
    temp["even"] = even;

    return temp;
  }

  bool operator!=(const some_data &other) const { return !(*this == other); }

  bool operator==(const some_data &other) const {
    return name == other.name && even == other.even;
  }
};

using some_data_vector = std::vector<some_data>;

Q_DECLARE_METATYPE(some_data)
Q_DECLARE_METATYPE(some_data_vector)

template <typename T> struct convert_help_vector {
  static T convert_to_cpp(const QVariantList &map) {
    T temp;
    for (auto &i : map) {
      temp.push_back(i.toMap());
    }
    return temp;
  }

  static QVariantList convert_to_js(const T &container) {
    QVariantList temp;

    for (auto &i : container) {
      temp.append(i.to_map());
    }

    return temp;
  }

  static void register_type() {
    qRegisterMetaType<T>();
    QMetaType::registerConverter<QVariantList, T>(convert_to_cpp);
    QMetaType::registerConverter<T, QVariantList>(convert_to_js);
  }
};
