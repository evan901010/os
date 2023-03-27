# Document
## Part 1
將程式碼和makefile寫好後make
![image](image/part1-1.png)
要先清空核心日誌緩衝區
```
sudo dmesg -c
```
輸入指令載入核心模組
```
sudo insmod project1_part1.ko
```
輸入指令檢視
```
dmesg
```
顯示目前載入核心模組
```
lsmod
```
![image](image/part1-2.png)
移除核心模組
```
sudo insmod project1_part1.ko
```
輸入指令檢視
```
dmesg
```
![image](image/part1-3.png)

## Part 2
將程式碼和makefile寫好後make
![image](image/part2-1.png)
要先清空核心日誌緩衝區
```
sudo dmesg -c
```
輸入指令載入核心模組
```
sudo insmod project1_part2.ko
```
輸入指令檢視
```
dmesg
```
顯示目前載入核心模組
```
lsmod
```
![image](image/part2-2.png)
移除核心模組
```
sudo insmod project1_part1.ko
```
輸入指令檢視
```
dmesg
```
![image](image/part2-3.png)