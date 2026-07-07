#ifndef MANUAL_INPUT_H
#define MANUAL_INPUT_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QTableWidget>
#include <QHeaderView>
#include <QLabel>
#include <QMessageBox>

#include <vector>

#include "../algorithm/task.h"

class QSpinBox;
class QPushButton;
class QTableWidget;

class ManualInput : public QWidget{
    Q_OBJECT

    public:
        explicit ManualInput(QWidget *parent=nullptr);

    signals:
        void backRequested();
        void settingsRequested();
        void startRequested(const std::vector<Task>& tasks);

    private slots:
        void createTable();
        void start();

    private:
        QSpinBox *m_taskCount;

        QPushButton *m_createButton;

        QTableWidget *m_table;

        QPushButton *m_backButton;
        QPushButton *m_settingsButton;
        QPushButton *m_startButton;

        std::vector <Task> collectTasks();
};

#endif
