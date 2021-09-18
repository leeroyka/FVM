#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QmlApplication/QmlApplication.hpp>

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
  QGuiApplication app(argc, argv);
  QQuickStyle::setStyle("Material");
  QQmlApplicationEngine engine;
  Gui::QmlApplication qmlApp;
  engine.rootContext()->setContextProperty("qmlApp", &qmlApp);
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;
  return app.exec();
}
