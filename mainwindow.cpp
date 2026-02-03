#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

QString RemoveTrailingZeroes(const QString &text) {
    for (qsizetype i = 0; i < text.size(); ++i) {
        if (text[i] != '0') {
            return text.mid(i);
        }
    }
    return "";
}

QString NormalizeNumber(const QString &text) {
    if (text.isEmpty()) {
        return "0";
    }
    if (text.startsWith('.')) {
        return NormalizeNumber("0" + text);
    }
    if (text.startsWith('-')) {
        return "-" + NormalizeNumber(text.mid(1));
    }
    if (text.startsWith('0') && !text.startsWith("0.")) {
        return NormalizeNumber(RemoveTrailingZeroes(text));
    }
    return text;
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->l_result->setText("0");
    ui->l_memory->setText("");
    ui->l_formula->setText("");
    QFont font = ui->l_result->font();

    font.setFamily("Arial Narrow");
    ui->l_result->setFont(font);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent*) {
    QFont font = ui->l_result->font();
    int height =  ui->l_result->height();

    font.setPixelSize(height / 2);
    ui->l_result->setFont(font);
}

QString MainWindow::ToString(Operation operation) {
    switch(operation) {
        case Operation::ADDITION: return "+";
        case Operation::DIVISION: return "÷";
        case Operation::MULTIPLICATION: return "×";
        case Operation::SUBTRACTION: return "−";
        case Operation::POWER: return "^";
        default: return "";
    }
}

void MainWindow::SetActiveNumber(double number) {
    active_number_ = number;
    ui->l_result->setText(QString::number(active_number_));
}

void MainWindow::SetText(const QString& number) {
    input_number_ = NormalizeNumber(number);
    active_number_ = input_number_.toDouble();
    ui->l_result->setText(input_number_);
}

void MainWindow::on_tb_zero_clicked() {
    AddText(ui->tb_zero->text());
}

void MainWindow::on_tb_one_clicked() {
    AddText(ui->tb_one->text());
}

void MainWindow::on_tb_two_clicked() {
    AddText(ui->tb_two->text());
}

void MainWindow::on_tb_three_clicked() {
    AddText(ui->tb_three->text());
}

void MainWindow::on_tb_four_clicked() {
    AddText(ui->tb_four->text());
}

void MainWindow::on_tb_five_clicked() {
    AddText(ui->tb_five->text());
}

void MainWindow::on_tb_six_clicked() {
    AddText(ui->tb_six->text());
}

void MainWindow::on_tb_seven_clicked() {
    AddText(ui->tb_seven->text());
}

void MainWindow::on_tb_eight_clicked() {
    AddText(ui->tb_eight->text());
}

void MainWindow::on_tb_nine_clicked() {
    AddText(ui->tb_nine->text());
}

void MainWindow::on_tb_comma_clicked() {
    AddText(ui->tb_comma->text());
}

void MainWindow::Calculate(double number) {
    switch(current_operation_) {
        case Operation::ADDITION: calculator_.Add(number); break;
        case Operation::DIVISION: calculator_.Div(number); break;
        case Operation::MULTIPLICATION: calculator_.Mul(number); break;
        case Operation::SUBTRACTION: calculator_.Sub(number); break;
        case Operation::POWER: calculator_.Pow(number); break;
        default: break;
    }

    SetActiveNumber(calculator_.GetNumber());
}

void MainWindow::Reset() {
    current_operation_ = Operation::NO_OPERATION;
    input_number_.clear();
}

void MainWindow::ProcessOperation(Operation operation) {
    QString operation_str = ToString(operation);

    if (current_operation_ == Operation::NO_OPERATION) {
        calculator_.Set(active_number_);
    }

    current_operation_ = operation;

    ui->l_formula->setText(QString::number(calculator_.GetNumber()) + operation_str);
    input_number_.clear();
}

void MainWindow::on_tb_equal_clicked() {
    if(current_operation_ == Operation::NO_OPERATION) {
        return;
    }

    QString operation_str = ToString(current_operation_);

    double second_number = active_number_;
    ui->l_formula->setText(QString("%1 " + operation_str + " %2 =").arg(calculator_.GetNumber()).arg(second_number));
    Calculate(second_number);
    Reset();
}

void MainWindow::on_tb_add_clicked() {
    ProcessOperation(Operation::ADDITION);
}

void MainWindow::on_tb_divide_clicked() {
    ProcessOperation(Operation::DIVISION);
}

void MainWindow::on_tb_substract_clicked() {
    ProcessOperation(Operation::SUBTRACTION);
}

void MainWindow::on_tb_multiplicate_clicked() {
    ProcessOperation(Operation::MULTIPLICATION);
}

void MainWindow::on_tb_power_clicked() {
    ProcessOperation(Operation::POWER);
}

void MainWindow::on_tb_negate_clicked() {
    if (input_number_.startsWith('-')) {
        input_number_ = input_number_.mid(1);
    } else {
        input_number_ = "-" + input_number_;
    }
    SetText(input_number_);
}

void MainWindow::on_tb_reset_clicked() {
    SetActiveNumber(0.);
    calculator_.Set(0.);

    Reset();
    ui->l_formula->clear();
}

void MainWindow::on_tb_mc_clicked() {
    has_mem_ = false;
    ui->l_memory->setText("");
}

void MainWindow::on_tn_mr_clicked() {
    if(!has_mem_) {
        return;
    }

    SetActiveNumber(saved_number_);
    input_number_.clear();
}

void MainWindow::on_tb_ms_clicked() {
    saved_number_ = active_number_;
    has_mem_ = true;
    ui->l_memory->setText("M");
}

void MainWindow::on_tb_backspace_clicked() {
    if (input_number_.isEmpty()) {
        return;
    }

    input_number_.chop(1);
    SetText(input_number_);
}
