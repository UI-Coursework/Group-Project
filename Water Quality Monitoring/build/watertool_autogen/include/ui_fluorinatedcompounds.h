/********************************************************************************
** Form generated from reading UI file 'fluorinatedcompounds.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FLUORINATEDCOMPOUNDS_H
#define UI_FLUORINATEDCOMPOUNDS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FluorinatedCompounds
{
public:
    QWidget *centralWidget;

    void setupUi(QDialog *FluorinatedCompounds)
    {
        if (FluorinatedCompounds->objectName().isEmpty())
            FluorinatedCompounds->setObjectName("FluorinatedCompounds");
        FluorinatedCompounds->resize(800, 600);
        centralWidget = new QWidget(FluorinatedCompounds);
        centralWidget->setObjectName("centralWidget");
        centralWidget->setGeometry(QRect(20, 10, 761, 571));

        retranslateUi(FluorinatedCompounds);

        QMetaObject::connectSlotsByName(FluorinatedCompounds);
    } // setupUi

    void retranslateUi(QDialog *FluorinatedCompounds)
    {
        (void)FluorinatedCompounds;
    } // retranslateUi

};

namespace Ui {
    class FluorinatedCompounds: public Ui_FluorinatedCompounds {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FLUORINATEDCOMPOUNDS_H
