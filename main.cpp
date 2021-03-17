#include "loginauth.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // The form type below will be the first form loaded on program startup
    // LoginAuth will be the first window displayed
    LoginAuth* w = new LoginAuth;
    // Disable window resizing
    w->setFixedSize(w->size());
    w->show();
    return a.exec();
}
