import subprocess


with open('./gen/STM32F767_Fire.objdump', "w") as outfile:
    subprocess.run(["arm-none-eabi-objdump.exe", "-dS", "../out/STM32F767_Fire/Huawei_LiteOS.elf"], stdout=outfile)

with open('./gen/STM32F767_Fire.readelf', "w") as outfile:
    subprocess.run(["arm-none-eabi-readelf.exe", "-a", "../out/STM32F767_Fire/Huawei_LiteOS.elf"], stdout=outfile)
