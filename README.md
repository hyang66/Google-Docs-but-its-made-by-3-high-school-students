# Google Docs 
but its made by 3 high school students (and is not really google docs)

## collaborators:
Matthew Kendall
Joshua Weiner
Hanna Yang

## description
This is a text editor that allows people to edit not only files on thier own machine, but also files on the machines of others (given that they have the IP adress of the other person).
People can edit the files of other people on the same wifi network as them. However, they cannot edit the same file simultaneously and still stay in sync with one another.

## use
Run the server file on the computer which has the file you wish to edit. (the server file is called ./server_sockets)
Then, run the client file wherever you please. It will prompt you for whether or not you want to edit on someone else's computer. Follow the instructions, and eventually you will be asked what filename you want to edit. 
If you enter the name of a file that does not exist, a file will be created for you. If not, it will open the file that you requested, and you will be able to edit it.
To edit, you can: enter new keys, and hit backspace. You can also move up and down to different lines, but you will be sent to the end of the line. Enter will insert a new empty line under the one you are currently editing.
Pressing capital Q will save and quit the file. 

## required libraries
c standard library, curses
to install curses: sudo apt-get install libncurses5-dev libncursesw5-dev

## bugs
1. hitting enter only works sometimes (and only on macs, it seems like)... (backspace may or may not work on the school computer keyboards)
1. hitting up and down will add extra lines to the end of the file
1. each time you go up or down, you may see a glimpse of the terminal window.
1. hitting upp and down too fast on some computers may cause some strange symbols to show up in the text.
1. going down past the end of the file will cause it to crash...
1. there may be some issues when editing on someone else's computer that will only let you edit (for the first time) the first line of a file...

