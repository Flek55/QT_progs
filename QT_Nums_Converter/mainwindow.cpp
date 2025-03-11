#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Конвертер систем счисления");
    connect(ui->swapButton, &QPushButton::clicked, this, &MainWindow::onSwapClicked);
    connect(ui->convertButton, &QPushButton::clicked, this, &MainWindow::onCalculateClicked);
    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::onClearClicked);
    connect(ui->copyButton, &QPushButton::clicked, this, &MainWindow::onCopyClicked);

    context = allocateContext();

    msgBox.setIcon(QMessageBox::Warning);

    ui->inputComboBox->addItem("Десятеричная", DEC);
    ui->inputComboBox->addItem("Двоичная", BIN);
    ui->inputComboBox->addItem("Восьмеричная", OCT);
    ui->outputComboBox->addItem("Двоичная", BIN);
    ui->outputComboBox->addItem("Восьмеричная", OCT);
    ui->outputComboBox->addItem("Десятичная", DEC);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onCalculateClicked() {
    Params* params = allocateParams();
    parseNumSystems();
    parseInputText(params);
    doOperation(context, VALIDATE, params);
    updateValue(params);
    freeParams(params);
}

void MainWindow::onClearClicked() {
    Params* params = allocateParams();
    doOperation(context, CLEAR_RESULT, params);
    ui->outputLine->setText(QString(context->result));
    ui->inputLine->setText("");
    freeParams(params);
}

void MainWindow::onSwapClicked() {
    Params* params = allocateParams();
    std::string str = ui->inputLine->text().toStdString();
    params->value = str.c_str();
    std::string str2 = ui->outputLine->text().toStdString();
    context->result = str2.c_str();
    parseNumSystems();
    doOperation(context, SWAP, params);
    updateFields(params);
    doOperation(context, CLEAR_RESULT, params);
    freeParams(params);
}

void MainWindow::parseInputText(Params* params) {
    std::string inputText = ui->inputLine->text().toStdString();
    params->value = strdup(inputText.c_str());
}

void MainWindow::updateFields(Params* params) {
    ui->inputLine->setText(QString::fromStdString(params->value));
    ui->outputLine->setText(QString::fromStdString(context->result));
    ui->inputComboBox->setCurrentIndex(ui->inputComboBox->findData(context->oldNumSys));
    ui->outputComboBox->setCurrentIndex(ui->outputComboBox->findData(context->newNumSys));
}

void MainWindow::updateValue(Params* params) {
    if (context->validation != CORRECT) {
        errorSwitchDisplay();
    } else {
        doOperation(context, PARSE_OPERATION, params);

        ui->outputLine->setText(QString(context->result));
    }
}

void MainWindow::onCopyClicked() {
    QGuiApplication::clipboard()->setText(ui->outputLine->text());
}

void MainWindow::displayIncorrectInputError() {
    msgBox.setText("Неверно введенное значение!");
    msgBox.exec();
}

void MainWindow::displayEmptyInputError() {
    msgBox.setText("Введите значение!");
    msgBox.exec();
}

void MainWindow::displayOverflowError() {
    msgBox.setText("Превышен предел значения!");
    msgBox.exec();
}

void MainWindow::displayEmptyStartError() {
    msgBox.setText("Выберите изначальную систему счисления!");
    msgBox.exec();
}

void MainWindow::displayEmptyEndError() {
    msgBox.setText("Выберите конечную систему счисления!");
    msgBox.exec();
}

void MainWindow::displayMaxValueError() {
    msgBox.setText("Введено слишком больше значение!");
    msgBox.exec();
}

void MainWindow::parseNumSystems() {
    context->oldNumSys = (enum NumberSystems)ui->inputComboBox->currentData().toInt();
    context->newNumSys = (enum NumberSystems)ui->outputComboBox->currentData().toInt();
}

void MainWindow::errorSwitchDisplay() {
    switch (context->validation) {
    case EMPTY_TEXT:
        displayEmptyInputError();
        break;
    case INCORRECT_INPUT:
        displayIncorrectInputError();
        break;
    case MAX_LEN_EXCEEDED:
        displayOverflowError();
        break;
    case EMPTY_START_SYS:
        displayEmptyStartError();
        break;
    case EMPTY_END_SYS:
        displayEmptyEndError();
        break;
    case MAX_VALUE_EXCEEDED:
        displayMaxValueError();
        break;
    default:
        break;
    }
}
