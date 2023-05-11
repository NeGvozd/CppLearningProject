#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>
#include <QPainter>
#include <QTime>

static const int LOAD_TIME_MSEC = 0.001 * 1000;

void createSplashScreen(MainWindow &w, QApplication &a)
{
    //static const int LOAD_TIME_MSEC = 3 * 1000;
    static const int PROGRESS_X_PX = 423;
    static const int PROGRESS_Y_PX = 683;
    static const int PROGRESS_WIDTH_PX = 430;
    static const int PROGRESS_HEIGHT_PX = 70;

    QPixmap pix( ":/rec/img/SplashScreen.png" );
    QSplashScreen splashScreen( pix );
    splashScreen.show();
    a.processEvents();

    QTime time;
    time.start();
    while( time.elapsed() < LOAD_TIME_MSEC ) {
        const int progress = static_cast< double >( time.elapsed() ) / LOAD_TIME_MSEC * 100.0;
        splashScreen.showMessage( QObject::trUtf8( "Загружено: %1%" ).arg( progress ), Qt::AlignBottom | Qt::AlignCenter);

        QPainter painter;
        painter.begin( &pix );
        painter.fillRect(PROGRESS_X_PX, PROGRESS_Y_PX, progress / 100.0 * PROGRESS_WIDTH_PX, PROGRESS_HEIGHT_PX, Qt::green);
        painter.end();

        splashScreen.setPixmap(pix);
        a.processEvents();
    }
    splashScreen.finish( &w );
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    createSplashScreen(w, a);
    w.show();
    return a.exec();
}
