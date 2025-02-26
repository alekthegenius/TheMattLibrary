If GMP is installed on MacOS through Homebrew:
clang++ -std=c++11 main.cpp -o app -I /usr/local/include -L /usr/local/lib -lgmp -lgmpxx

Otherwise use:

clang++ -std=c++11 main.cpp -o app -I ./ -L ./ -lgmp -lgmpxx
