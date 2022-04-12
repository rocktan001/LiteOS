import re
import subprocess
contents = ""

with open('backtrace.txt') as f:
    contents = f.read()

pat = r'lr = (.*?) '
lr_list = re.findall(pat, contents)

for lr in lr_list:
    subprocess.run(["arm-none-eabi-addr2line.exe", "-e", "../out/STM32F767_Fire/Huawei_LiteOS.elf", "-paf", lr])
