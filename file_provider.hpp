#pragma once

#include <QMimeDatabase>
#include <QWebEngineUrlSchemeHandler>


class FileLoaderUrlSchemeHandler : public QWebEngineUrlSchemeHandler {
  Q_OBJECT
public:
  FileLoaderUrlSchemeHandler(QObject *parent = Q_NULLPTR);
  void requestStarted(QWebEngineUrlRequestJob *job);
  QMimeDatabase db;
};
