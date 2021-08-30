@echo off
taskkill /f /im caps2esc.exe 2> NUL
cl -W4 caps2esc.c /O2 /Oi /Oy /link user32.lib
