#include "bitoptions.h"
#include "QGridLayout"
#define	HEIGHT 130
#define	WIDTH_S 60
#define	WIDTH_L	140
bitOptions::bitOptions(QWidget *parent, Bits * bits) : QWidget(parent)
{
    this->bits = bits;
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSpacing(0);
    this->setFixedHeight(HEIGHT);
    this->setFixedWidth(WIDTH_S);
    btn_8 = new QRadioButton("8");
    btn_16 = new QRadioButton("16");
    btn_32 = new QRadioButton("32");
    btn_64 = new QRadioButton("64");
    ckbox_always_on_top = new QCheckBox("Top");
    mainLayout->addWidget(btn_8,			0,0,1,1);
    mainLayout->addWidget(btn_16,	    	1,0,1,1);
    mainLayout->addWidget(btn_32,			2,0,1,1);
    mainLayout->addWidget(btn_64,			3,0,1,1);
    mainLayout->addWidget(ckbox_always_on_top,4,0,1,1);
    this->setLayout(mainLayout);
    btn_8->setFocusPolicy(Qt::NoFocus);
    btn_16->setFocusPolicy(Qt::NoFocus);
    btn_32->setFocusPolicy(Qt::NoFocus);
    btn_64->setFocusPolicy(Qt::NoFocus);
    ckbox_always_on_top->setFocusPolicy(Qt::NoFocus);

    update_display();
    connect(btn_8,SIGNAL(toggled(bool)),this,SLOT(change_width()));
    connect(btn_16,SIGNAL(toggled(bool)),this,SLOT(change_width()));
    connect(btn_32,SIGNAL(toggled(bool)),this,SLOT(change_width()));
    connect(btn_64,SIGNAL(toggled(bool)),this,SLOT(change_width()));
    connect(ckbox_always_on_top,SIGNAL(stateChanged(int)),this,SLOT(set_alway_on_top(int)));
    connect(bits,SIGNAL(value_changed()),this,SLOT(update_display()));
}

void bitOptions::change_width(){
    if (btn_8->isChecked()){
        bits->set_width(8);
    }
    else if(btn_16->isChecked()){
        bits->set_width(16);
    }
    else if(btn_32->isChecked()){
        bits->set_width(32);
    }
    else if(btn_64->isChecked()){
        bits->set_width(64);
    }
}

void bitOptions::update_display(){
    switch (bits->get_width()){
        case 8:
            btn_8->setChecked(true);
            break;
        case 16:
            btn_16->setChecked(true);
            break;
        case 32:
            btn_32->setChecked(true);
            break;
        case 64:
            btn_64->setChecked(true);
            break;
    }

}

void bitOptions::set_alway_on_top(int){
#ifdef Q_OS_WIN
    if (cke_state==Qt::Unchecked){
        SetWindowPos((HWND)winId(),HWND_NOTOPMOST,pos().x(),pos().y(),width(),height(),SWP_SHOWWINDOW);
    }
    else{
        SetWindowPos((HWND)winId(),HWND_TOPMOST,pos().x(),pos().y(),width(),height(),SWP_SHOWWINDOW);
    }
#endif
}
