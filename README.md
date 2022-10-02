# UUIDRegistryShellcode
Write and Hide each UUID in the char* array of UUIDS shellcode in a registry key value location as REG_SZ (the location could be different from the other), then retrieve them and assemble them in UUIDs char* array shellcode and Run it  

Generate UUID shellcode from binary shellcode using : https://github.com/boku7/Ninja_UUID_Runner/blob/main/bin2uuids.py  
msfvenom -p windows/x64/exec CMD=calc.exe -f raw -o calc.bin  
python3 bin2uuid.py calc.bin  

https://user-images.githubusercontent.com/110354855/193465856-b6d959fc-f66e-4700-801d-4e3cbaee2833.mp4
