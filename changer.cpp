/* 
 * File:   changer.cpp
 * Author: Suratov Vladislav
 * 
 * Created on August 3, 2012, 6:38 PM
 */

#include "changer.h"
#include "welldonedialog.h"

//#include <QtGui>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QComboBox>
#include <QStringList>
#include <QFile>
#include <QString>
#include <QTextEdit>
#include <QMessageBox>

void Changer::browseClicked()
{
    fileDialog = new QFileDialog;
    fileList = fileDialog->getOpenFileNames(this, tr("Select one or more files to open"), "/home", tr("Video (*.avi)"));
    
    textEdit->clear();
    for (int i = 0; i < fileList.size(); ++i)
    {
          textEdit->insertPlainText(fileList.at(i).toLocal8Bit().constData());
          textEdit->insertPlainText("\n");
    }
    if (fileList.size() != 0)
    {
        changeButton->setEnabled(true);
        comboBox->setEnabled(true);
        comboBoxLabel->setEnabled(true);
    }
    else
    {
        changeButton->setEnabled(false);
        comboBox->setEnabled(false);
        comboBoxLabel->setEnabled(false);
    }
}

void Changer::changeClicked()
{
    QString file_name = "";
    int index = comboBox->currentIndex();
    for (int i = 0; i < fileList.size(); ++i)
    {
          file_name = fileList.at(i).toLocal8Bit().constData();          
          openFileToChange(file_name, index);
    }
    
    WellDoneDialog okDialog(this);
    okDialog.exec();
}

void Changer::openFileToChange(QString& file_name, int index)
{    
    QFile file(file_name);
    if (!file.open(QIODevice::ReadWrite))
    {
        QMessageBox msgBox;
        msgBox.setText(tr("Warning! Cannot open file!"));
        msgBox.exec();
        return;
    }
    
    std::string codec;
    if (index == 0) codec = "XVID";
    if (index == 1) codec = "DIVX";
    if (index == 2) codec = "DX50";
    if (index == 3) codec = "3IV2";
    
    file.seek(188);
    file.putChar(codec[0]);
    file.putChar(codec[1]);
    file.putChar(codec[2]);
    file.putChar(codec[3]);
    
    file.close();
}

Changer::Changer(QWidget* parent) : QDialog(parent)
{
    /*descriptionLabel = new QLabel(tr("Данная утилита осуществляет изменение заголовка видео-файлов"
                                     "<br>сжатых кодеками MPEG4"
                                     "<br><br>В оригинальных avi-файлах заменяются только данные"
                                     "<br>заголовка. Изменение обратно возможно только в том"
                                     "<br>случае, если вы знаете, каким кодеком был закодирован"
                                     "<br>файл (HEX-editor в помощь)"));
    descriptionLabel = new QLabel(tr(
            "This application changes header of video files encoded MPEG4."
            "<br><br>Only data of header is being changed by this application in"
            "<br>original avi-files."
            "<br>If you want to revert the changes back, you should know previous"
            "<br>codec for this file. You can use the Hex-viewer for this.<br>"));**/
    descriptionLabel = new QLabel(tr(
            "This application changes header of video files encoded MPEG4.\n\n"
            "Only data of header is being changed by this application in\n"
            "original avi-files.\n"
            "If you want to revert the changes back, you should know previous\n"
            "codec for this file. You can use the Hex-viewer for this.\n"));   
    
    openFileButton = new QPushButton(tr("Browse"));
    changeButton = new QPushButton(tr("Change"));
    changeButton->setEnabled(false);
    closeButton = new QPushButton(tr("Close"));    

    
    QVBoxLayout *topRightLayout = new QVBoxLayout;
    topRightLayout->addWidget(openFileButton);
    topRightLayout->addWidget(changeButton);
    topRightLayout->addWidget(closeButton);
    
    comboBoxLabel = new QLabel(tr("Choose the codec:"));
    comboBox = new QComboBox;
    comboBoxLabel->setEnabled(false);
    comboBox->setEnabled(false);
    QHBoxLayout *comboBoxLayout = new QHBoxLayout;
    comboBoxLayout->addWidget(comboBoxLabel);
    comboBoxLayout->addWidget(comboBox);
    
    comboBox->addItem(tr("XviD"), QVariant(0));
    comboBox->addItem(tr("DivX 4"), QVariant(1));
    comboBox->addItem(tr("DivX 5"), QVariant(2));
    comboBox->addItem(tr("3iv2"), QVariant(3));
    
    QVBoxLayout *topLeftLayout = new QVBoxLayout;
    topLeftLayout->addWidget(descriptionLabel);
    topLeftLayout->addLayout(comboBoxLayout);
    
    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addLayout(topLeftLayout);
    topLayout->addLayout(topRightLayout);
    
    textEdit = new QTextEdit;
    textEdit->setEnabled(false);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(topLayout);
    layout->addWidget(textEdit);
    
    QObject::connect(openFileButton, SIGNAL(clicked()), this, SLOT(browseClicked()));
    QObject::connect(changeButton, SIGNAL(clicked()), this, SLOT(changeClicked()));
    QObject::connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
    
    setLayout(layout);
    setWindowTitle("FourCC_Changer");
}

