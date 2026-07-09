#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QDialog>

#include "algorithm/parameters.h"
#include "gui/startPage.h"
#include "gui/manualInput.h"
#include "gui/fileInput.h"
#include "gui/randomInput.h"
#include "gui/executionPage.h"
#include "gui/dataLoader.h"
#include "gui/settings.h"
#include "controller.h"

class QStackedWidget;
class StartPage;
class ManualInput;
class FileInput;
class ExecutionPage;

class MainWindow : public QMainWindow{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);

    private slots:
        void showStartPage();
        void showManualPage();
        void showFilePage();
        void showRandomPage();

        void showExecutionPage();

        void openSettings();

        void run(const std::vector<Task>& tasks);
        void runFile(const QString& fileName);

    private:
        QStackedWidget *m_stack;

        StartPage *m_startPage;
        ManualInput *m_manualPage;
        FileInput *m_filePage;
        RandomInput *m_randomPage;

        ExecutionPage *m_executionPage;

        Controller *m_controller;

        Parameters parameters;

        void createPages();
        void createConnections();
};

#endif
