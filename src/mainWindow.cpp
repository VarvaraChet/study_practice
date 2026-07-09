#include "mainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    resize(1000, 700);

    setWindowTitle("Расписание");

    createPages();

    m_controller = new Controller(this);

    createConnections();

    setCentralWidget(m_stack);

    showStartPage();
}

void MainWindow::createPages(){
    m_stack = new QStackedWidget(this);

    m_startPage = new StartPage();
    m_manualPage = new ManualInput();
    m_filePage = new FileInput();
    m_randomPage = new RandomInput();
    m_executionPage = new ExecutionPage();

    m_stack->addWidget(m_startPage);
    m_stack->addWidget(m_manualPage);
    m_stack->addWidget(m_filePage);
    m_stack->addWidget(m_randomPage);
    m_stack->addWidget(m_executionPage);
}

void MainWindow::createConnections(){
    connect(m_startPage, &StartPage::manualSelected, this, &MainWindow::showManualPage);
    connect(m_startPage, &StartPage::fileSelected, this, &MainWindow::showFilePage);
    connect(m_startPage, &StartPage::randomSelected, this, &MainWindow::showRandomPage);

    connect(m_manualPage, &ManualInput::backRequested, this, &MainWindow::showStartPage);
    connect(m_manualPage, &ManualInput::settingsRequested, this, &MainWindow::openSettings);
    connect(m_manualPage, &ManualInput::startRequested, this, &MainWindow::run);

    connect(m_filePage, &FileInput::backRequested, this, &MainWindow::showStartPage);
    connect(m_filePage, &FileInput::settingsRequested, this, &MainWindow::openSettings);
    connect(m_filePage, &FileInput::startRequested, this, &MainWindow::runFile);

    connect(m_randomPage, &RandomInput::backRequested, this, &MainWindow::showStartPage);
    connect(m_randomPage, &RandomInput::settingsRequested, this, &MainWindow::openSettings);
    connect(m_randomPage, &RandomInput::startRequested, this, &MainWindow::run);

    connect(m_controller, &Controller::stateChange, m_executionPage, &ExecutionPage::updateState);
    connect(m_executionPage, &ExecutionPage::nextStepRequested, m_controller, &Controller::step);
    connect(m_executionPage, &ExecutionPage::runRequested, m_controller, &Controller::fullExecute);

    connect(m_executionPage, &ExecutionPage::nextStepRequested, this, [](){});
    connect(m_executionPage, &ExecutionPage::runRequested, this, [](){});

    connect(m_executionPage, &ExecutionPage::individualSelected, m_controller, &Controller::showIndividual);
    connect(m_controller, &Controller::individualReady, m_executionPage, &ExecutionPage::showIndividual);

}

void MainWindow::showStartPage(){
    m_stack->setCurrentWidget(m_startPage);
}

void MainWindow::showManualPage(){
    m_stack->setCurrentWidget(m_manualPage);
}

void MainWindow::showFilePage(){
    m_stack->setCurrentWidget(m_filePage);
}

void MainWindow::showRandomPage(){
    m_stack->setCurrentWidget(m_randomPage);
}

void MainWindow::showExecutionPage(){
    m_stack->setCurrentWidget(m_executionPage);
}

void MainWindow::openSettings(){
    Settings dialog(this);

    dialog.setParameters(parameters);

    if (dialog.exec() == QDialog::Accepted)
        parameters = dialog.parameters();
}

void MainWindow::run(const std::vector<Task>& tasks){
    m_executionPage->setTasks(tasks);
    m_controller->run(tasks, parameters);

    showExecutionPage();
}

void MainWindow::runFile(const QString &fileName){
    DataLoader loader;

    std::vector <Task> tasks;
    if (!loader.load(fileName.toStdString(), tasks)){
        QMessageBox::warning(this, "Ошибка", "Не удалось загрузить файл.");
        return;
    }

    m_executionPage->setTasks(tasks);
    m_controller->run(tasks, parameters);

    showExecutionPage();
}
