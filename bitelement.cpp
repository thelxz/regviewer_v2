#include "bitelement.h"
#include <QGridLayout>

BitElement::BitElement(QWidget *parent) : QWidget(parent)
{
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSpacing(0);
    bitbtns = new Bitbuttons(this, bits);
    line_edits = new BitLineEdits(this, bits);
    bit_operate = new BitOperate(this,bits);
    mainLayout->addWidget(bitbtns,0,0,1,1);
    mainLayout->addWidget(line_edits,0,1,2,1);
    mainLayout->addWidget(bit_operate,1,0,1,1);
    setLayout(mainLayout);
}
