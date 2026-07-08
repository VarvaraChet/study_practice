#ifndef RANDOM_INPUT_H
#define RANDOM_INPUT_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QRandomGenerator>

#include <vector>

#include "../algorithm/task.h"

class QSpinBox;
class QPushButton;

class RandomInput : public QWidget{
    Q_OBJECT

    public:
        explicit RandomInput(QWidget *parent = nullptr);

    signals:
        void backRequested();
        void settingsRequested();
        void startRequested(const std::vector <Task>& tasks);

    private slots:
        void generate();

    private:
        QSpinBox *m_taskCount;

        QSpinBox *m_minTime;
        QSpinBox *m_maxTime;

        QSpinBox *m_minDeadline;
        QSpinBox *m_maxDeadline;

        QPushButton *m_backButton;
        QPushButton *m_settingsButton;
        QPushButton *m_generateButton;
};

#endif
