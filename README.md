<h1 style="font-size: 100px;">Eternity Pushback Great Planes Repository</h1>

### This reposoitory contains code for team 42824A Eternity's Great Planes Robot, below are instructions to get this code onto your computer:

## **Project Setup Guide**

This guide walks you through getting this code on your local machine.

### **Requirements:**

[PROS CLI + VS Code Extension](https://pros.cs.purdue.edu/v5/getting-started/index.html)

[Git](https://github.com/git-guides/install-git)

## 1. Clone the Repository

### Navigate to your desired folder (e.g., Desktop)
  1. Click on a folder
  2. Click on the 3 dots near the top of your screen
  3. Click on **"Copy Path"**

![Copy Path](https://static1.howtogeekimages.com/wordpress/wp-content/uploads/2024/01/3-copy-path-file-explorer-toolbar-option.jpg)

Then, go to your terminal (ex. Git CMD, VSC Terminal, etc.) and type:

cd ***-insert your copied path here-***

### Clone the repo
Enter the following commands into your terminal:

git clone https://github.com/iagrwl/pushbackGreatPlanes.git
cd pushbackGreatPlanes

## 2. Open in VS Code

  1. Open VS Code.
  2. Go to File > Open Folder.
  3. Select the folder you just cloned.

### Note: Next two steps are optional, they help things run more smoothly

## 3. (OPTIONAL) Rebuild IntelliSense Index
  1. Make sure you’ve opened the entire project folder in VS Code (File > Open Folder, not just individual files).
  2. Open the Command Palette (Ctrl+Shift+P).
  3. Type in PROS: Rebuild IntelliSense Index.
  4. If you see PROS: Rebuild IntelliSense Index, select it and wait for it to finish.
  5. If you ***don’t see*** that option:
     - Make sure the PROS VS Code extension is installed.
     - Alternatively, close and reopen VS Code.
  6. You can also run this from the terminal:
     - pros conduct intellisense

Restart VS Code once you've completed these steps.

## 4. (OPTIONAL) Clean the Project
Type this command in your PROS terminal (within VSC):
pros make clean

This removes any old compiled files and ensures a clean build.

# Done!

You're now ready to run and test this code locally and on your robot.

# Still need help?
Watch this [slightly passive agressive video](https://www.youtube.com/watch?v=mJ-qvsxPHpY&t=870s&ab_channel=NickWhite).

This will also teach you how to push your changes onto this repo!


