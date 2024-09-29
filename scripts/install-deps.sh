#/bin/bash

# check if script was runed with sudo 
if [ $(id -u) -ne 0 ]; then
    echo "please, use sudo with this script"
    exit
fi

apt update  
apt install g++ cmake clang-format clang-tidy-14 # you can add new programms here