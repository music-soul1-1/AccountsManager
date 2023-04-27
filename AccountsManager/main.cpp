#include "AccountsManager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    AccountsManager window;

    window.show();
    return app.exec();
}
