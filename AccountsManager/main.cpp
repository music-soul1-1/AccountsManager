#include "AccountsManager.h"
#include <QApplication>
#include <QFont>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    AccountsManager window;

    QFont font("Inter", 10);
    app.setFont(font);

    window.show();
    return app.exec();
}
