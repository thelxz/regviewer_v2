#ifndef BASELINEEDIT_H
#define BASELINEEDIT_H
#include <QLineEdit>
#include "bits.h"

class BitLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    BitLineEdit(QWidget *parent, Bits * bits, Bits::STR_TYPE type);
    Bits *bits;
    Bits::STR_TYPE type;
private:
    void string_format_error(bool is_error);
private slots:
    void finish_edit();
    void update_display();
    void text_changed(QString input_str);
};

#endif // BASELINEEDIT_H
