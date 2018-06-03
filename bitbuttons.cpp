#include "bitbuttons.h"
#include <QLabel>
#include <QPushButton>
#include <QPalette>
#include <QGridLayout>
#include <QMessageBox>
Bitbuttons::Bitbuttons(QWidget *parent, Bits * bits) : QWidget(parent)
{
    this->bits = bits;
    this->setFixedSize(800,100);
    QGridLayout *bits_layout = new QGridLayout;
    QGridLayout *mainLayout = new QGridLayout;
    bits_layout->setSpacing(0);
    QPalette pa_color;

    int row = 0;
    int column = 0;
    int bit_count = 0;
    for (int i=0; i<REG_BIT_NUM ; i++)
    {
        bit_count = REG_BIT_NUM - i -1;
        btn_bits[bit_count] = new BitButton();
        label_bits[bit_count] = new QLabel(QString::number(bit_count));
        if (1 == (i/4)%2) {
            pa_color.setColor(QPalette::WindowText,Qt::red);
            label_bits[bit_count]->setPalette(pa_color);
        } else {
            pa_color.setColor(QPalette::WindowText,Qt::blue);
            label_bits[bit_count]->setPalette(pa_color);
        }
        label_bits[bit_count]->setAlignment(Qt::AlignCenter);
        column = i%(REG_BIT_NUM/2);
        row = i/(REG_BIT_NUM/2);
        bits_layout->addWidget(label_bits[bit_count],row*2,column,1,1);
        bits_layout->addWidget(btn_bits[bit_count],row*2+1,column,1,1);
        connect(btn_bits[bit_count], SIGNAL(bittoggled()), this, SLOT(click_bits_btn()));
    }
    mainLayout->addLayout(bits_layout,0,0,1,1);
    setLayout(mainLayout);
    connect(bits,SIGNAL(value_changed()),this,SLOT(update_display()));
    this->update_display();
}

void Bitbuttons::update_display()
{
    int num_tmp;
    QPalette pa_color;
    for (unsigned int i=0; i<REG_BIT_NUM ; i++)
    {
        num_tmp = (int) bits->get_bit(i);
        this->btn_bits[i]->set_value(num_tmp);
        if (bits->get_width() <= i){				//is disable bits
            pa_color.setColor(QPalette::WindowText,Qt::gray);
            label_bits[i]->setPalette(pa_color);
            this->btn_bits[i]->setDisabled(true);
        }											//is enable bits
        else {
            this->btn_bits[i]->setDisabled(false);
            if (1 == (i/4)%2) {
                pa_color.setColor(QPalette::WindowText,Qt::red);
                label_bits[i]->setPalette(pa_color);
            } else {
                pa_color.setColor(QPalette::WindowText,Qt::blue);
                label_bits[i]->setPalette(pa_color);
            }
        }
    }
}

void Bitbuttons::click_bits_btn()
{
    QString bits_str;
    bits_str = "";
    for (int i=0; i<REG_BIT_NUM ; i++)
    {
        bits_str = this->btn_bits[i]->text() + bits_str;
    }
    bool ok;
    bits->set_data(bits_str.toULongLong(&ok,2));
}

