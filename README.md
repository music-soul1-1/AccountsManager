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

![screenshot_1](https://user-images.githubusercontent.com/72669184/233647937-b74f9540-de6b-4c2b-8d0d-0c9d7934f44e.png)
![screenshot_2](https://user-images.githubusercontent.com/72669184/233647956-3914e85f-a19f-4249-bd3b-96e3de366a86.png)
![screenshot_3](https://user-images.githubusercontent.com/72669184/233647968-cdb6046c-534b-4839-9053-1ab5cdefba5b.png)


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
* app font changed to Inter
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
