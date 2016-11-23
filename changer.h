/* 
 * File:   changer.h
 * Author: Suratov Vladislav
 *
 * Created on August 3, 2012, 6:38 PM
 */

#ifndef CHANGER_H
#define	CHANGER_H

#include <QDialog>

class QFileDialog;
class QLabel;
class QStringList;
class QPushButton;
class QTextEdit;
class QComboBox;

class Changer: public QDialog
{
    Q_OBJECT
public:
    Changer(QWidget *parent = 0);
private slots:
    void browseClicked();
    void changeClicked();
private:
    QFileDialog *fileDialog;
    QStringList fileList;
    QComboBox *comboBox;
    
    QPushButton *openFileButton;
    QPushButton *changeButton;
    QPushButton *closeButton;
    
    QLabel *descriptionLabel;
    QLabel *comboBoxLabel;
    QTextEdit *textEdit;
    
    void openFileToChange(QString&, int);
};

#endif	/* CHANGER_H */

