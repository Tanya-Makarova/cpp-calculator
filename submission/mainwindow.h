#pragma once

#include "enums.h"

#include <functional>
#include <optional>
#include <string>

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

    void SetInputText(const std::string& text);
    void SetErrorText(const std::string& text);
    void SetFormulaText(const std::string& text);
    void SetMemText(const std::string& text);
    void SetExtraKey(const std::optional<std::string>& key);

    void SetDigitKeyCallback(std::function<void(int key)> callback);
    void SetProcessOperationKeyCallback(std::function<void(Operation key)> callback);
    void SetProcessControlKeyCallback(std::function<void(ControlKey key)> callback);
    void SetControllerCallback(std::function<void(ControllerType controller)> callback);

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

    void on_tb_add_clicked();
    void on_tb_substract_clicked();
    void on_tb_multiplicate_clicked();
    void on_tb_divide_clicked();
    void on_tb_power_clicked();

    void on_tb_equal_clicked();
    void on_tb_reset_clicked();
    void on_tb_mc_clicked();
    void on_tn_mr_clicked();
    void on_tb_ms_clicked();
    void on_tb_negate_clicked();
    void on_tb_backspace_clicked();
    void on_tb_extra_clicked();

    void on_cmb_controller_currentIndexChanged(int index);

private:
    ControllerType GetControllerType(const std::string& text) const;

    Ui::MainWindow* ui;

    std::function<void(int key)> digit_key_callback_;
    std::function<void(Operation key)> operation_key_callback_;
    std::function<void(ControlKey key)> control_key_callback_;
    std::function<void(ControllerType controller)> controller_callback_;
};
