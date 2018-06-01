#include "bitlineedit.h"
#include <QDebug>

BitLineEdit::BitLineEdit(QWidget *parent, Bits *bits, Bits::STR_TYPE type):QLineEdit(parent)
{
    this->bits = bits;
    this->type = type;
    connect(bits, SIGNAL(value_changed()),this,SLOT(update_display()));
    connect(this, SIGNAL(textEdited(QString)),this,SLOT(text_changed(QString)));
    connect(this, SIGNAL(editingFinished()),this,SLOT(finish_edit()));
}

void BitLineEdit::update_display(){
    Bits tmp_bits(bits->get_width());
    tmp_bits.set_string(this->text().toStdString(),type);
    if (tmp_bits.get_data() != bits->get_data()){			//	need to update?
        this->setText(bits->get_string(type).c_str());
    }
    this->string_format_error(false);
}
void BitLineEdit::finish_edit(){
    // update other viewers' display
    bits->broadcast_value_changed();
}

void BitLineEdit::text_changed(QString input_str){
    string_format_error(!bits->set_string(input_str.toStdString(),type));
}

void BitLineEdit::string_format_error(bool is_error){
    if (is_error){
        this->setStyleSheet("QLineEdit { background-color: #FF8888 }");
    }
    else{
        this->setStyleSheet("");
    }
}


