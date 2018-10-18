/*
 * Copyright(C) 2010,Hikvision Digital Technology Co., Ltd 
 * 
 * File Name£ºmain.cpp
 * Description£º
 * Version£º1.0
 * author£º gongpu wang
 * Create Time£º2009/11/12/
 * modify£º
 */

#include "qtclientdemo.h"
#include <QTextCodec>
#include <QtGui>
#include <QApplication>


//main Windows
QtClientDemo* gqtclinetdemo;

/*******************************************************************
      Function:   main
   Description:   
     Parameter:   (IN)   int argc  
                  (IN)   char *argv[]  
        Return:   0--success£¬-1--failed¡£   
**********************************************************************/
int main(int argc, char *argv[])
{
	gqtclinetdemo = NULL;   
    QApplication a(argc, argv);
	QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));

    //Add translation file.
    QTranslator translator;
    BOOL bSuc;
    bSuc = translator.load("..//..//..//..//translation//QtDemo_zh_CN");
    if (!bSuc)
    {
         bSuc = translator.load("..//..//translation//QtDemo_zh_CN");
    }
    if (!bSuc)
    {
        translator.load("translation/QtDemo_zh_CN");
    }
    if (!bSuc)
    {
        translator.load("./QtDemo_zh_CN");
    }
    a.installTranslator(&translator);

    //Show the main window.
    QtClientDemo w;
	w.show();
	gqtclinetdemo =&w;
    return a.exec();
}
