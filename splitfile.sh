##################################################
# File Name     : splitfile.sh
# Author      : biolxy
# E-mail      : biolxy@aliyun.com
# Created Time: 2018年09月15日 星期六 00时26分08秒
##################################################
#!/bin/bash
split_file=$1
output_file_num=$2
split_file_prefix=$3

num=`cat ${split_file} | wc -l`
split_num1=$((num / output_file_num ))
split_num2=$((split_num1 + 1))
split -l ${split_num2} ${split_file} ${split_file_prefix} 

