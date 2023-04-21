#pragma once
#include <QtWidgets/QWidget>
#include "ui_LogInManager.h"
#include <QString>
#include <QCoreApplication>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>

using namespace std;

class LogInManager : public QWidget
{
    Q_OBJECT

private:
    string currentUser, currentPassword,
		   usersFile = "users.datafile", accountsFile = "accounts.datafile";
    const char* temporaryFile = "temp.datafile";
	int logInAttempts = 0;

    Ui::LogInManagerClass ui; // ui object

	// Event handlers
private slots:
    void on_loginButton_clicked();
    void on_exitButton_clicked();
    void on_addUserButton_clicked();
	void on_readAccountsButton_clicked();
    void on_addUserConfirmButton_clicked();
	void on_addNewAccountButton_clicked();
	void on_addAccountConfirmButton_clicked();
	void on_removeAccountButton_clicked();
	void on_removeAccountConfirmButton_clicked();
	void on_removeCurrentUserButton_clicked();
	void onAcceptClicked();
	void onRejectClicked();
	void on_goBackButton_clicked();
	void on_infoButton_clicked();


public:
	LogInManager(QWidget* parent = nullptr);
    ~LogInManager();

#pragma region +-----------Public functions declarations---------------+

	// prints text in label
	void printQText(QString text);

	// prints text in textEdit
	void printText(string text);

#pragma region +---------Ui-modifying functions-----------+

	// shows buttons and line edits for login menu
	void showLogInMenu();

	// hides all the buttons and line edits from log in menu
	void hideLogInMenu();

	// shows all the buttons needed for accounts menu
	void showAccountsMenu();

	// hides all the buttons and line edits from accounts menu
	void hideAccountsMenu();

#pragma endregion

	// checks if user exists within a file.
	bool checkForUserName(string fileName, string inputParam);

	// checks if content for current user exists within a file
	bool checkContent(string fileName, string contentToCheck, string decryptionKey);

	// login function
	bool login();

	// adds user
	bool addUser(string newUser, string newPassword);

	// add line function. This function encrypts and adds specified content to file.
	// "encryptionKey" parameter is the key used for encrypting content.
	// "delimiter" parameter is printed after all the content. Default valuse is 0.
	// "endWith" parameter defines the ending of each character. Default value is ' '(space).
	void addLine(string fileName, string content, string encryptionKey, char delimiter = '0', char endWith = ' ');

	// displays all records for current user
	void readAccounts();

	// adds new account records for the current user
	bool addAccount(string newServiceName, string newLogin, string newPassword);

	// removes account record for the current user
	bool removeAccount(string recordToRemove);

	// removes current user and it's accounts file
	void removeUser();

	// Encryption function.
	// Second parameter is used as a key(password) for encrypting.
	long long encrypt(int input, string key = "");

	// Decryption function.
	// Second parameter is used as a key(password) for decrypting.
	char decrypt(long long input, string key = "");

#pragma endregion
};
