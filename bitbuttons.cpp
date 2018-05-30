#include "intbits.h"
#include <QLabel>
#include <QPushButton>
#include <QPalette>
#include <QGridLayout>
#include <QMessageBox>
Intbits::Intbits(QWidget *parent) : QWidget(parent)
{
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
        if (1 == (i/4)%2)
        {
            pa_color.setColor(QPalette::WindowText,Qt::red);
            label_bits[bit_count]->setPalette(pa_color);
        }
        else
        {
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
    this->set_value(0);

}

int get_bit(quint64 int_num, int bit_num)
{
    quint64 a,tmp;
    a= 1;
    a = a << bit_num;
    tmp = int_num & a;
    return (tmp==a) ? 1 : 0;
}

void Intbits::update_display()
{
    int num_tmp;
    for (int i=0; i<REG_BIT_NUM ; i++)
    {
        num_tmp = get_bit(this->int_num,i);
        this->btn_bits[i]->set_value(num_tmp);
    }
}

void Intbits::update_data()
{
    QString bits_str;
    bits_str = "";
    for (int i=0; i<REG_BIT_NUM ; i++)
    {
        bits_str = this->btn_bits[i]->text() + bits_str;
    }
    bool ok;
    this->int_num = bits_str.toULongLong(&ok,2);
    emit value_changed(int_num);
}

void Intbits::click_bits_btn()
{
    this->update_data();
}

quint64 Intbits::get_value()
{
    return this->int_num;
}

void Intbits::set_value(quint64 input_num)
{
    this->int_num = input_num;
    this->update_display();
}
