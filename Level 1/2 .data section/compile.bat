@ECHO OFF

cl.exe /nologo /Ox /MT /W0 /GS- /DNDEBUG /Tc4byte.cpp /link /OUT:4byte.exe /SUBSYSTEM:CONSOLE /MACHINE:x64

cl.exe /nologo /Ox /MT /W0 /GS- /DNDEBUG /Tccalculator.cpp /link /OUT:calculator.exe /SUBSYSTEM:CONSOLE /MACHINE:x64