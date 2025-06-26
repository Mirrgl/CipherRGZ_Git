
#!/bin/bash

installDir=$USER/DirCipherRGZ

mkdir -p $installDir

cp CipherRGZ "$installDir/"
cp doubleCipher.so "$installDir/"
cp vernam.so "$installDir/"
cp web.so "$installDir/"

echo "$installDir/CipherRGZ" > "/usr/local/bin/CipherRGZ"
chmod +x "/usr/local/bin/CipherRGZ"

echo "Установка завершена"
