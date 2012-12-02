#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"
#include "src/gpxmodel.h"
#include "src/gpxviewer.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    GpxViewer MyViewer;

//    QmlApplicationViewer viewer;
//    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
//    //viewer.setMainQmlFile(QLatin1String("qml/test03/main.qml"));
//    //viewer.setMainQmlFile(QLatin1String("qml/test03/dynamiclist.qml"));
//    //viewer.rootContext()->setContextProperty("GpxModel",m_pGpxModel);
//    viewer.setMainQmlFile(QLatin1String("qml/test03/expandingdelegates.qml"));
//    viewer.showExpanded();

    return app->exec();
}
