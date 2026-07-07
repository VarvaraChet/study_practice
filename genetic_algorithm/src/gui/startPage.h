#ifndef START_PAGE_H
#define START_PAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QPushButton>
#include <QLabel>

class QRadioButton;
class QPushButton;


class StartPage : public QWidget{
    Q_OBJECT

    public:
        explicit StartPage(QWidget *parent=nullptr);

    signals:
        void manualSelected();
        void fileSelected();
        void randomSelected();

    private slots:
        void onNextClicked();

    private:
        QRadioButton *m_manualRadio;
        QRadioButton *m_fileRadio;
        QRadioButton *m_randomRadio;

        QPushButton *m_nextButton;
};

#endif
