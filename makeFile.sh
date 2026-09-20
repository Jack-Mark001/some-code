#!/bin/bash

month=`date +%m`
day=`date +%d`

name="$month-$day"
echo $month-$day

week=`date +%u`

# week ="六"


echo $week

if [ -d "$name" ]
then 
    echo "文件夹 '$name' 已存在，无法再创建"
elif [ "$week" -eq 6 ]
then
    echo "星期六不创建文件"
elif [ "$week" -eq 7 ]
then
    echo "星期天不创建文件"
else
    mkdir -p "$name"
    echo "成功创建'$name' 文件夹"
fi

echo -n "当前时间为:"

date

if [ "$week" -ne 6 -a "$week" -ne 7 ];
then
echo "正在打开'$name'目录,并且打开'$name'目录的VScode"
cd $name
code .
fi

