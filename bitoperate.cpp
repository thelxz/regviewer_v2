#include "bitoperate.h"
#include <QGridLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QWidget>
#include <QRegExpValidator>
#include <QComboBox>

BitOperate::BitOperate(QWidget *parent, Bits *bits) : QWidget(parent)
{
    this->bits = bits;
    QGridLayout *mainLayout = new QGridLayout;
    QGridLayout *shiftLayout = new QGridLayout;
    QWidget * shiftWidget = new QWidget;
    btn_clear = new QPushButton("clear", this);
    btn_set = new QPushButton("set all", this);
    btn_reverse = new QPushButton("reverse", this);
    btn_shift_left = new QPushButton("<<shift",this);
    txt_shift_bit_num = new QLineEdit("0",this);
    btn_shift_right = new QPushButton("shift>>",this);
    shift_mode = new QComboBox(this);
    shift_mode->setToolTip("Shift Mode");
    shift_mode->addItem("Logic");
    shift_mode->addItem("Arith");
    shift_mode->addItem("Rotate");
    shift_mode->setEditable(false);

    QRegExp rx_dec("[0-9]+");
    QValidator *dec_validator = new QRegExpValidator(rx_dec, this);
    txt_shift_bit_num->setValidator(dec_validator);
    txt_shift_bit_num->setMaxLength(2);
    txt_shift_bit_num->setAlignment(Qt::AlignCenter);

    shiftLayout->addWidget(btn_shift_left,		0,0,1,1);
    shiftLayout->addWidget(txt_shift_bit_num,	0,1,2,1);
    shiftLayout->addWidget(btn_shift_right,		0,2,1,1);
    shiftLayout->setSpacing(0);
    shiftLayout->setMargin(1);
    shiftWidget->setLayout(shiftLayout);
    shiftWidget->setFixedWidth(200);

    mainLayout->addWidget(btn_clear,			0,0,1,1);
    mainLayout->addWidget(btn_set,				0,1,1,1);
    mainLayout->addWidget(btn_reverse,			0,2,1,1);
    mainLayout->addWidget(shiftWidget,			0,3,1,1);
    mainLayout->addWidget(shift_mode,			0,4,1,1);
    this->setLayout(mainLayout);
    txt_shift_bit_num->setText("1");
    btn_clear->setFocusPolicy(Qt::NoFocus);
    btn_reverse->setFocusPolicy(Qt::NoFocus);
    btn_set->setFocusPolicy(Qt::NoFocus);
    btn_shift_left->setFocusPolicy(Qt::NoFocus);
    btn_shift_right->setFocusPolicy(Qt::NoFocus);
    shift_mode->setFocusPolicy(Qt::NoFocus);
    connect(shift_mode,SIGNAL(currentTextChanged(QString)),this,SLOT(set_shift_mode(QString)));
    connect(btn_clear,SIGNAL(clicked(bool)),this,SLOT(clear_num()));
    connect(btn_reverse,SIGNAL(clicked(bool)),this,SLOT(reverse_num()));
    connect(btn_set,SIGNAL(clicked(bool)),this,SLOT(set_num()));
    connect(btn_shift_left,SIGNAL(clicked(bool)),this,SLOT(shift_left()));
    connect(btn_shift_right,SIGNAL(clicked(bool)),this,SLOT(shift_right()));
    connect(bits,SIGNAL(value_changed()),this,SLOT(update_display()));
}

void BitOperate::clear_num(){
    bits->clear_all();
}
void BitOperate::set_num(){
    bits->set_all();
}
void BitOperate::reverse_num(){
    bits->reverse_all();
}

void BitOperate::shift_left(){
    int shift_bits = this->txt_shift_bit_num->text().toInt();
    bits->shift_left(shift_bits);
}

void BitOperate::shift_right(){
    int shift_bits = this->txt_shift_bit_num->text().toInt();
    bits->shift_right(shift_bits);
}

void BitOperate::update_display(){
    switch (bits->get_shift_mode()){
        case Bits::SHF_LOGIC:
            shift_mode->setCurrentText("Logic");
            break;
        case Bits::SHF_ARITH:
            shift_mode->setCurrentText("Arith");
            break;
        case Bits::SHF_ROTATE:
            shift_mode->setCurrentText("Rotate");
            break;
    }
}

void BitOperate::set_shift_mode(QString mode){
    if (mode=="Logic")
        bits->set_shift_mode(Bits::SHF_LOGIC);
    else if (mode=="Arith")
        bits->set_shift_mode(Bits::SHF_ARITH);
    else if (mode=="Rotate")
        bits->set_shift_mode(Bits::SHF_ROTATE);
}
