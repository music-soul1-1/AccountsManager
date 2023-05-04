# AccountsManager

#### This C++ app is based on [ConsoleAccountManager](https://github.com/music-soul1-1/ConsoleAccountManager). Now it has graphic UI (using [Qt v.6.4.2](https://www.qt.io/)).
It allows you to store logins and passwords for different services.

Data files are stored in the app's folder.

### [See changelog](https://github.com/music-soul1-1/AccountsManager#changelog)

## Features:
* account manager
* GUI with multi-theme support
* multi-user app
* account records are only available for authorised users who created the records
* data files are encrypted
* names of the services are also stored
* data files are created automatically

## Usage:
1. Download the [latest release](https://github.com/music-soul1-1/AccountsManager/releases).
2. Unzip the folder.
3. Run "AccountsManager.exe".
4. Enjoy :)

## Screenshots:

#### Dark themes:
![dark themes](https://user-images.githubusercontent.com/72669184/236248623-105a95f0-2cfe-4a1b-9823-f5cf23520bfc.jpg)

#### Light themes:
![light themes](https://user-images.githubusercontent.com/72669184/236248714-9375a6c8-ea74-4f8b-bbac-feff073323a3.jpg)

#### When logged in:
![screenshot when logged in](https://user-images.githubusercontent.com/72669184/236249133-4c60b588-4778-4073-b5e9-3478fdeffd56.png)


## Plans for the app:
* fix an issue with scroll bar isn't showing(in TextEdit)
* fix an issue with QInputDialog always loading theme whether user chose to or not
* change QWidget to QMainWindow
* rename AccountsManager class to AppUI
* improve encryption/decryption security
* find and fix bugs
* improve code readability


## Changelog:

### v.0.0.4-beta:
* added theming support. Now the app has 4 themes. User's theme choice is saved to config.ini
* app font changed to [Inter](https://fonts.google.com/specimen/Inter?query=inter)
* stylesheets are now stored separately from .ui file. That means the users can create their own themes. 
To use them, copy the .qss file to ./styles/themes/ folder.

### v.0.0.3-beta:
* all "back-end" functions were moved to separate class ("AppManager")
* LogInManager class was renamed to AccountsManager
* UI was rewritten. Now .ui file doesn't have almost any elements. Creating and destroying ui elements has been moved to AccountsManager class.
* UI is now responsive to the window size changes.


### v.0.0.2-beta:
* app style changed
* app icon added
* added log in attempts limit

### v.0.0.1-beta:
* first version
* GUI added to [ConsoleAccountManager](https://github.com/music-soul1-1/ConsoleAccountManager)


Made by @music-soul1-1

2023
