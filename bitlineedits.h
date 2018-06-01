#ifndef BITLINEEDITS_H
#define BITLINEEDITS_H

#include <QWidget>
#include "bits.h"
class BitLineEdit;
class QLabel;

class BitLineEdits : public QWidget
{
    Q_OBJECT
public:
    explicit BitLineEdits(QWidget *parent, Bits *bits);

private:
    Bits * bits;
    BitLineEdit * hex_line_edit;
    BitLineEdit * dec_line_edit;
    BitLineEdit * oct_line_edit;
    BitLineEdit * bin_line_edit;
    BitLineEdit * dec_s_line_edit;
    BitLineEdit * addr_line_edit;

    QLabel * hex_label;
    QLabel * dec_label;
    QLabel * oct_label;
    QLabel * bin_label;
    QLabel * dec_s_label;
    QLabel * addr_label;

};

#endif // BITLINEEDITS_H
