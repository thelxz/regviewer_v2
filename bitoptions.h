#ifndef BITOPTIONS_H
#define BITOPTIONS_H

#include <QWidget>
#include "bits.h"
#include <QRadioButton>
#include <QCheckBox>
#include <QPushButton>

#ifdef Q_OS_WIN
#include <windows.h>
#endif

class bitOptions : public QWidget
{
    Q_OBJECT
public:
    explicit bitOptions(QWidget *parent, Bits * bits);

signals:

private:
    Bits * bits;
    QRadioButton * btn_8;
    QRadioButton * btn_16;
    QRadioButton * btn_32;
    QRadioButton * btn_64;
    QCheckBox * ckbox_always_on_top;

public slots:
    void set_alway_on_top(int);
    void change_width();
    void update_display();
};

#endif // BITOPTIONS_H
