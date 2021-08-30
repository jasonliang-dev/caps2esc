@echo off
taskkill /f /im caps2esc.exe 2> NUL
cl -W4 caps2esc.c /link user32.lib

