@echo off
@echo TEST %2
@echo TEST %2 >> result.txt
copy prom.%2.in prom.in > nul
CowsDance2.exe
Timer %1 2000 65536 >> result.txt
fc prom.%2.out prom.out >> result.txt
if exist prom.in del prom.in
if exist prom.out del prom.out