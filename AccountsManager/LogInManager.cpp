// TODO: separate the app into 2 windows
// TODO: add white theme

#include "LogInManager.h"

LogInManager::LogInManager(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	// Set application info
	QCoreApplication::setApplicationName("Account Manager");
	QCoreApplication::setApplicationVersion("0.0.2-beta");
	QCoreApplication::setOrganizationName("music-soul1-1");
	QCoreApplication::setOrganizationDomain("https://github.com/music-soul1-1");

	// hiding all unnecessary ui elements
	ui.addUserConfirmButton->hide();
	ui.addAccountConfirmButton->hide();
	ui.addNewAccountButton->hide();
	ui.goBackButton->hide();
	ui.readAccountsButton->hide();
	ui.removeAccountButton->hide();
	ui.removeAccountConfirmButton->hide();
	ui.removeCurrentUserButton->hide();
	ui.textEdit->hide();
	ui.serviceNameEdit->hide();
	ui.removeUserButtonBox->hide();

	// connecting accept and reject buttons(needed for removing current user)
	QObject::connect(ui.removeUserButtonBox, SIGNAL(accepted()), this, SLOT(onAcceptClicked()));
	QObject::connect(ui.removeUserButtonBox, SIGNAL(rejected()), this, SLOT(onRejectClicked()));
}

LogInManager::~LogInManager()
{}

// prints text in label
void LogInManager::printQText(QString text)
{
	ui.label->setText(text);
}

// prints text in textEdit
void LogInManager::printText(string text)
{
	ui.textEdit->append(QString::fromStdString(text));
}

#pragma region +---------Ui-modifying functions-----------+

void LogInManager::showLogInMenu()
{
	ui.loginLineEdit->show();
	ui.passwordLineEdit->show();

	ui.loginButton->show();
	ui.addUserButton->show();
	ui.exitButton->show();
	ui.infoButton->show();

	printQText("Enter user login and password");
	ui.loginLineEdit->setPlaceholderText("login");
	ui.passwordLineEdit->setPlaceholderText("password");
}

void LogInManager::hideLogInMenu()
{
	ui.loginButton->hide();
	ui.addUserButton->hide();
	ui.exitButton->hide();
	ui.infoButton->hide();

	ui.loginLineEdit->hide();
	ui.passwordLineEdit->hide();
}

void LogInManager::showAccountsMenu()
{
	printQText("Choose action");
	ui.readAccountsButton->show();
	ui.addNewAccountButton->show();
	ui.removeAccountButton->show();
	ui.removeCurrentUserButton->show();
	ui.goBackButton->show();
}

void LogInManager::hideAccountsMenu()
{
	ui.readAccountsButton->hide();
	ui.textEdit->hide();
	ui.addNewAccountButton->hide();
	ui.removeAccountButton->hide();
	ui.removeCurrentUserButton->hide();

	ui.serviceNameEdit->hide();
	ui.loginLineEdit->hide();
	ui.passwordLineEdit->hide();
	//ui.goBackButton->hide();
}

#pragma endregion

#pragma region +-------------Event handlers--------------+

void LogInManager::on_infoButton_clicked()
{
	QMessageBox* appInfo = new QMessageBox(this);

	QString info = QString("%1 \nv.%2 \n%3 \n%4 \n\n%5").arg(QCoreApplication::applicationName()).arg(
					QCoreApplication::applicationVersion()).arg(
					QCoreApplication::organizationName()).arg(
					QCoreApplication::organizationDomain()).arg("Visit the app page on GitHub?");

	QMessageBox::StandardButton reply = QMessageBox::question(nullptr, "Application Information", info,
										QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

	if (reply == QMessageBox::Yes) {
		QDesktopServices::openUrl(QUrl("https://github.com/music-soul1-1/AccountsManager"));
	}
}

void LogInManager::on_exitButton_clicked()
{
	quick_exit(0);
}

void LogInManager::on_loginButton_clicked()
{
	currentUser = (ui.loginLineEdit->text()).toStdString();
	currentPassword = (ui.passwordLineEdit->text()).toStdString();

	if (LogInManager::login() && currentPassword != "" && currentPassword != " ")
	{
		logInAttempts = 0;
		printQText("Successfully logged in. Choose action:");

		// hiding all unnecessary ui elements
		hideLogInMenu();

		// showing all necessary ui elements
		showAccountsMenu();
	}
	else
	{
		printQText("Username or password isn't correct");
		if (logInAttempts <= 2)
		{
			logInAttempts++;
		}
		else
		{
			QMessageBox* attempsWarning = new QMessageBox(this);

			QString info = "You have exceeded the maximum number of login attempts.";
			QMessageBox::warning(nullptr, "Attempts excess", info);
			
			on_exitButton_clicked();
		}
	}
}

void LogInManager::on_addUserButton_clicked()
{
	ui.loginButton->hide();
	ui.addUserButton->hide();
	ui.infoButton->hide();

	ui.addUserConfirmButton->show();

	printQText("Enter new user's login and password");
}

void LogInManager::on_addUserConfirmButton_clicked()
{
	string newUser = (ui.loginLineEdit->text()).toStdString();
	string newPassword = (ui.passwordLineEdit->text()).toStdString();

	if (addUser(newUser, newPassword))
	{
		ui.addUserConfirmButton->hide();

		ui.loginButton->show();
		ui.addUserButton->show();
	}
}

void LogInManager::on_readAccountsButton_clicked()
{
	ui.textEdit->show();
	ui.textEdit->clear();
	readAccounts();
}

void LogInManager::on_addNewAccountButton_clicked()
{
	// hiding unnecessary ui elements
	hideAccountsMenu();

	// showing line edits needed for getting data
	ui.serviceNameEdit->show();
	ui.loginLineEdit->show();
	ui.passwordLineEdit->show();
	ui.addAccountConfirmButton->show();

	ui.serviceNameEdit->setPlaceholderText("Enter the name of the service (e.g. Gmail)");
	ui.loginLineEdit->setPlaceholderText("Enter account's login");
	ui.passwordLineEdit->setPlaceholderText("Enter account's password");
}

void LogInManager::on_addAccountConfirmButton_clicked()
{
	string serviceName = (ui.serviceNameEdit->text()).toStdString();
	string login = (ui.loginLineEdit->text()).toStdString();
	string password = (ui.passwordLineEdit->text().toStdString());

	if (addAccount(serviceName, login, password))
	{
		hideAccountsMenu();
		ui.addAccountConfirmButton->hide();

		// showing ui elements again
		//ui.textEdit->show();
		showAccountsMenu();

		ui.loginLineEdit->setPlaceholderText("login");
		ui.passwordLineEdit->setPlaceholderText("password");
	}
	else
	{
		printQText("This record already exists.");
	}
}

void LogInManager::on_removeAccountButton_clicked()
{
	// hiding unnecessary ui elements
	hideAccountsMenu();

	// showing necessary ui elements
	ui.serviceNameEdit->show();
	ui.removeAccountConfirmButton->show();

	ui.serviceNameEdit->setPlaceholderText("Enter the name of the service you would like to delete");
}

void LogInManager::on_removeAccountConfirmButton_clicked()
{
	string serviceName = (ui.serviceNameEdit->text()).toStdString();

	if (removeAccount(serviceName))
	{
		printQText("Account removed successfully");
	}
	else
	{
		printQText("There is no such record");
	}

	ui.serviceNameEdit->hide();
	ui.removeAccountConfirmButton->hide();
	showAccountsMenu();
	ui.serviceNameEdit->setPlaceholderText("Enter service name here");
}

void LogInManager::on_removeCurrentUserButton_clicked()
{
	hideAccountsMenu();
	
	ui.removeUserButtonBox->show();
	printQText("Would you like to delete this user? Note that accounts for this user will also be deleted.");
}

void LogInManager::onAcceptClicked()
{
	removeUser();
	printQText("Choose action");

	LogInManager::on_goBackButton_clicked();
}

void LogInManager::onRejectClicked()
{
	ui.removeUserButtonBox->hide();

	showAccountsMenu();
}

void LogInManager::on_goBackButton_clicked()
{
	hideAccountsMenu();
	ui.addUserConfirmButton->hide();
	ui.addAccountConfirmButton->hide();
	ui.goBackButton->hide();
	ui.removeAccountConfirmButton->hide();
	ui.textEdit->hide();
	ui.removeUserButtonBox->hide();
	showLogInMenu();
}

#pragma endregion

#pragma region +-----------Functions------------+

bool LogInManager::login()
{
	QString login = ui.loginLineEdit->text();
	QString password = ui.passwordLineEdit->text();

	currentUser = login.toStdString();
	currentPassword = password.toStdString();

	bool isLoggedIn = checkContent(usersFile, currentPassword, currentUser) ? true : false;

	return isLoggedIn;
}

bool LogInManager::checkContent(string fileName, string contentToCheck, string decryptionKey)
{
	fstream file;
	string line;
	bool isContentCorrect = false, isUserCorrect = false;
	long long tempChar = 0;

	file.open(fileName, ios::in);

	// read untill the end of the file
	while (file.peek() != EOF)
	{
		file >> tempChar;

		// 1 is a dilimiter for user logins
		if (tempChar == 1)
		{
			if (currentUser == line)
			{
				isUserCorrect = true;
			}
			else
			{
				isUserCorrect = false;
			}
			line.erase(line.begin(), line.end());
		}
		// 0 is delimiter for the whole user record
		else if (tempChar == 0 && isUserCorrect)
		{
			if (contentToCheck == line)
			{
				isContentCorrect = true;

				file.close();
				return true;
			}
			else
			{
				line.erase();
				isContentCorrect = false;
			}
		}
		else if (tempChar == 0)
		{
			line.erase();
		}
		else
		{
			line += decrypt(tempChar, decryptionKey);
		}
	}
	file.close();

	return isContentCorrect;
}

// checks if user exists within a file.
// Returns true if user was found.
bool LogInManager::checkForUserName(string fileName, string inputParam)
{
	bool valueExists = false;
	ifstream file;
	string line;
	long long tempChar = 0;

	file.open(fileName);
	// read untill the end of the file(or untill suitable value(string) found)
	while (file.peek() != EOF)
	{
		file >> tempChar;

		// 1 is a dilimiter for user logins
		if (tempChar == 1)
		{
			if (inputParam == line)
			{
				valueExists = true;
				file.close();
				return true;
			}
			else
			{
				line.erase(line.begin(), line.end());
			}
		}
		// 0 is delimiter for the whole user record
		else if (tempChar == 0)
		{
			line.erase(line.begin(), line.end());
		}
		else
		{
			line += decrypt(tempChar, inputParam);
		}
	}
	file.close();

	return valueExists;
}

// adds user
bool LogInManager::addUser(string newUser, string newPassword)
{
	if (checkForUserName(usersFile, newUser))
	{
		printQText("This user already exists.");
		return false;
	}
	else
	{
		// putting username and password into appropriate files
		addLine(usersFile, newUser, newUser, '1');
		addLine(usersFile, newPassword, newUser);

		printQText("User added successfully :)");

		return true;
	}
}

void LogInManager::addLine(string fileName, string content, string encryptionKey, char delimiter, char endWith)
{
	fstream file;

	// opening file and going to the end of it
	file.open(fileName, ios::out | ios::app);

	if (file.is_open())
	{
		for (int i = 0; i < content.length(); i++)
		{
			file << encrypt(content[i], encryptionKey) << endWith;
		}
		if (delimiter == ' ')
		{
			file << '\n';
		}
		else
		{
			file << '\n' << delimiter << '\n';
		}
	}
	else
	{
		QMessageBox msgBox;
		msgBox.setText("Error occupied while opening '" + QString::fromStdString(fileName) + "' file.");
		msgBox.exec();
	}

	file.close();
}

// displays all records for current user
void LogInManager::readAccounts()
{
	fstream file;
	string line;
	bool isCurrentUser = false, recordExists = false;
	long long tempChar = 0;

	// opening accounts file in input mode
	file.open(accountsFile, ios::in);

	// read untill the end of the file
	while (file.peek() != EOF)
	{
		// writing characters from file to tempChar variable
		file >> tempChar;

		// 1 is a dilimiter for user logins
		if (tempChar == 1)
		{
			if (currentUser == line)
			{
				isCurrentUser = true;
				recordExists = true;
			}
			else
			{
				isCurrentUser = false;
			}
			line.erase();
		}
		else if (tempChar == 0)
		{
			if (isCurrentUser)
			{
				printText(line);
			}
			line.erase();
		}
		else
		{
			line += decrypt(tempChar, currentUser + currentPassword);
		}
	}

	if (!recordExists)
	{
		printText("There are no records for user '" + currentUser + "'");
	}

	file.close();
}

// adds new account records for the current user
bool LogInManager::addAccount(string newServiceName, string newLogin, string newPassword)
{
	if (!checkContent(accountsFile, newServiceName, currentUser + currentPassword))
	{
		addLine(accountsFile, currentUser, currentUser + currentPassword, '1');
		addLine(accountsFile, "+----------------------------+", currentUser + currentPassword);
		addLine(accountsFile, newServiceName, currentUser + currentPassword);
		addLine(accountsFile, "############################", currentUser + currentPassword);
		addLine(accountsFile, newLogin, currentUser + currentPassword);
		addLine(accountsFile, newPassword, currentUser + currentPassword);
		addLine(accountsFile, "+----------------------------+", currentUser + currentPassword);
		addLine(accountsFile, "", currentUser + currentPassword, ' '); // just adding a new line

		return true;
	}
	else
	{
		return false;
	}
}

// removes account record for the current user
bool LogInManager::removeAccount(string recordToRemove)
{
	fstream mainFile;
	ofstream tempFile;
	string decryptedLine, user, separator;
	long long tempChar = 0;
	bool isUserCorrect = false, isBeginningOfRecord = false,
		 isNeededToSkip = false, isSeparator = false,
		 isRecordFound = false;

	mainFile.open(accountsFile, ios::in);

	// needed to create file
	tempFile.open(temporaryFile, ios::out);

	// read untill the end of the file
	while (mainFile.peek() != EOF)
	{
		mainFile >> tempChar;

		if (tempChar == 1)
		{
			// checking username
			isUserCorrect = (currentUser == decryptedLine);

			isBeginningOfRecord = true;
			isNeededToSkip = false;

			user = decryptedLine;
			decryptedLine.erase();
		}
		else if (tempChar == 0)
		{
			// check if line is "+----------------------------+"
			isSeparator = (decryptedLine.length() == 30 && decryptedLine[0] == decryptedLine[decryptedLine.length() - 1]);
			if (isSeparator)
			{
				separator = decryptedLine;
				for (int i = 1; i < decryptedLine.length() - 2; i++)
				{
					if (decryptedLine[i] != decryptedLine[static_cast <char> (i + 1)])
					{
						isSeparator = false;
						separator.erase();
						break;
					}
				}
			}

			if (decryptedLine == recordToRemove && isUserCorrect)
			{
				isNeededToSkip = isRecordFound = true; // record to remove was found
				decryptedLine.erase();

				continue;
			}

			if ((isSeparator && isBeginningOfRecord) || isNeededToSkip)
			{
				decryptedLine.erase();

				continue;
			}
			else if (decryptedLine != recordToRemove)
			{
				if (isBeginningOfRecord)
				{
					addLine(temporaryFile, user, currentUser + currentPassword, '1');
					user.erase();

					addLine(temporaryFile, separator, currentUser + currentPassword);
					isBeginningOfRecord = false;
				}
				addLine(temporaryFile, decryptedLine, currentUser + currentPassword);
			}
			decryptedLine.erase();
		}
		else
		{
			decryptedLine += decrypt(tempChar, currentUser + currentPassword);
		}
	}
	addLine(temporaryFile, "", currentUser + currentPassword, ' '); // just adding a new line

	mainFile.close();
	tempFile.close();

	remove(accountsFile.c_str());

	if (rename(temporaryFile, accountsFile.c_str())) // rename returns 0 if successfull
	{
		printQText("Error renaming 'temp.datafile' file");
	}

	return isRecordFound;
}

// removes current user and it's accounts file
void LogInManager::removeUser()
{
	fstream recordsFile, userFile;
	ofstream tempFile;

	string decryptedLine;
	long long tempChar = 0;
	bool isUserCorrect = false, isNeededToSkip = false;

#pragma region Removing account records

	recordsFile.open(accountsFile, ios::in);
	tempFile.open(temporaryFile, ios::app);

	// read untill the end of the file
	while (recordsFile.peek() != EOF)
	{
		recordsFile >> tempChar;

		if (tempChar == 1)
		{
			// checking username
			if (currentUser == decryptedLine)
			{
				isUserCorrect = isNeededToSkip = true;
			}
			else
			{
				isUserCorrect = isNeededToSkip = false;

				addLine(temporaryFile, decryptedLine, currentUser + currentPassword, '1');
			}
			decryptedLine.erase();
		}
		else if (tempChar == 0)
		{
			if (!isNeededToSkip)
			{
				addLine(temporaryFile, decryptedLine, currentUser + currentPassword);
			}

			decryptedLine.erase();
		}
		else
		{
			decryptedLine += decrypt(tempChar, currentUser + currentPassword);
		}
	}
	decryptedLine.erase();

	recordsFile.close();
	tempFile.close();

	remove(accountsFile.c_str());

	if (rename(temporaryFile, accountsFile.c_str())) // rename returns 0 if successfull
	{
		printQText("Error renaming temporary file");
	}
#pragma endregion

#pragma region Removing user

	isUserCorrect = isNeededToSkip = false;

	userFile.open(usersFile, ios::in);
	tempFile.open(temporaryFile, ios::app);

	// read untill the end of the file
	while (userFile.peek() != EOF)
	{
		userFile >> tempChar;

		if (tempChar == 1)
		{
			if (currentUser == decryptedLine)
			{
				isUserCorrect = true;
				isNeededToSkip = true;
			}
			else
			{
				isUserCorrect = false;
				isNeededToSkip = false;
				addLine(temporaryFile, decryptedLine, currentUser, '1');
			}
			decryptedLine.erase();
		}
		else if (tempChar == 0)
		{
			if (!isNeededToSkip)
			{
				addLine(temporaryFile, decryptedLine, currentUser);
				decryptedLine.erase();
			}
			else
			{
				decryptedLine.erase();
				continue;
			}

		}
		else
		{
			decryptedLine += decrypt(tempChar, currentUser);

		}
	}
	userFile.close();
	tempFile.close();

	remove(usersFile.c_str());

	if (rename(temporaryFile, usersFile.c_str())) // rename returns 0 if successfull
	{
		printQText("Error renaming file");
	}
#pragma endregion
}

char LogInManager::decrypt(long long input, string key)
{
	// key is "" when the second parameter is not used
	if (key == "")
	{
		return static_cast <char> (input);
	}
	else
	{
		long long result = 0;

		for (int i = 0; i < key.length(); i++)
		{
			result -= static_cast <int> (pow(key[i], 3));
		}

		return static_cast <char> (input + result);
	}
}

long long LogInManager::encrypt(int input, string key)
{
	// key is "" when the second parameter is not used
	if (key == "")
	{
		return input;
	}
	else
	{
		long long result = 0;

		for (int i = 0; i < key.length(); i++)
		{
			result += static_cast <int> (pow(key[i], 3));
		}

		return input + result;
	}
}

#pragma endregion
