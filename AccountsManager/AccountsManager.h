#pragma once
#include "AppManager.h"
#include "ui_AccountsManager.h"
#include <QtWidgets/QWidget>
#include <QFrame>
#include <QPushButton>
#include <QInputDialog>
#include <QDialogButtonBox>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QFile>
#include <QDir>
#include <QCoreApplication>
#include <QDesktopServices>
#include <QUrl>
#include <QSettings>

using namespace std;

class AccountsManager : public QWidget
{
	Q_OBJECT

private:
	Ui::AccountsManagerClass ui; // ui object
	AppManager app;

#pragma region +------UI elements--------+

	QLabel * label{};

	QPushButton* loginButton{}, * addUserButton{}, * addUserConfirmButton{}, * exitButton{}, * infoButton{}, * themeButton{},
		* readAccountsButton{}, * addAccountButton{}, * addAccountConfirmButton{}, * removeAccountButton{},
		* removeAccountConfirmButton{}, * removeCurrentUserButton{}, * goToLoginMenuButton{}, * goToAccountsMenuButton{};

	QDialogButtonBox* removeUserButtonBox{};

	QLineEdit* serviceNameEdit{}, * loginLineEdit{}, * passwordLineEdit{};

	QTextEdit* textEdit{};

#pragma endregion

#pragma region +---------Ui-modifying functions-----------+

	// Loads specified theme
	void loadTheme(QString fileName);
	// Gets and loads the theme that's saved in the settings
	void getTheme();
	void addButton(QPushButton*& button, QString label, int position = -1);
	void addLabel(QLabel*& label, QString placeholder, int position = -1);
	void addLineEdit(QLineEdit*& lineEdit, QString placeholder, int position = -1);
	void addTextEdit(QTextEdit*& textEdit, QString placeholder, int position = -1);
	void addDialogButton(QDialogButtonBox*& button, int position = -1);

	// shows buttons and line edits for login menu
	void showLogInMenu();

	// hides all the buttons and line edits from log in menu
	void hideLogInMenu();

	// shows all the buttons needed for accounts menu
	void showAccountsMenu();

	// hides all the buttons and line edits from accounts menu
	void hideAccountsMenu();

#pragma endregion

#pragma region +-----Event handlers-----+

private slots:
	void on_loginButton_clicked();
	void on_addUserButton_clicked();
	void on_addUserConfirmButton_clicked();
	void on_exitButton_clicked();
	void on_infoButton_clicked();
	void on_themeButton_clicked();

	void on_readAccountsButton_clicked();
	void on_addNewAccountButton_clicked();
	void on_addAccountConfirmButton_clicked();
	void on_removeAccountButton_clicked();
	void on_removeAccountConfirmButton_clicked();
	void on_removeCurrentUserButton_clicked();
	void onAcceptClicked();
	void on_goToLoginMenuButton_clicked();
	void on_goToAccountsMenuButton_clicked();
	

#pragma endregion

public:
	AccountsManager(QWidget* parent = nullptr);
	~AccountsManager();

#pragma region +-----------Public functions declarations---------------+

	// prints text in label
	void printQText(QString text);

	// prints text in textEdit
	void printText(string text);

#pragma endregion
};
