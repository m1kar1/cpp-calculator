#pragma once

#include "calculator.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    enum class Operation {
        NO_OPERATION,
        MULTIPLICATION,
        DIVISION,
        SUBTRACTION,
        ADDITION,
        POWER,
    };

private slots:

    void on_tb_zero_clicked();
    void on_tb_one_clicked();
    void on_tb_two_clicked();
    void on_tb_three_clicked();
    void on_tb_four_clicked();
    void on_tb_five_clicked();

    void on_tb_six_clicked();
    void on_tb_seven_clicked();
    void on_tb_eight_clicked();
    void on_tb_nine_clicked();

    void on_tb_comma_clicked();

    void on_tb_add_clicked();
    void on_tb_divide_clicked();
    void on_tb_substract_clicked();
    void on_tb_multiplicate_clicked();

    void on_tb_negate_clicked();
    void on_tb_equal_clicked();
    void on_tb_reset_clicked();

    void on_tb_mc_clicked();

    void on_tn_mr_clicked();

    void on_tb_ms_clicked();

    void on_tb_backspace_clicked();

    void on_tb_power_clicked();

private:
    void Calculate(Number number);
    void Reset();
    void ProcessOperation(Operation operation);
    void ProcessDigit(const QString& digit);
    void SetActiveNumber(Number number);
    QString ToString(Operation operation);

    void SetText(const QString& number);
    void AddText(const QString& suffix) {
        SetText(input_number_ + suffix);
    }

    void resizeEvent(QResizeEvent*);

private:
    Ui::MainWindow* ui;

    Operation current_operation_ = Operation::NO_OPERATION;
    Calculator calculator_;
    QString input_number_ = "";
    Number active_number_ = 0;
    Number saved_number_;
    bool has_mem_;
};
