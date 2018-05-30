#ifndef INTBITS_H
#define INTBITS_H

#include <QWidget>
#include "bitbutton.h"

#define REG_BIT_NUM 64
class QPushButton;
class BitButton;
class QLabel;

class Intbits : public QWidget
{
    Q_OBJECT
public:
    explicit Intbits(QWidget *parent = 0);
    void set_value(quint64 input_num);
    quint64 get_value();
signals:
    void value_changed(quint64 changed_num);

private:
    quint64 int_num;
    BitButton * btn_bits[REG_BIT_NUM];
    QLabel *label_bits[REG_BIT_NUM];
    void update_display();
    void update_data();
public slots:
    void click_bits_btn();
};

#endif // INTBITS_H
