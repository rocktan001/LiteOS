# ESP32 教程

## 1.简介

ESP32目录包含esp32单板相关代码及脚本。

## 2.环境搭建

1. esp-idf安装

   使用安装指导请参考：(https://docs.espressif.com/projects/esp-idf/zh_CN/release-v4.1/get-started/index.html)

2. esptool安装

   ```
   python -m pip install esptool 或 python3 -m pip install esptool
   ```

3. 生成bootloader.bin

   ```
   $ cd esp-idf
   $ ./install.sh
   $ ./export.sh
   (注释掉example目录下sdkconfig中的CONFIG_PARTITION_TABLE_MD5)
   $ make bootloader
   ```

4. 生成分区表

   根据官方文档（[分区表 - ESP32 - — ESP-IDF 编程指南 v4.3.1 文档 (espressif.com)](https://docs.espressif.com/projects/esp-idf/zh_CN/stable/esp32/api-guides/partition-tables.html?highlight=esptool py#id3)）进入esp-idf/partition_table目录下，使用`gen_esp32part.py`脚本将csv文件转换为对应分区表，如：

   ```
   $ ./gen_esp32part.py partitions_singleapp.csv partitionn.bin --disable-md5sum
   ```

5. 编译工具链，建议安装8.4.0版本（已验证），下载地址：
   ```
   https://github.com/espressif/crosstool-NG/releases/download/esp-2021r1/xtensa-esp32-elf-gcc8_4_0-esp-2021r1-linux-amd64.tar.gz
   ```
