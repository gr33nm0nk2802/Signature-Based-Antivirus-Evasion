@ECHO OFF

rc resources.rc
cvtres /MACHINE:x64 /OUT:resources.o resources.res
cl.exe /nologo /Ox /MT /W0 /GS- /DNDEBUG /Tccalculator.cpp /link /OUT:calculator.exe /SUBSYSTEM:CONSOLE /MACHINE:x64 resources.o