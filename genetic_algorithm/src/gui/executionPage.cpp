#include "executionPage.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>

ExecutionPage::ExecutionPage(QWidget *parent) : QWidget(parent){
    auto *mainLayout = new QVBoxLayout(this);
    auto *buttonLayout = new QHBoxLayout();

    m_nextButton = new QPushButton("Следующий шаг");
    m_runButton = new QPushButton("Выполнить полностью");

    buttonLayout->addWidget(m_nextButton);
    buttonLayout->addWidget(m_runButton);
    buttonLayout->addStretch();

    mainLayout->addLayout(buttonLayout);

    m_generationTable = new QTableWidget();
    m_generationTable->setColumnCount(3);

    QStringList headers;

    headers << "Поколение" << "Средняя задержка" << "Минимальная задержка";

    m_generationTable->setHorizontalHeaderLabels(headers);
    m_generationTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_generationTable->verticalHeader()->setVisible(false);
    m_generationTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_populationTable = new QTableWidget;

    m_populationTable->setColumnCount(2);
    m_populationTable->setHorizontalHeaderLabels({"Порядок", "Задержка"});
    m_populationTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_populationTable->verticalHeader()->setVisible(false);
    m_populationTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QHBoxLayout *centerLayout = new QHBoxLayout;

    centerLayout->addWidget(m_generationTable, 1);
    centerLayout->addWidget(m_populationTable, 1);

    mainLayout->addLayout(centerLayout, 2);

    m_averageSeries = new QLineSeries();
    m_averageSeries->setName("Средняя");

    m_bestSeries = new QLineSeries();
    m_bestSeries->setName("Минимальная");

    auto *chart = new QChart();

    chart->addSeries(m_averageSeries);
    chart->addSeries(m_bestSeries);

    chart->setTitle("Изменение приспособляемости");

    auto *axisX = new QValueAxis();
    axisX->setTitleText("Поколение");
    axisX->setLabelFormat("%d");

    auto *axisY = new QValueAxis();
    axisY->setTitleText("Задержка");

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    m_averageSeries->attachAxis(axisX);
    m_averageSeries->attachAxis(axisY);

    m_bestSeries->attachAxis(axisX);
    m_bestSeries->attachAxis(axisY);

    chart->legend()->setVisible(true);

    m_chartView = new QChartView(chart);

    m_chartView->setRenderHint(QPainter::Antialiasing);
    m_chartView->setMinimumHeight(300);

    mainLayout->addWidget(m_chartView, 3);

    connect(m_nextButton, &QPushButton::clicked, this, &ExecutionPage::nextStepRequested);
    connect(m_runButton, &QPushButton::clicked, this, &ExecutionPage::runRequested);
}

void ExecutionPage::updateState(const AlgorithmState &state){
    addGeneration(state.generation, state.averageFitness, state.bestFitness);
    updatePopulation(state.population);
}

void ExecutionPage::updatePopulation(const std::vector <IndividualState>& population){
    m_populationTable->setRowCount(static_cast<int>(population.size()));

    for (int i=0; i < static_cast<int>(population.size()); i++){
        const IndividualState &individual = population[i];

        m_populationTable->setItem(i, 1, new QTableWidgetItem(QString::number(individual.delay)));

        QString chromosome;
        for (int j=0; j < individual.order.size(); j++){
            chromosome += QString::number(individual.order[j]);

            if (j+1 != individual.order.size())
                chromosome += " ";
        }

        m_populationTable->setItem(i, 0, new QTableWidgetItem(chromosome));
    }
}

void ExecutionPage::addGeneration(int generation, double averageFitness, double bestFitness){
    int row = m_generationTable->rowCount();
    m_generationTable->insertRow(row);

    m_generationTable->setItem(row, 0, new QTableWidgetItem(QString::number(generation)));
    m_generationTable->setItem(row, 1, new QTableWidgetItem(QString::number(averageFitness, 'f', 2)));
    m_generationTable->setItem(row, 2, new QTableWidgetItem(QString::number(bestFitness, 'f', 2)));

    m_generationTable->scrollToBottom();

    m_averageSeries->append(generation, averageFitness);

    m_bestSeries->append(generation, bestFitness);

    double currentMin = std::min(averageFitness, bestFitness);
    double currentMax = std::max(averageFitness, bestFitness);

    m_minFitness = std::min(m_minFitness, currentMin);
    m_maxFitness = std::max(m_maxFitness, currentMax);

    auto *chart = m_chartView->chart();
    auto *axisX = qobject_cast<QValueAxis*>(chart->axes(Qt::Horizontal).first());
    auto *axisY = qobject_cast<QValueAxis*>(chart->axes(Qt::Vertical).first());

    axisX->setRange(0, std::max(1, generation));    
    axisY->setRange(m_minFitness, m_maxFitness);
}
