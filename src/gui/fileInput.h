#ifndef FILEINPUT_H
#define FILEINPUT_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>

class QLineEdit;
class QPushButton;

class FileInput : public QWidget{
    Q_OBJECT

    public:
        explicit FileInput(QWidget *parent=nullptr);

    signals:
        void backRequested();
        void settingsRequested();
        void startRequested(const QString& fileName);

    private slots:
        void browseFile();
        void start();


    private:
        QLineEdit *m_filePath;

        QPushButton *m_browseButton;
        QPushButton *m_backButton;
        QPushButton *m_settingsButton;
        QPushButton *m_startButton;
};

#endif
