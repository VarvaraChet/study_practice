#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>

#include "../algorithm/parameters.h"

class QSpinBox;
class QDoubleSpinBox;
class QPushButton;

class Settings : public QDialog{
    Q_OBJECT

    public:
        explicit Settings(QWidget *parent=nullptr);

        void setParameters(const Parameters& parameters);

        Parameters parameters() const;

    private:
        QSpinBox *m_populationSize;
        QSpinBox *m_generations;

        QDoubleSpinBox *m_Pc;
        QDoubleSpinBox *m_Pm;

        QPushButton *m_okButton;
        QPushButton *m_cancelButton;
};

#endif
