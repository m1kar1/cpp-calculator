#include "mainwindow.h"

#include "ui_mainwindow.h"

#include <QComboBox>
#include <QPushButton>
#include <QStringList>
#include <utility>

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui_(new Ui::MainWindow) {
	ui_->setupUi(this);

	ui_->cmb_controller->clear();
	ui_->cmb_controller->addItems(QStringList{
		"double",
		"float",
		"uint8_t",
		"int",
		"int64_t",
		"size_t",
		"Rational",
	});

	connect(ui_->tb_0, &QPushButton::clicked, this, [this](){ if (digit_cb_) { digit_cb_(0); } });
	connect(ui_->tb_1, &QPushButton::clicked, this, [this](){ if (digit_cb_) { digit_cb_(1); } });
	connect(ui_->tb_2, &QPushButton::clicked, this, [this](){ if (digit_cb_) { digit_cb_(2); } });
	connect(ui_->tb_3, &QPushButton::clicked, this, [this](){ if (digit_cb_) { digit_cb_(3); } });
	connect(ui_->tb_4, &QPushButton::clicked, this, [this](){ if (digit_cb_) { digit_cb_(4); } });
	connect(ui_->tb_5, &QPushButton::clicked, this, [this](){ if (digit_cb_) { digit_cb_(5); } });
	connect(ui_->tb_6, &QPushButton::clicked, this, [this](){ if (digit_cb_) { digit_cb_(6); } });
	connect(ui_->tb_7, &QPushButton::clicked, this, [this](){ if (digit_cb_) { digit_cb_(7); } });
	connect(ui_->tb_8, &QPushButton::clicked, this, [this](){ if (digit_cb_) { digit_cb_(8); } });
	connect(ui_->tb_9, &QPushButton::clicked, this, [this](){ if (digit_cb_) { digit_cb_(9); } });

	connect(ui_->tb_add, &QPushButton::clicked, this, [this](){ if (operation_cb_) { operation_cb_(Operation::ADDITION); } });
	connect(ui_->tb_sub, &QPushButton::clicked, this, [this](){ if (operation_cb_) { operation_cb_(Operation::SUBTRACTION); } });
	connect(ui_->tb_mul, &QPushButton::clicked, this, [this](){ if (operation_cb_) { operation_cb_(Operation::MULTIPLICATION); } });
	connect(ui_->tb_div, &QPushButton::clicked, this, [this](){ if (operation_cb_) { operation_cb_(Operation::DIVISION); } });
	connect(ui_->tb_pow, &QPushButton::clicked, this, [this](){ if (operation_cb_) { operation_cb_(Operation::POWER); } });

	connect(ui_->tb_equals, &QPushButton::clicked, this, [this](){ if (control_cb_) { control_cb_(ControlKey::EQUALS); } });
	connect(ui_->tb_clear, &QPushButton::clicked, this, [this](){ if (control_cb_) { control_cb_(ControlKey::CLEAR); } });
	connect(ui_->tb_mem_save, &QPushButton::clicked, this, [this](){ if (control_cb_) { control_cb_(ControlKey::MEM_SAVE); } });
	connect(ui_->tb_mem_load, &QPushButton::clicked, this, [this](){ if (control_cb_) { control_cb_(ControlKey::MEM_LOAD); } });
	connect(ui_->tb_mem_clear, &QPushButton::clicked, this, [this](){ if (control_cb_) { control_cb_(ControlKey::MEM_CLEAR); } });
	connect(ui_->tb_plus_minus, &QPushButton::clicked, this, [this](){ if (control_cb_) { control_cb_(ControlKey::PLUS_MINUS); } });
	connect(ui_->tb_backspace, &QPushButton::clicked, this, [this](){ if (control_cb_) { control_cb_(ControlKey::BACKSPACE); } });
	connect(ui_->tb_extra, &QPushButton::clicked, this, [this](){ if (control_cb_) { control_cb_(ControlKey::EXTRA_KEY); } });

	connect(ui_->cmb_controller, qOverload<int>(&QComboBox::currentIndexChanged), this, [this](int) {
		if (controller_cb_) {
			controller_cb_(ParseControllerType(ui_->cmb_controller->currentText()));
		}
	});
}

MainWindow::~MainWindow() {
	delete ui_;
}

void MainWindow::SetInputText(const std::string& text) {
	ui_->l_result->setStyleSheet("");
	ui_->l_result->setText(QString::fromStdString(text));
}

void MainWindow::SetErrorText(const std::string& text) {
	ui_->l_result->setStyleSheet("color: red;");
	ui_->l_result->setText(QString::fromStdString(text));
}

void MainWindow::SetFormulaText(const std::string& text) {
	ui_->l_formula->setText(QString::fromStdString(text));
}

void MainWindow::SetMemText(const std::string& text) {
	ui_->l_memory->setText(QString::fromStdString(text));
}

void MainWindow::SetExtraKey(const std::optional<std::string>& key) {
	if (!key.has_value()) {
		ui_->tb_extra->hide();
		return;
	}

	ui_->tb_extra->show();
	ui_->tb_extra->setText(QString::fromStdString(key.value()));
}

void MainWindow::SetDigitKeyCallback(std::function<void(int key)> cb) {
	digit_cb_ = std::move(cb);
}

void MainWindow::SetProcessOperationKeyCallback(std::function<void(Operation key)> cb) {
	operation_cb_ = std::move(cb);
}

void MainWindow::SetProcessControlKeyCallback(std::function<void(ControlKey key)> cb) {
	control_cb_ = std::move(cb);
}

void MainWindow::SetControllerCallback(std::function<void(ControllerType controller)> cb) {
	controller_cb_ = std::move(cb);
}

ControllerType MainWindow::ParseControllerType(const QString& text) const {
	if (text == "double") {
		return ControllerType::DOUBLE;
	}
	if (text == "float") {
		return ControllerType::FLOAT;
	}
	if (text == "uint8_t") {
		return ControllerType::UINT8_T;
	}
	if (text == "int") {
		return ControllerType::INT;
	}
	if (text == "int64_t") {
		return ControllerType::INT64_T;
	}
	if (text == "size_t") {
		return ControllerType::SIZE_T;
	}
	return ControllerType::RATIONAL;
}