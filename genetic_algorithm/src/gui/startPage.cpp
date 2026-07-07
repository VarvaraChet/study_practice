#include "startPage.h"

StartPage::StartPage(QWidget *parent) : QWidget(parent){
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(40, 40, 40, 40);

    auto *title = new QLabel("Минимизация задержек");
    title->setAlignment(Qt::AlignCenter);

    QFont font = title->font();
    font.setPointSize(18);
    font.setBold(true);

    title->setFont(font);

    mainLayout->addWidget(title);

    auto *text = new QLabel("Дано N задач, каждая их которых имеет свое время выполнения и дедлайн к которому она должна быть выполнена.\nСоставляется расписание с минимальными задержками.\nЗадержка – количество времени на которое выполнение задач превысило дедлайны.");
    text->setAlignment(Qt::AlignCenter);

    QFont text_font = text->font();
    text_font.setPointSize(15);

    title->setFont(text_font);

    mainLayout->addWidget(text);

    auto *group = new QGroupBox("Выберите способ ввода данных");

    m_manualRadio = new QRadioButton("Ввести вручную");
    m_fileRadio = new QRadioButton("Загрузить из файла");
    m_randomRadio = new QRadioButton("Сгенерировать случайные данные");

    m_manualRadio->setChecked(true);

    auto *groupLayout = new QVBoxLayout(group);
    groupLayout->addWidget(m_manualRadio);
    groupLayout->addWidget(m_fileRadio);
    groupLayout->addWidget(m_randomRadio);

    mainLayout->addWidget(group);

    auto *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();

    m_nextButton = new QPushButton("Далее");

    buttonLayout->addWidget(m_nextButton);

    mainLayout->addLayout(buttonLayout);

    connect(m_nextButton, &QPushButton::clicked, this, &StartPage::onNextClicked);
}

void StartPage::onNextClicked(){
    if (m_manualRadio->isChecked())
        emit manualSelected();
    else if (m_fileRadio->isChecked())
        emit fileSelected();
    else if (m_randomRadio->isChecked())
        emit randomSelected();
}
