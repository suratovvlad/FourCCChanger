/* 
 * File:   welldonedialog.h
 * Author: Suratov Vladislav
 *
 * Created on August 5, 2012, 4:02 PM
 */

#ifndef WELLDONEDIALOG_H
#define	WELLDONEDIALOG_H

#include <QDialog>

class QLabel;
class QPushButton;

class WellDoneDialog: public QDialog
{
    Q_OBJECT
public:
    WellDoneDialog(QWidget *parent = 0);
private:
    QLabel *label;
    QPushButton *okButton;
};

#endif	/* WELLDONEDIALOG_H */

