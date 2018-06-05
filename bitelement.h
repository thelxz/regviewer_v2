#ifndef BITELEMENT_H
#define BITELEMENT_H

#include <QWidget>
#include "bitbuttons.h"
#include "bitlineedits.h"
#include "bitoperate.h"
#include "bits.h"
#include "bitoptions.h"

class BitElement : public QWidget
{
    Q_OBJECT
public:
    explicit BitElement(QWidget *parent = nullptr);
private:
    Bitbuttons * bitbtns;
    BitLineEdits * line_edits;
    BitOperate * bit_operate;
    bitOptions * bit_options;
    Bits * bits = new Bits(16);
signals:

public slots:
};

#endif // BITELEMENT_H
