#include "LogInManager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    LogInManager window;

    window.show();
    return app.exec();
}
