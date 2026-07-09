#ifndef EXECUTION_PAGE_H
#define EXECUTION_PAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QPainter>

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

#include "../algorithm/algorithmState.h"
#include "../algorithm/task.h"

class QPushButton;
class QTableWidget;

class ExecutionPage : public QWidget{
    Q_OBJECT

    public:
        explicit ExecutionPage(QWidget *parent=nullptr);
        void setTasks(const std::vector <Task>& t);

    public slots:
        void updateState(const AlgorithmState& state);
        void showIndividual(const Individual& individ);

    signals:
        void nextStepRequested();
        void runRequested();

        void individualSelected(int row);


    private:
        void addGeneration(int generation, double averageFitness, double bestFitness);
        void updatePopulation(const std::vector <Individual>& population);

        QPushButton *m_nextButton;
        QPushButton *m_runButton;

        QTableWidget *m_generationTable;
        QTableWidget *m_populationTable;
        QTableWidget *m_individualTable;

        std::vector <Task> tasks;

        QChartView *m_chartView;

        QLineSeries *m_averageSeries;
        QLineSeries *m_bestSeries;

        double m_minFitness = std::numeric_limits<double>::max();
        double m_maxFitness = std::numeric_limits<double>::lowest();
};

#endif
