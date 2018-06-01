#ifndef INTBITS_H
#define INTBITS_H

#include <QWidget>
#include "bitbutton.h"
#include "bits.h"

#define REG_BIT_NUM 64
class QPushButton;
class BitButton;
class QLabel;

class Bitbuttons : public QWidget
{
    Q_OBJECT
public:
    explicit Bitbuttons(QWidget *parent = 0, Bits * bits = NULL);

private:
    Bits * bits;
    BitButton * btn_bits[REG_BIT_NUM];
    QLabel *label_bits[REG_BIT_NUM];

public slots:
    void update_display();
    void click_bits_btn();
};

#endif // INTBITS_H
