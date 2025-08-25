#!/bin/bash


echo "[Desktop Entry]
Name=TerminalURL 
Exec=$HOME/bin/open_app.sh %u
Type=Application
NoDisplay=true
Categories=System;
MimeType=x-scheme-handler/app;
" > appurl.desktop

