#ifndef BITELEMENT_H
#define BITELEMENT_H

#include <QWidget>
#include "bitbuttons.h"
#include "bitlineedit.h"
#include "bitlineedits.h"
#include "bits.h"

class BitElement : public QWidget
{
    Q_OBJECT
public:
    explicit BitElement(QWidget *parent = nullptr);
private:
    Bitbuttons * bitbtns;
    BitLineEdit * line_edit;
    BitLineEdits * line_edits;
    Bits * bits = new Bits(32);
signals:

public slots:
};

#endif // BITELEMENT_H
