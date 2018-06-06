#include "bitlineedits.h"
#include "bitlineedit.h"
#include <QLabel>
#include <QGridLayout>

BitLineEdits::BitLineEdits(QWidget *parent, Bits * bits) : QWidget(parent)
{
    this->bits = bits;
    this->setFixedSize(300,130);
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSpacing(0);
    hex_line_edit = new BitLineEdit(this,bits,Bits::HEX);
    dec_line_edit = new BitLineEdit(this,bits,Bits::DEC);
    dec_s_line_edit = new BitLineEdit(this,bits,Bits::DEC_S);
    oct_line_edit = new BitLineEdit(this,bits,Bits::OCT);
    bin_line_edit = new BitLineEdit(this,bits,Bits::BIN);
    addr_line_edit = new BitLineEdit(this,bits,Bits::ADDR);

    hex_label = new QLabel("Hex:");
    dec_label = new QLabel("uDec:");
    dec_s_label = new QLabel("sDec:");
    oct_label = new QLabel("Oct:");
    bin_label = new QLabel("Bin:");
    addr_label = new QLabel("Size:");
//    hex_label->setAlignment(Qt::AlignRight);
//    dec_label->setAlignment(Qt::AlignRight);
//    dec_s_label->setAlignment(Qt::AlignRight);
//    oct_label->setAlignment(Qt::AlignRight);
//    bin_label->setAlignment(Qt::AlignRight);
//    addr_label->setAlignment(Qt::AlignRight);
    mainLayout->addWidget(this->hex_label,0,0,1,1);
    mainLayout->addWidget(this->dec_label,1,0,1,1);
    mainLayout->addWidget(this->dec_s_label,2,0,1,1);
    mainLayout->addWidget(this->oct_label,3,0,1,1);
    mainLayout->addWidget(this->bin_label,4,0,1,1);
    mainLayout->addWidget(this->addr_label,5,0,1,1);
    mainLayout->addWidget(this->hex_line_edit,0,1,1,5);
    mainLayout->addWidget(this->dec_line_edit,1,1,1,5);
    mainLayout->addWidget(this->dec_s_line_edit,2,1,1,5);
    mainLayout->addWidget(this->oct_line_edit,3,1,1,5);
    mainLayout->addWidget(this->bin_line_edit,4,1,1,5);
    mainLayout->addWidget(this->addr_line_edit,5,1,1,5);
    this->setLayout(mainLayout);
}
