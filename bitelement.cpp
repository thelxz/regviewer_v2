#include "bitelement.h"
#include <QGridLayout>

BitElement::BitElement(QWidget *parent) : QWidget(parent)
{
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSpacing(0);
    bitbtns = new Bitbuttons(this, bits);
    line_edit = new BitLineEdit(this, bits, Bits::ADDR);
    line_edits = new BitLineEdits(this, bits);
    mainLayout->addWidget(bitbtns);
    mainLayout->addWidget(line_edit);
    mainLayout->addWidget(line_edits);
    setLayout(mainLayout);
}
