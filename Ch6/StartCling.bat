@echo off
set path=%path%;C:\Users\frank\Documents\Codes\CodeRepository\FrankWongCN\bin
title Data Structure: Cling

chcp 65001

:while
cling -std=c++2a -L.. -lFormat -lJansson -Wno-dangling-else
goto :while