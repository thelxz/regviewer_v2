#include "bitbutton.h"
#include <QPushButton>
#include <QWidget>

BitButton::BitButton(QWidget *parent) : QPushButton(parent)
{
    connect(this, SIGNAL(clicked()), this, SLOT(bitbtnclick()));
    this->setFocusPolicy(Qt::NoFocus);
}

void BitButton::bitbtnclick()
{
    if (this->text()=="1") {
        this->set_value(0);
    }
    else {
        this->set_value(1);
    }
    emit bittoggled();
}

void BitButton::set_value(int input_value){
    if (input_value == 0){
        this->setText("0");
        this->setStyleSheet("QPushButton {}");
    }
    else {
        this->setText("1");
        this->setStyleSheet("QPushButton { background-color: green}");
    }
}
