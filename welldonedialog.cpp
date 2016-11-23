/* 
 * File:   welldonedialog.cpp
 * Author: Suratov Vladislav
 * 
 * Created on August 5, 2012, 4:02 PM
 */

#include "welldonedialog.h"

#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>

WellDoneDialog::WellDoneDialog(QWidget *parent): QDialog(parent)
{
    label = new QLabel(tr("Well done!"));
    okButton = new QPushButton(tr("OK"));
    
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(label);
    layout->addWidget(okButton);
    
    QObject::connect(okButton, SIGNAL(clicked()), this, SLOT(close()));
    
    setLayout(layout);
    setWindowTitle("Well Done");
}

