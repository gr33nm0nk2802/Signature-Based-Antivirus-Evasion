@ECHO OFF

cl.exe /nologo /Ox /MT /W0 /GS- /DNDEBUG /Tccalculator.cpp /link /OUT:calculator.exe /SUBSYSTEM:CONSOLE /MACHINE:x64