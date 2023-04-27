// TODO: add white theme

#include "AccountsManager.h"

AccountsManager::AccountsManager(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	// Set application info
	QCoreApplication::setApplicationName("Account Manager");
	QCoreApplication::setApplicationVersion("0.0.3-beta");
	QCoreApplication::setOrganizationName("music-soul1-1");
	QCoreApplication::setOrganizationDomain("https://github.com/music-soul1-1");

	// initial interface
	addLabel(label, "Enter user login and password");
	showLogInMenu();
}

AccountsManager::~AccountsManager()
{}

AppManager app;

// prints text in label
void AccountsManager::printQText(QString text)
{
	label->setText(text);
}

// prints text in textEdit
void AccountsManager::printText(string text)
{
	textEdit->append(QString::fromStdString(text));
}

#pragma region +---------Ui-modifying functions-----------+

// adds QButton
void AccountsManager::addButton(QPushButton*& button, QString label, int position) // first parameter here is a reference to the pointer
{
	// Create a QPushButton object
	button = new QPushButton(label, ui.frame);

	// Get the existing layout for the widget
	QVBoxLayout* myLayout = qobject_cast<QVBoxLayout*>(layout());

	// Add the button to the existing layout
	if (position == -1)
	{
		// inserting to the bottom of the layout
		myLayout->insertWidget(myLayout->count(), button);
	}
	else
	{
		myLayout->insertWidget(position, button);
	}
}

// adds QDialogButtonBox
void AccountsManager::addDialogButton(QDialogButtonBox*& button, int position) // first parameter here is a reference to the pointer
{
	// Create a QPushButton object
	button = new QDialogButtonBox(QDialogButtonBox::Yes | QDialogButtonBox::No);

	// Get the existing layout for the widget
	QVBoxLayout* myLayout = qobject_cast<QVBoxLayout*>(layout());

	// Add the button to the existing layout
	if (position == -1)
	{
		// inserting to the bottom of the layout
		myLayout->insertWidget(myLayout->count(), button);
	}
	else
	{
		myLayout->insertWidget(position, button);
	}
}

// adds QLabel
void AccountsManager::addLabel(QLabel*& label, QString placeholder, int position)
{
	// Create a QLabel object
	label = new QLabel(placeholder, ui.frame);

	// Get the existing layout for the widget
	QVBoxLayout* myLayout = qobject_cast<QVBoxLayout*>(layout());

	// Add the label to the existing layout
	if (position == -1)
	{
		myLayout->insertWidget(myLayout->count(), label);
	}
	else
	{
		myLayout->insertWidget(position, label);
	}

}

// adds QLineEdit
void AccountsManager::addLineEdit(QLineEdit*& lineEdit, QString placeholder, int position)
{
	// Create a QLineEdit object
	lineEdit = new QLineEdit(ui.frame);
	lineEdit->setPlaceholderText(placeholder);

	// Get the existing layout for the widget
	QVBoxLayout* myLayout = qobject_cast<QVBoxLayout*>(layout());

	// Add the lineEdit to the existing layout
	if (position == -1)
	{
		myLayout->insertWidget(myLayout->count(), lineEdit);
	}
	else
	{
		myLayout->insertWidget(position, lineEdit);
	}
}

// adds QTextEdit
void AccountsManager::addTextEdit(QTextEdit*& textEdit, QString placeholder, int position)
{
	// Create a QTextEdit object
	textEdit = new QTextEdit(placeholder, ui.frame);
	textEdit->setPlaceholderText(placeholder);

	// Get the existing layout for the widget
	QVBoxLayout* myLayout = qobject_cast<QVBoxLayout*>(layout());

	// Add the textEdit to the existing layout
	if (position == -1)
	{
		myLayout->insertWidget(myLayout->count(), textEdit);
	}
	else
	{
		myLayout->insertWidget(position, textEdit);
	}
	textEdit->setReadOnly(true);
}

// shows all elements needed for Login menu. Also connects the buttons
void AccountsManager::showLogInMenu()
{
	addLineEdit(loginLineEdit, "login");
	addLineEdit(passwordLineEdit, "password");

	addButton(loginButton, "Log in");
	addButton(addUserButton, "Add new user");
	addButton(exitButton, "Exit");
	addButton(infoButton, "See app info");

	printQText("Enter user login and password");

	QObject::connect(loginButton, SIGNAL(clicked()), this, SLOT(on_loginButton_clicked()));
	QObject::connect(addUserButton, SIGNAL(clicked()), this, SLOT(on_addUserButton_clicked()));
	QObject::connect(addUserConfirmButton, SIGNAL(clicked()), this, SLOT(on_addUserConfirmButton_clicked()));
	QObject::connect(exitButton, SIGNAL(clicked()), this, SLOT(on_exitButton_clicked()));
	QObject::connect(infoButton, SIGNAL(clicked()), this, SLOT(on_infoButton_clicked()));
}

// deletes and sets equal to nullptr all UI elements from Login menu
void AccountsManager::hideLogInMenu()
{
	if (loginLineEdit) delete loginLineEdit;
	loginLineEdit = nullptr;
	if (passwordLineEdit) delete passwordLineEdit;
	passwordLineEdit = nullptr;
	if (loginButton) delete loginButton;
	loginButton = nullptr;
	if (addUserButton) delete addUserButton;
	addUserButton = nullptr;
	if (exitButton) delete exitButton;
	exitButton = nullptr;
	if (infoButton) delete infoButton;
	infoButton = nullptr;
}

// shows all elements needed for Accounts menu. Also connects the buttons
void AccountsManager::showAccountsMenu()
{
	printQText("Choose action");
	addButton(readAccountsButton, "Read accounts");
	addButton(addAccountButton, "Add new account");
	addButton(removeAccountButton, "Remove account");
	addButton(removeCurrentUserButton, "Remove current user");
	addButton(goToLoginMenuButton, "Go back");

	// connecting buttons to slots
	QObject::connect(readAccountsButton, SIGNAL(clicked()), this, SLOT(on_readAccountsButton_clicked()));
	QObject::connect(addAccountButton, SIGNAL(clicked()), this, SLOT(on_addNewAccountButton_clicked()));
	QObject::connect(removeAccountButton, SIGNAL(clicked()), this, SLOT(on_removeAccountButton_clicked()));
	QObject::connect(removeCurrentUserButton, SIGNAL(clicked()), this, SLOT(on_removeCurrentUserButton_clicked()));
	QObject::connect(goToLoginMenuButton, SIGNAL(clicked()), this, SLOT(on_goToLoginMenuButton_clicked()));
}

// deletes and sets equal to nullptr all UI elements from Accounts menu
void AccountsManager::hideAccountsMenu()
{
	if (serviceNameEdit) delete serviceNameEdit;
	serviceNameEdit = nullptr;
	if (loginLineEdit) delete loginLineEdit;
	loginLineEdit = nullptr;
	if (passwordLineEdit) delete passwordLineEdit;
	passwordLineEdit = nullptr;

	if (textEdit) delete textEdit;
	textEdit = nullptr;

	if (readAccountsButton) delete readAccountsButton;
	readAccountsButton = nullptr;
	if (addAccountButton) delete addAccountButton;
	addAccountButton = nullptr;
	if (addAccountConfirmButton) delete addAccountConfirmButton;
	addAccountConfirmButton = nullptr;
	if (removeAccountButton) delete removeAccountButton;
	removeAccountButton = nullptr;
	if (removeAccountConfirmButton) delete removeAccountConfirmButton;
	removeAccountConfirmButton = nullptr;
	if (removeCurrentUserButton) delete removeCurrentUserButton;
	removeCurrentUserButton = nullptr;
	if (removeUserButtonBox) delete removeUserButtonBox;
	removeUserButtonBox = nullptr;
	if (goToAccountsMenuButton) delete goToAccountsMenuButton;
	goToAccountsMenuButton = nullptr;
	if (goToLoginMenuButton) delete goToLoginMenuButton;
	goToLoginMenuButton = nullptr;
}

#pragma endregion

#pragma region +-------------Event handlers--------------+

#pragma region +--------------Log in menu------------------+

void AccountsManager::on_infoButton_clicked()
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

void AccountsManager::on_exitButton_clicked()
{
	quick_exit(0);
}

void AccountsManager::on_loginButton_clicked()
{
	app.currentUser = (loginLineEdit->text()).toStdString();
	app.currentPassword = (passwordLineEdit->text()).toStdString();

	if (app.login(app.currentUser, app.currentPassword) && app.currentPassword != "" && app.currentPassword != " ")
	{
		app.logInAttempts = 0;

		// hiding all unnecessary ui elements
		hideLogInMenu();

		// showing all necessary ui elements
		showAccountsMenu();

		printQText("Successfully logged in. Choose action:");
	}
	else
	{
		printQText("Username or password isn't correct");
		if (app.logInAttempts <= 2)
		{
			app.logInAttempts++;
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

void AccountsManager::on_addUserButton_clicked()
{
	loginButton->hide();
	addUserButton->hide();
	infoButton->hide();

	addButton(addUserConfirmButton, "Add", 4);
	QObject::connect(addUserConfirmButton, SIGNAL(clicked()), this, SLOT(on_addUserConfirmButton_clicked()));

	printQText("Enter new user's login and password");
}

void AccountsManager::on_addUserConfirmButton_clicked()
{
	string newUser = (loginLineEdit->text()).toStdString();
	string newPassword = (passwordLineEdit->text()).toStdString();

	if (app.addUser(newUser, newPassword))
	{
		delete addUserConfirmButton;
		addUserConfirmButton = nullptr;

		loginButton->show();
		addUserButton->show();
		infoButton->show();


		printQText("User added successfully :)");
	}
	else
	{
		printQText("This user already exists.");
	}
}

#pragma endregion

#pragma region +---------------Accounts menu------------------+

void AccountsManager::on_readAccountsButton_clicked()
{
	if (!textEdit) addTextEdit(textEdit, "", 2);
	textEdit->clear();

	textEdit->setText(QString::fromStdString(app.readAccounts()));
}

void AccountsManager::on_addNewAccountButton_clicked()
{
	// hiding unnecessary ui elements
	hideAccountsMenu();

	// showing line edits needed for getting data
	addLineEdit(serviceNameEdit, "Enter the name of the service (e.g. Gmail)");
	addLineEdit(loginLineEdit, "Enter account's login");
	addLineEdit(passwordLineEdit, "Enter account's password");

	addButton(addAccountConfirmButton, "Add");
	QObject::connect(addAccountConfirmButton, SIGNAL(clicked()), this, SLOT(on_addAccountConfirmButton_clicked()));

	addButton(goToAccountsMenuButton, "Go Back");
	QObject::connect(goToAccountsMenuButton, SIGNAL(clicked()), this, SLOT(on_goToAccountsMenuButton_clicked()));

}

void AccountsManager::on_addAccountConfirmButton_clicked()
{
	string serviceName = (serviceNameEdit->text()).toStdString();
	string login = (loginLineEdit->text()).toStdString();
	string password = (passwordLineEdit->text().toStdString());

	if (app.addAccount(serviceName, login, password))
	{
		hideAccountsMenu();

		// showing ui elements again
		showAccountsMenu();
		printQText("Account added successfully.");
	}
	else
	{
		printQText("This record already exists.");
	}
}

void AccountsManager::on_removeAccountButton_clicked()
{
	// hiding unnecessary ui elements
	hideAccountsMenu();

	// showing necessary ui elements
	addLineEdit(serviceNameEdit, "Enter the name of the service you would like to delete");

	addButton(removeAccountConfirmButton, "Remove this account");
	addButton(goToAccountsMenuButton, "Go Back");
	QObject::connect(removeAccountConfirmButton, SIGNAL(clicked()), this, SLOT(on_removeAccountConfirmButton_clicked()));
	QObject::connect(goToAccountsMenuButton, SIGNAL(clicked()), this, SLOT(on_goToAccountsMenuButton_clicked()));
}

void AccountsManager::on_removeAccountConfirmButton_clicked()
{
	if (app.removeAccount((serviceNameEdit->text()).toStdString()))
	{
		hideAccountsMenu();

		showAccountsMenu();
		printQText("Account removed successfully");
	}
	else
	{
		printQText("There is no such record");
	}

}

void AccountsManager::on_removeCurrentUserButton_clicked()
{
	hideAccountsMenu();

	addDialogButton(removeUserButtonBox);

	QObject::connect(goToAccountsMenuButton, SIGNAL(clicked()), this, SLOT(on_goToAccountsMenuButton_clicked()));
	// connecting accept and reject buttons
	QObject::connect(removeUserButtonBox, SIGNAL(accepted()), this, SLOT(onAcceptClicked()));
	QObject::connect(removeUserButtonBox, SIGNAL(rejected()), this, SLOT(on_goToAccountsMenuButton_clicked()));

	printQText("Would you like to delete this user? Note that accounts for this user will also be deleted.");
}

void AccountsManager::onAcceptClicked()
{
	app.removeUser();
	printQText("Choose action");

	AccountsManager::on_goToLoginMenuButton_clicked();
}

void AccountsManager::on_goToAccountsMenuButton_clicked()
{
	hideAccountsMenu();

	showAccountsMenu();
}

void AccountsManager::on_goToLoginMenuButton_clicked()
{
	hideAccountsMenu();

	showLogInMenu();
}

#pragma endregion

#pragma endregion
