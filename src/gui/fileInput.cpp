#include "fileInput.h"

FileInput::FileInput(QWidget *parent) : QWidget(parent){
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(30, 30, 30, 30);

    auto *title = new QLabel("Загрузка задач из файла");

    QFont font = title->font();
    font.setPointSize(16);
    font.setBold(true);

    title->setFont(font);

    mainLayout->addWidget(title);

    auto *fileLayout = new QHBoxLayout();
    fileLayout->addWidget(new QLabel("Файл:"));

    m_filePath = new QLineEdit();
    m_filePath->setReadOnly(true);

    m_browseButton =new QPushButton("Обзор...");

    fileLayout->addWidget(m_filePath);
    fileLayout->addWidget(m_browseButton);

    mainLayout->addLayout(fileLayout);
    mainLayout->addStretch();

    auto *buttons = new QHBoxLayout();

    m_backButton = new QPushButton("Назад");
    m_settingsButton = new QPushButton("Настройки");
    m_startButton = new QPushButton("Запустить");

    buttons->addWidget(m_backButton);
    buttons->addStretch();
    buttons->addWidget(m_settingsButton);
    buttons->addWidget(m_startButton);

    mainLayout->addLayout(buttons);

    connect(m_browseButton, &QPushButton::clicked, this, &FileInput::browseFile);
    connect(m_backButton, &QPushButton::clicked, this, &FileInput::backRequested);
    connect(m_settingsButton, &QPushButton::clicked, this, &FileInput::settingsRequested);
    connect(m_startButton, &QPushButton::clicked, this, &FileInput::start);
}

void FileInput::browseFile(){
    QString fileName = QFileDialog::getOpenFileName(this,"Выберите файл", "", "Text (*.txt)");

    if (!fileName.isEmpty())
        m_filePath->setText(fileName);

}

void FileInput::start(){
    if (m_filePath->text().isEmpty()){
        QMessageBox::warning(this, "Ошибка", "Выберите файл");
        return;
    }

    emit startRequested(m_filePath->text());
}

