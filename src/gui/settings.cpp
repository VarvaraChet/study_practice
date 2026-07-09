#include "settings.h"

Settings::Settings(QWidget *parent) : QDialog(parent){
    setWindowTitle("Настройки алгоритма");
    resize(400, 300);

    auto *mainLayout = new QVBoxLayout(this);
    auto *form = new QFormLayout();

    m_populationSize = new QSpinBox();
    m_populationSize->setRange(2, 1000);

    m_generations = new QSpinBox();
    m_generations->setRange(1, 10000);

    m_tournament = new QSpinBox();
    m_tournament->setRange(2, 10);

    m_elite = new QSpinBox();
    m_elite->setRange(1, 7);

    m_Pc = new QDoubleSpinBox();
    m_Pc->setRange(0.0, 1.0);
    m_Pc->setSingleStep(0.05);
    m_Pc->setDecimals(2);

    m_Pm = new QDoubleSpinBox();
    m_Pm->setRange(0.0, 1.0);
    m_Pm->setSingleStep(0.05);
    m_Pm->setDecimals(2);

    form->addRow("Размер популяции:", m_populationSize);
    form->addRow("Количество поколений:", m_generations);
    form->addRow("Размер турнира:", m_tournament);
    form->addRow("Количество элиты:", m_elite);
    form->addRow("Вероятность скрещивания:", m_Pc);
    form->addRow("Вероятность мутации:", m_Pm);

    mainLayout->addLayout(form);

    auto *buttons = new QHBoxLayout();
    buttons->addStretch();

    m_cancelButton = new QPushButton("Отмена");
    m_okButton = new QPushButton("OK");

    buttons->addWidget(m_cancelButton);
    buttons->addWidget(m_okButton);

    mainLayout->addLayout(buttons);

    connect(m_okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(m_cancelButton, &QPushButton::clicked, this, &QDialog::reject);

    Parameters defaultParameters;
    setParameters(defaultParameters);
}

void Settings::setParameters(const Parameters& parameters){
    m_populationSize->setValue(parameters.populationSize);
    m_generations->setValue(parameters.generations);
    m_tournament->setValue(parameters.tournamentSize);
    m_elite->setValue(parameters.eliteSize);
    m_Pc->setValue(parameters.Pc);
    m_Pm->setValue(parameters.Pm);
}

Parameters Settings::parameters() const{
    Parameters result;

    result.populationSize = m_populationSize->value();
    result.generations = m_generations->value();
    result.tournamentSize = m_tournament->value();
    result.eliteSize = m_elite->value();
    result.Pc = m_Pc->value();
    result.Pm = m_Pm->value();

    return result;
}
