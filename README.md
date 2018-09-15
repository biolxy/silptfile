# splitfile 介绍

### 功能

- 指定输入文件
	+ 必选参数
	+ 判断文件存在
- 指定输出文件夹
	+ 可选参数
	+ 默认为当前文件夹(获得当前路径)
	+ 判断指定路径存在
- 指定拆分单位行数
	+ 按行拆分
	+ 可选参数
	+ 默认为4(split fastq file)
- 指定输出文件个数
	+ 最多为文件行数
- 指定输出文件前缀
- 缺少必须参数是输出help信息
- `splitfile.sh` 是一个用`wc -l` `splie` 串联起来的shell脚本，基本实现了上述功能
	+ 缺点：不能实现`指定拆分单位行数` 的功能，即不能实现downsample的功能
	可能会导致拆分后的文件数据质量不一致




### 参考
- [https://blog.csdn.net/qq_29214249/article/details/75307512](https://blog.csdn.net/qq_29214249/article/details/75307512)

### 联系

- biolxy@aliyun.com
