#include <QApplication>
#include <bitelement.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BitElement bit_element;
    bit_element.show();

    return a.exec();
}
