set cin rnu cursorline
set sw=4 ts=4 mouse=a
syn on
imap kj <ESC>l
map <F9> :!clear && g++ -o a -std=c++20 -g -Wfatal-errors -O2 % && gdb a 
set timeoutlen=150
