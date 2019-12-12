#include "file_provider.hpp"
#include <QBuffer>
#include <QFileInfo>
#include <QUrlQuery>
#include <QWebEngineUrlRequestJob>


FileLoaderUrlSchemeHandler::FileLoaderUrlSchemeHandler(QObject *parent)
    : QWebEngineUrlSchemeHandler(parent) {}

void FileLoaderUrlSchemeHandler::requestStarted(QWebEngineUrlRequestJob *job) {

  QString url = job->requestUrl().toString();

  url.replace("files://", ":");

  QFileInfo info(url);

  if (info.exists()) {
    std::unique_ptr<QFile> file = std::make_unique<QFile>(url);

    job->connect(job, &QObject::destroyed, file.get(), &QObject::deleteLater);

    job->reply(db.mimeTypeForFile(info).name().toUtf8(), file.release());
  } else {
    job->fail(QWebEngineUrlRequestJob::Error::UrlNotFound);
  }
}
