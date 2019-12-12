#include "mainwindow.h"
#include "file_provider.hpp"
#include "ui_mainwindow.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QWebChannel>
#include <QWebEnginePage>
#include <QWebEngineProfile>
#include <QWebEngineUrlScheme>
#include <QWebEngineView>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  QWebEngineUrlScheme::registerScheme(QWebEngineUrlScheme(QByteArray("files")));
  convert_help_vector<some_data_vector>::register_type();
  QWebEngineView *view = new QWebEngineView(this);
  m_data = std::make_unique<dummy_data>(this);
  QWebChannel *channel = new QWebChannel(m_data.get());
  view->page()->setWebChannel(channel);
  channel->registerObject(QString("js_data"), m_data.get());
  view->page()->profile()->installUrlSchemeHandler(
      QByteArray("files"), new FileLoaderUrlSchemeHandler(this));
  view->setUrl(QUrl("files://index.html"));
  ui->horizontalLayout->replaceWidget(ui->widget, view);

  connect(m_data.get(), &dummy_data::some_data_vector_changed,
          [this](const some_data_vector &data) {
            QJsonDocument doc = QJsonDocument::fromVariant(
                convert_help_vector<some_data_vector>::convert_to_js(data));
            ui->text_edit->setText(doc.toJson());
          });
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_button_send_clicked() {
  QJsonDocument doc =
      QJsonDocument::fromJson(ui->text_edit->toPlainText().toUtf8());
  emit m_data->some_data_vector_changed(
      convert_help_vector<some_data_vector>::convert_to_cpp(
          doc.array().toVariantList()));
}
