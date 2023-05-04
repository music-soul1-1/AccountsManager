#include "AppManager.h"

#pragma region +-----------Functions------------+

bool AppManager::login(string login, string password)
{
	bool isLoggedIn = checkContent(usersFile, password, login) ? true : false;

	return isLoggedIn;
}

bool AppManager::checkContent(string fileName, string contentToCheck, string decryptionKey)
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
bool AppManager::checkForUserName(string fileName, string inputParam)
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
bool AppManager::addUser(string newUser, string newPassword)
{
	if (checkForUserName(usersFile, newUser) || newUser == "" || newUser == " ")
	{
		// user already exists or is not specified
		return false;
	}
	else
	{
		// putting username and password into appropriate files
		addLine(usersFile, newUser, newUser, '1');
		addLine(usersFile, newPassword, newUser);

		return true;
	}
}

void AppManager::addLine(string fileName, string content, string encryptionKey, char delimiter, char endWith)
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
		newMessageBox("Error occupied while opening '" + QString::fromStdString(fileName) + "' file.");
	}

	file.close();
}

// displays all records for current user
string AppManager::readAccounts()
{
	fstream file;
	string line, output;
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
				output += line + '\n';
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
		output += ("There are no records for user '" + currentUser + "'");
	}

	file.close();

	return output;
}

// adds new account records for the current user
bool AppManager::addAccount(string newServiceName, string newLogin, string newPassword)
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
bool AppManager::removeAccount(string recordToRemove)
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
		newMessageBox("Error renaming '" + QString::fromStdString(temporaryFile) + "'.");
	}

	return isRecordFound;
}

// removes current user and it's accounts file
void AppManager::removeUser()
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
		newMessageBox("Error renaming '" + QString::fromStdString(temporaryFile) + "'.");
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
		newMessageBox("Error renaming '" + QString::fromStdString(temporaryFile) + "'.");
	}
#pragma endregion
}

char AppManager::decrypt(long long input, string key)
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

long long AppManager::encrypt(int input, string key)
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

void AppManager::newMessageBox(QString message)
{
	QMessageBox msgBox;
	msgBox.setText(message);

	msgBox.exec();
}

#pragma endregion
