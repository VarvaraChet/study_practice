#include "manualInput.h"

ManualInput::ManualInput(QWidget *parent) : QWidget(parent){
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(30, 30, 30, 30);

    auto *title = new QLabel("Ввести задачи вручную");

    QFont font = title->font();
    font.setPointSize(16);
    font.setBold(true);

    title->setFont(font);

    mainLayout->addWidget(title);

    auto *inputLayout = new QHBoxLayout();
    inputLayout->addWidget(new QLabel("Количество задач:"));

    m_taskCount = new QSpinBox();
    m_taskCount->setRange(1, 10000);
    m_taskCount->setValue(10);

    inputLayout->addWidget(m_taskCount);

    m_createButton = new QPushButton("Создать таблицу");

    inputLayout->addWidget(m_createButton);
    inputLayout->addStretch();

    mainLayout->addLayout(inputLayout);

    m_table = new QTableWidget();
    m_table->setColumnCount(2);

    QStringList headers;
    headers << "Время выполнения" << "Дедлайн";

    m_table->setHorizontalHeaderLabels(headers);
    m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    mainLayout->addWidget(m_table);

    auto *buttonLayout = new QHBoxLayout();

    m_backButton = new QPushButton("Назад");
    m_settingsButton = new QPushButton("Настройки");
    m_startButton = new QPushButton("Запустить");

    buttonLayout->addWidget(m_backButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(m_settingsButton);
    buttonLayout->addWidget(m_startButton);

    mainLayout->addLayout(buttonLayout);

    connect(m_createButton, &QPushButton::clicked, this, &ManualInput::createTable);
    connect(m_backButton, &QPushButton::clicked, this, &ManualInput::backRequested);
    connect(m_settingsButton, &QPushButton::clicked, this, &ManualInput::settingsRequested);
    connect(m_startButton, &QPushButton::clicked, this, &ManualInput::start);
}

void ManualInput::createTable(){
    int count = m_taskCount->value();
    m_table->setRowCount(count);

    for (int i=0; i < count; i++){
        m_table->setVerticalHeaderItem(i, new QTableWidgetItem(QString::number(i+1)));

        m_table->setItem(i, 0, new QTableWidgetItem());
        m_table->setItem(i, 1, new QTableWidgetItem());
    }
}

std::vector <Task> ManualInput::collectTasks(){
    std::vector <Task> tasks;

    for (int i=0; i < m_table->rowCount(); i++){
        Task task;

        task.time = m_table ->item(i, 0) ->text().toInt();
        task.deadline = m_table->item(i,1)->text().toInt();

        tasks.push_back(task);
    }

    return tasks;
}

void ManualInput::start(){
    if(m_table->rowCount() == 0){
        QMessageBox::warning(this, "Ошибка", "Создайте таблицу задач");
        return;
    }

    auto tasks = collectTasks();
    emit startRequested(tasks);
}
