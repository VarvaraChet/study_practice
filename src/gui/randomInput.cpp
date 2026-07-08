#include "randomInput.h"

RandomInput::RandomInput(QWidget *parent) : QWidget(parent){
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(30, 30, 30, 30);

    auto *title = new QLabel("Генерация случайных задач");

    QFont font = title->font();
    font.setPointSize(16);
    font.setBold(true);

    title->setFont(font);

    mainLayout->addWidget(title);

    auto *form = new QFormLayout();

    m_taskCount = new QSpinBox();
    m_taskCount->setRange(1,100000);
    m_taskCount->setValue(100);

    m_minTime = new QSpinBox();
    m_maxTime = new QSpinBox();

    m_minTime->setRange(1, 100000);
    m_maxTime->setRange(1, 100000);

    m_minTime->setValue(1);
    m_maxTime->setValue(50);

    m_minDeadline = new QSpinBox();
    m_maxDeadline = new QSpinBox();

    m_minDeadline->setRange(1, 100000);
    m_maxDeadline->setRange(1, 100000);

    m_minDeadline->setValue(50);
    m_maxDeadline->setValue(500);

    form->addRow("Количество задач", m_taskCount);
    form->addRow("Мин. время выполнения", m_minTime);
    form->addRow("Макс. время выполнения", m_maxTime);
    form->addRow("Мин. дедлайн", m_minDeadline);
    form->addRow("Макс. дедлайн", m_maxDeadline);

    mainLayout->addLayout(form);
    mainLayout->addStretch();

    auto *buttons = new QHBoxLayout();

    m_backButton = new QPushButton("Назад");
    m_settingsButton = new QPushButton("Настройки");
    m_generateButton = new QPushButton("Сгенерировать");

    buttons->addWidget(m_backButton);
    buttons->addStretch();
    buttons->addWidget(m_settingsButton);
    buttons->addWidget(m_generateButton);

    mainLayout->addLayout(buttons);

    connect(m_backButton, &QPushButton::clicked, this, &RandomInput::backRequested);
    connect(m_settingsButton, &QPushButton::clicked, this, &RandomInput::settingsRequested);
    connect(m_generateButton, &QPushButton::clicked, this, &RandomInput::generate);
}

void RandomInput::generate(){
    if(m_minTime->value() > m_maxTime->value()){
        QMessageBox::warning(this, "Ошибка", "Минимальное время выполнения больше максимального.");
        return;
    }

    if(m_minDeadline->value() > m_maxDeadline->value()){
        QMessageBox::warning(this, "Ошибка", "Минимальный дедлайн больше максимального.");
        return;
    }

    std::vector <Task> tasks;
    tasks.reserve(m_taskCount->value());

    for (int i=0; i < m_taskCount->value(); i++){
        Task task;

        task.id = i+1;
        task.time = QRandomGenerator::global()->bounded(m_minTime->value(), m_maxTime->value()+1);
        task.deadline = QRandomGenerator::global()->bounded(m_minDeadline->value(), m_maxDeadline->value()+1);

        tasks.push_back(task);
    }

    emit startRequested(tasks);
}

