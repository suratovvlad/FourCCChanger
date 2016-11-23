/*
 * File:   main.cpp
 * Author: Suratov Vladislav
 *
 * Created on August 3, 2012, 6:36 PM
 */

#include <QApplication>
#include <QTextCodec>
#include "changer.h"
#include <QTranslator>
#include <QLocale>

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);

    // create and show your widgets here
    
    QTranslator translator;
	translator.load(":/translations/fourccchanger_ru.qm", ".");
    app.installTranslator(&translator);
    
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
	//QTextCodec::setCodecForTr(codec);
    
	//QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);
    
    /*It doesn't work. I don't know why. 
     * But I know if it is enable, this program doesn't want to work with path contains Cyrillic alphabet
    //QTextCodec::setCodecForCStrings(codec);
    //QTextCodec::setCodecForLocale(codec);
     * */
    
    Changer *obj = new Changer;
    obj->show();
    
    return app.exec();
}
