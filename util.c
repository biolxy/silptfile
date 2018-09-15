/******************************************************************
	> File Name     : util.c
	> Author      : biolxy
	> Mail        : biolxy@aliyun.com 
	> Created Time: 2018年09月15日 星期六 16时30分33秒
******************************************************************/
#include<stdio.h>
nclude <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/sockios.h>
#include <linux/ethtool.h>
#include <linux/if_ether.h>
#include <stddef.h>		/* offsetof */
#include <fcntl.h>
#include <ctype.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>
#include <netinet/in.h>
#include <net/if.h>
#include <net/route.h>
#include <net/if_arp.h>
#include <sys/socket.h>
#include <sys/syscall.h>
 
 
#include <sys/select.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <net/if_arp.h>
#include <sys/ioctl.h>
#include <sys/inotify.h>
#include <pthread.h>
 
 
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>
#include <signal.h>
#include <stdarg.h>
#include <time.h>
#include <semaphore.h>
#include <termios.h>
 
#include <arpa/inet.h>
 
#include <linux/rtc.h>
#include <linux/sockios.h>
#include <linux/ethtool.h>
#include <linux/if_ether.h>
//#include <linux/inotify.h>
 
 
#include <netinet/ip_icmp.h>
#include <netinet/in.h>
#include <net/if.h>
#include <net/route.h>
#include <net/if_arp.h>
#include <netinet/in.h>
 
#include "toolbox.h"
#include "common.h"
#include "global_config.h"
 
/*****************************************************************************
 函 数 名  : COMMON_GetStorageInfo
 功能描述  : 获取容量
 输入参数  : char* MountPoint
             int* Capacity
             int type: 1 for totol Capacity, 2 for used Capacity , 3 for free Capacity
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2017年7月17日
    作    者   : cw
    修改内容   : 增加注释
*****************************************************************************/
int COMMON_GetStorageInfo(char* MountPoint,int* Capacity,int type)
{
	int					ret;
	struct statfs 		statFS;
	unsigned int		totalBytes;
	unsigned int		freeBytes;
	unsigned int		usedBytes;
 
	if(MountPoint == 0 || Capacity == 0){
		return -1;
	}
	ret = statfs(MountPoint, &statFS);
	if (ret == -1){
		printf("statfs failed for path->[%s]\n", MountPoint);
		return -1;
	}
	totalBytes = (unsigned int)statFS.f_blocks * (unsigned int)(statFS.f_frsize/1024);
	freeBytes = (unsigned int)statFS.f_bfree * (unsigned int)(statFS.f_frsize/1024);
	usedBytes = (unsigned int)(totalBytes - freeBytes);
	switch( type )
	{
	case 1:
		*Capacity = totalBytes/1024;
		break;
	case 2:
		*Capacity = usedBytes/1024;
		break;
	case 3:
		*Capacity = freeBytes/1024;
		break;
	default:
		return -1;
	}
	return 0;
}
 
/*****************************************************************************
 函 数 名  : StrisInt
 功能描述  : 
 输入参数  : const char* str
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2017年7月17日
    作    者   : cw
    修改内容   : 增加注释
*****************************************************************************/
int StrisInt(const char* str)
{
	int value;
	char intstr[20];
	value = atoi(str);
	sprintf(intstr, "%d", value);
	return strcmp(str, intstr);
}
 
/*****************************************************************************
 函 数 名  : CreateProcess
 功能描述  : 创建一个进程
 输入参数  : const char* cmd
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2017年7月17日
    作    者   : cw
    修改内容   : 增加注释
*****************************************************************************/
int CreateProcess(const char* cmd)
{
	FILE* fp;
	fp = popen(cmd,"r");
	pclose(fp);
    return 0;
}
 
/*****************************************************************************
 函 数 名  : is_file_exist
 功能描述  : 判断文件是否存在
 输入参数  : const char *file_path
 输出参数  : 无
 返 回 值  : int
             0: 存在
             -1:不存在
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2017年7月17日
    作    者   : cw
    修改内容   : 增加注释
*****************************************************************************/
int is_file_exist(const char *file_path)
{
	if(file_path ==NULL)
		return -1 ;
	if(access(file_path,F_OK) == 0)
		return 0 ;
	return -1;
}
 
/*****************************************************************************
 函 数 名  : is_dir_exist
 功能描述  : 判断目录是否存在
 输入参数  : const char *dir_path
 输出参数  : 无
 返 回 值  : int
             0: 存在
             -1:不存在
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2017年7月17日
    作    者   : cw
    修改内容   : 增加注释
*****************************************************************************/
int is_dir_exist(const char *dir_path)
{
	if(dir_path ==NULL)
		return -1 ;
	if(opendir(dir_path) == NULL)
		return -1 ;
	return 0;
}
 
/*****************************************************************************
 函 数 名  : getfilesize
 功能描述  : 传入文件名，获取文件大小
 输入参数  : FILE *pFile
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2017年7月17日
    作    者   : cw
    修改内容   : 增加注释
*****************************************************************************/
int getfilesize(FILE *pFile)
{          
	// check FILE*.          
	if( pFile == NULL){                  
		return -1;          
	}            
	// get file size.          
	int fd = fileno((FILE *)pFile);          
	if(fd == -1){                  
		return -1;          
	}          
	struct stat fileStat;          
	if( -1 == fstat(fd, &fileStat)){                  
		return -1;          
	}            
	// deal returns.          
	return fileStat.st_size;  
}  
 
/*****************************************************************************
 函 数 名  : GetFileSize
 功能描述  : 传入文件路径，获取文件大小
 输入参数  : const char* path
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2017年7月17日
    作    者   : cw
    修改内容   : 增加注释
*****************************************************************************/
int GetFileSize(const char* path)
{
	int 			fd;
	int				ret = -1;
	struct stat 	fileStat; 
	fd = open(path,O_RDONLY);
	if(fd == -1){
		return -1;
	}
	ret = fstat(fd, &fileStat);
	if(ret == -1){
		close(fd);
		return -1;
	}
	ret = fileStat.st_size;
	close(fd);
	return ret;
}
 
 
#define LOG_BUF_MAX 512
 
 /*****************************************************************************
 函 数 名  : gettid
 功能描述  : 获取进程号
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2017年7月17日
    作    者   : cw
    修改内容   : 增加注释
*****************************************************************************/
pid_t gettid()
{
	return syscall(SYS_gettid);
}
 
 /*****************************************************************************
 函 数 名  : ipc_pthread_create
 功能描述  : 创建线程
 输入参数  : pthread_t *thread_id
             ipc_thread_main *func
             void *arg
             int stack_size
             int priority)
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2017年7月17日
    作    者   : cw
    修改内容   : 增加注释
*****************************************************************************/
int ipc_pthread_create(pthread_t *thread_id, ipc_thread_main *func, void *arg, int stack_size, int priority)
{
    
    int ret;
    pthread_attr_t SchedAttr;
    struct sched_param	SchedParam;
 
#ifdef _POSIX_THREAD_PRIORITY_SCHEDULING
    //ipc_print("pthread priority(SCHED_RR)=(min=%d,max=%d)\n", sched_get_priority_min(SCHED_RR), sched_get_priority_max(SCHED_RR));
    //ipc_print("pthread priority(SCHED_FIFO)=(min=%d,max=%d)\n", sched_get_priority_min(SCHED_FIFO), sched_get_priority_max(SCHED_FIFO));
#endif
    /** init sched param attribute  **/
    pthread_attr_init(&SchedAttr);		
        
    if(priority != -1)
    {
        ret = pthread_attr_setinheritsched(&SchedAttr, PTHREAD_EXPLICIT_SCHED);
        if (ret != 0)
             ipc_print("pthread_attr_setschedpolicy, %s\n", strerror(ret));       
        ret = pthread_attr_setschedpolicy(&SchedAttr, SCHED_RR);
        if (ret != 0)
            ipc_print("pthread_attr_setschedpolicy, %s\n", strerror(ret));
        SchedParam.sched_priority = priority;	
        ret = pthread_attr_setschedparam(&SchedAttr, &SchedParam);
        if (ret != 0)
            ipc_print("pthread_attr_setschedparam, %s\n", strerror(ret));
    }
    
    ret = pthread_attr_setstacksize(&SchedAttr, stack_size);
    if (ret != 0)
        ipc_print("pthread_attr_setstacksize, %s\n", strerror(ret));
    ret = pthread_create(thread_id, &SchedAttr, func, arg);
	if(ret != 0)
		ipc_print("pthread_create [ %x ] failed, %s\n", (unsigned int)*func, strerror(ret));
 
    pthread_attr_destroy(&SchedAttr);
 
    return ret;
    
}
 
 
/*****************************************************************************
 函 数 名  : ipc_print
 功能描述  : 自定义打印
 输入参数  : char * fmt, 可变参数
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2017年7月17日
    作    者   : cw
    修改内容   : 增加注释
*****************************************************************************/
T_VOID ipc_print(char* fmt, ...)
{
	T_CHR buf[LOG_BUF_MAX];
	va_list ap;
 
	memset(buf, 0, sizeof(buf));
	va_start(ap, fmt);
 
	vsnprintf(buf, LOG_BUF_MAX, fmt, ap);
	if(strlen(buf) >= LOG_BUF_MAX)
	{
		printf("*****************buf overflow**********************\n");
	}
 
	buf[LOG_BUF_MAX - 1] = 0;
  	va_end(ap);
 
	syslog(LOG_DEBUG,"%s", buf);
	printf("%s", buf);
											    
}
 
 
/*****************************************************************************
 函 数 名  : do_syscmd
 功能描述  : 执行系统命令
 输入参数  : char * cmd, 要执行的命令
             char *result， 执行结果
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2017年7月17日
    作    者   : cw
    修改内容   : 增加注释
*****************************************************************************/
int do_syscmd(char *cmd, char *result)
{
	char buf[4096];	
	FILE *filp;
	
	filp = popen(cmd, "r");
	if (NULL == filp){
		ipc_print("[%s:%d] popen %s, cmd:%s!\n", 
			__func__, __LINE__, strerror(errno), cmd);
		return -2;
	}
 
	//fgets(buf, sizeof(buf)-1, filp);
	memset(buf, '\0', sizeof(buf));
	fread(buf, sizeof(char), sizeof(buf)-1, filp);
	
	sprintf(result, "%s", buf);
	
	pclose(filp);
	return strlen(result);	
}
 
/*****************************************************************************
 函 数 名  : IPC_GetSysTime
 功能描述  : 获取系统时间
 输入参数  : IPC_TIME *pSysTime
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2017年7月17日
    作    者   : cw
    修改内容   : 增加注释
*****************************************************************************/
int   IPC_GetSysTime(IPC_TIME *pSysTime)
{
 
	struct tm *gmt = 0;
	time_t timep   = 0;
 
	if (time(&timep) == -1)
	{
		printf( "IPC_GetSysTime time err\n");			
		
	}
	timep = timep+ipc_conf.TimeZone*3600;//获取时间后 对应处理时区的时间
	if (0 == (gmt = localtime(&timep)))
	{
		printf( "IPC_GetSysTime gmtime err\n");
	}
 
	pSysTime->year	=  (gmt->tm_year % 100) & 0x1f;   //since 1900
	pSysTime->month	=  (gmt->tm_mon + 1) % 13;		  //0	 ~ 11,
	pSysTime->day	=  (gmt->tm_mday) % 32;
	pSysTime->hour	=  (gmt->tm_hour ) % 24;  
	pSysTime->minute =  (gmt->tm_min)  % 60;
	pSysTime->second =  (gmt->tm_sec)  % 60;
	pSysTime->week	=  (gmt->tm_wday) % 7;			  //0	 ~ 6  0(sunday)   
	return 0;
}
 
/*****************************************************************************
 函 数 名  : IPC_GetSysTime_offset
 功能描述  : 获取系统时间(带时区)
 输入参数  : IPC_TIME *pSysTime
             int offset_second
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2017年7月17日
    作    者   : cw
    修改内容   : 增加注释
*****************************************************************************/
int   IPC_GetSysTime_offset(IPC_TIME *pSysTime ,int offset_second)
{
 
	struct tm *gmt = 0;
	time_t timep   = 0;
 
	if (time(&timep) == -1)
	{
		printf( "IPC_GetSysTime time err\n");			
		
	}
	timep = timep+ipc_conf.TimeZone*3600 + offset_second;//获取时间后 对应处理时区的时间
	if (0 == (gmt = localtime(&timep)))
	{
		printf( "IPC_GetSysTime gmtime err\n");
	}
 
	pSysTime->year	=  (gmt->tm_year % 100) & 0x1f;   //since 1900
	pSysTime->month	=  (gmt->tm_mon + 1) % 13;		  //0	 ~ 11,
	pSysTime->day	=  (gmt->tm_mday) % 32;
	pSysTime->hour	=  (gmt->tm_hour ) % 24;  
	pSysTime->minute =  (gmt->tm_min)  % 60;
	pSysTime->second =  (gmt->tm_sec)  % 60;
	pSysTime->week	=  (gmt->tm_wday) % 7;			  //0	 ~ 6  0(sunday)   
	return 0;
}
 
/*****************************************************************************
 函 数 名  : COMMON_GetTime
 功能描述  : 获取系统时间
 输入参数  : 年月日
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2017年7月17日
    作    者   : cw
    修改内容   : 增加注释
*****************************************************************************/
int COMMON_GetTime(int *pYear,int *pMonth, int *pDay ,int *pWday,int *pHour , int *pMinute , int *pSecond)
{
	IPC_TIME SysTime;
	IPC_GetSysTime(&SysTime);
	*pYear = SysTime.year ;
	*pMonth = SysTime.month ;
	*pDay =  SysTime.day ;
	*pWday = SysTime.week ;
	*pHour = SysTime.hour ;
	*pMinute = SysTime.minute ;
	*pSecond = SysTime.second ;
	return 0;
}
 
/*****************************************************************************
 函 数 名  : getTimeStamp_usec
 功能描述  : 获取系统时间微秒
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2017年7月17日
    作    者   : cw
    修改内容   : 增加注释
*****************************************************************************/
unsigned int getTimeStamp_usec()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec*1000 + tv.tv_usec/1000);
}
 
/*****************************************************************************
 函 数 名  : getTimeStamp_sec
 功能描述  : 获取系统时间秒
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2017年7月17日
    作    者   : cw
    修改内容   : 增加注释
*****************************************************************************/
unsigned int getTimeStamp_sec()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec;
}
 
/*****************************************************************************
 函 数 名  : get_UTC_time
 功能描述  : 获取UTC时间
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2017年7月17日
    作    者   : cw
    修改内容   : 增加注释
*****************************************************************************/
int get_UTC_time(struct tm *tmx, unsigned int time)
{
    char buf[128];
    char str_mon[4],str_mday[3],str_year[5],str_hour[3],str_min[3],str_sec[3],str_day[3];
 
    int i;
    time_t timep;
 
    char str_mon_array[][4]=
    {
        "Jan",
        "Feb",
        "Mar",
        "Apr",
        "May",
        "Jun",
        "Jul",
        "Aug",
        "Sep",
        "Oct",
        "Nov",
        "Dec"
    };
    tmx->tm_mon=1;
 
    //time(&timep);
    timep = time;
    strcpy(buf,asctime(gmtime(&timep)));
 
    //printf("buf=%s\n",buf);//Sun Jan  4 02:16:10 1970
 
    sscanf(buf,"%3s %3s  %2s %2s:%2s:%2s %4s",(char *)&str_day,(char *)&str_mon,(char *)&str_mday,(char *)&str_hour,(char *)&str_min,(char *)&str_sec,(char *)&str_year);
 
    for(i=0; i<12; i++)
    {
        if(!strcmp(str_mon_array[i],str_mon))
        {
            tmx->tm_mon=i;
            break;
        }
    }
 
    tmx->tm_mday=atoi(str_mday);
    tmx->tm_year=atoi(str_year);
    tmx->tm_hour=atoi(str_hour);
    tmx->tm_min=atoi(str_min);
    tmx->tm_sec=atoi(str_sec);
 
    printf("TIME:[%04d/%02d/%02d-%02d:%02d:%02d]\n", tmx->tm_year, tmx->tm_mon+1, tmx->tm_mday,
           tmx->tm_hour, tmx->tm_min, tmx->tm_sec);
 
    return 0;
}
 
/*****************************************************************************
 函 数 名  : set_timezone
 功能描述  : 设置时区
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2017年7月17日
    作    者   : cw
    修改内容   : 增加注释
*****************************************************************************/
int set_timezone()
{
	int ret = 0;
	if( putenv("TZ=TAIST-8TAIDT")==-1)
	{
	   printf("Unable to set TZ/n");
	   return -1;
	}
	tzset();
 
	return ret;
}
 
#define MAX 1024
/*****************************************************************************
 函 数 名  : get_file_count
 功能描述  : 获取目录下的文件数
 输入参数  : char *root
             char *cmpstr
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2017年7月17日
    作    者   : cw
    修改内容   : 增加注释
*****************************************************************************/
int get_file_count(char *root,char *cmpstr)
{
 DIR *dir;
 struct dirent * ptr;
 int total = 0;
 char path[MAX];
 dir = opendir(root); /* 打开目录*/
 if(dir == NULL)
 {
  perror("fail to open dir");
  exit(1);
 }
 
 errno = 0;
 printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
 while((ptr = readdir(dir)) != NULL)
 {
  //顺序读取每一个目录项；
  //跳过“..”和“.”两个目录
  if(strcmp(ptr->d_name,".") == 0 || strcmp(ptr->d_name,"..") == 0)
  {
   continue;
  }
  //printf("%s%s/n",root,ptr->d_name);
  //如果是目录，则递归调用 get_file_count函数
  
  if(ptr->d_type == DT_DIR)
  {
   sprintf(path,"%s%s/",root,ptr->d_name);
   //printf("%s/n",path);
   total += get_file_count(path,cmpstr);
  }
  
  if(ptr->d_type == DT_REG)
  {
   
   
   if(strstr(ptr->d_name,cmpstr))
   {
   		printf(">>>>>>>>>>>>>>>%s%s\n",root,ptr->d_name);
	    total++;
   }
  }
 }
  printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
 if(errno != 0)
 {
  printf("fail to read dir");  //失败则输出提示信息
  exit(1);
 }
 closedir(dir);
 return total;
}
 
#define MAXBSTZE 1024  
/*****************************************************************************
 函 数 名  : file_wc
 功能描述  : 获取文件行数
 输入参数  : const char *filename
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2017年7月17日
    作    者   : cw
    修改内容   : 增加注释
*****************************************************************************/
int file_wc(const char *filename)
{
        int fd;
        register int linect = 0;
        char buf[MAXBSTZE];
        int len;
        char *p = NULL;
        if(filename) {
                if((fd = open(filename, O_RDONLY)) < 0) {
                        fprintf(stderr, "open %s\n",strerror(errno));
                        return -1;
                }
 
                while(1) {
                        if((len = read(fd,buf,MAXBSTZE)) == -1) {
                            return -1;
                        }
                        if(len == 0){
                            break;
                        }
                        for( p = buf; len--; ){
                            if( *p == '\n' ){
                               ++linect;
                            }
                            ++p;
                        }
                }
        }
 
        return linect;
 
}
 
/*****************************************************************************
 函 数 名  : GetPidByName
 功能描述  : 获取指定名称的PID的进程号
 输入参数  : char* name
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2017年7月17日
    作    者   : cw
    修改内容   : 增加注释
*****************************************************************************/
int GetPidByName(char* name)
{
	char cmd[50]={0};
	char str[20]={0};
	sprintf(cmd,"pgrep \"%s\"",name);
	FILE* fp = popen(cmd,"r");
	fread(str,1,19,fp);
	//printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&  %s\n",str);
	pclose(fp);
	return atoi(str);
}
 
 
///////////////////////////////////////////////////////////////////////////////
 
#define N_CLR            0x01
#define M_CLR            0x02
#define N_SET            0x04
#define M_SET            0x08
#define N_ARG            0x10
#define M_ARG            0x20
#define M_MASK           (M_CLR | M_SET | M_ARG)
#define N_MASK           (N_CLR | N_SET | N_ARG)
#define SET_MASK         (N_SET | M_SET)
#define CLR_MASK         (N_CLR | M_CLR)
#define SET_CLR_MASK     (SET_MASK | CLR_MASK)
#define ARG_MASK         (M_ARG | N_ARG)
#define A_CAST_TYPE      0x03
#define A_MAP_TYPE       0x0C
#define A_ARG_REQ        0x10	/* Set if an arg is required. */
#define A_NETMASK        0x20	/* Set if netmask (check for multiple sets). */
#define A_SET_AFTER      0x40	/* Set a flag at the end. */
#define A_COLON_CHK      0x80	/* Is this needed?  See below. */
#define A_CAST_CHAR_PTR  0x01
#define A_CAST_RESOLVE   0x01
#define A_CAST_HOST_COPY 0x02
#define A_CAST_HOST_COPY_IN_ETHER    A_CAST_HOST_COPY
#define A_CAST_HOST_COPY_RESOLVE     (A_CAST_HOST_COPY | A_CAST_RESOLVE)
#define A_MAP_ULONG      0x04	/* memstart */
#define A_MAP_USHORT     0x08	/* io_addr */
#define A_MAP_UCHAR      0x0C	/* irq */
#define ARG_METRIC       (A_ARG_REQ /*| A_CAST_INT*/)
#define ARG_MTU          (A_ARG_REQ /*| A_CAST_INT*/)
#define ARG_TXQUEUELEN   (A_ARG_REQ /*| A_CAST_INT*/)
#define ARG_MEM_START    (A_ARG_REQ | A_MAP_ULONG)
#define ARG_IO_ADDR      (A_ARG_REQ | A_MAP_ULONG)
#define ARG_IRQ          (A_ARG_REQ | A_MAP_UCHAR)
#define ARG_DSTADDR      (A_ARG_REQ | A_CAST_HOST_COPY_RESOLVE)
#define ARG_NETMASK      (A_ARG_REQ | A_CAST_HOST_COPY_RESOLVE | A_NETMASK)
#define ARG_BROADCAST    (A_ARG_REQ | A_CAST_HOST_COPY_RESOLVE | A_SET_AFTER)
#define ARG_HW           (A_ARG_REQ | A_CAST_HOST_COPY_IN_ETHER)
#define ARG_POINTOPOINT  (A_CAST_HOST_COPY_RESOLVE | A_SET_AFTER)
#define ARG_KEEPALIVE    (A_ARG_REQ | A_CAST_CHAR_PTR)
#define ARG_OUTFILL      (A_ARG_REQ | A_CAST_CHAR_PTR)
#define ARG_HOSTNAME     (A_CAST_HOST_COPY_RESOLVE | A_SET_AFTER | A_COLON_CHK)
 
struct options 
{
	const char *name;
	const unsigned char  flags;
	const unsigned char  arg_flags;
	const unsigned short selector;
};
 
static const struct options OptArray[] = {
	{"metric",       N_ARG,         ARG_METRIC,      0},
    {"mtu",          N_ARG,         ARG_MTU,         0},
	{"txqueuelen",   N_ARG,         ARG_TXQUEUELEN,  0},
	{"dstaddr",      N_ARG,         ARG_DSTADDR,     0},
	{"netmask",      N_ARG,         ARG_NETMASK,     0},
	{"broadcast",    N_ARG | M_CLR, ARG_BROADCAST,   IFF_BROADCAST},
	{"hw",           N_ARG,         ARG_HW,          0},
	{"pointopoint",  N_ARG | M_CLR, ARG_POINTOPOINT, IFF_POINTOPOINT},
	{"mem_start",    N_ARG,         ARG_MEM_START,   0},
	{"io_addr",      N_ARG,         ARG_IO_ADDR,     0},
	{"irq",          N_ARG,         ARG_IRQ,         0},
	{"arp",          N_CLR | M_SET, 0,               IFF_NOARP},
	{"trailers",     N_CLR | M_SET, 0,               IFF_NOTRAILERS},
	{"promisc",      N_SET | M_CLR, 0,               IFF_PROMISC},
	{"multicast",    N_SET | M_CLR, 0,               IFF_MULTICAST},
	{"allmulti",     N_SET | M_CLR, 0,               IFF_ALLMULTI},
	{"dynamic",      N_SET | M_CLR, 0,               IFF_DYNAMIC},
	{"up",           N_SET        , 0,               (IFF_UP | IFF_RUNNING)},
	{"down",         N_CLR        , 0,               IFF_UP},
	{ NULL,          0,             ARG_HOSTNAME,    (IFF_UP | IFF_RUNNING)}
};
 
 
/*****************************************************************************
 函 数 名  : get_netlink_status
 功能描述  : 获取网卡状态
 输入参数  : const char * const if_name
 输出参数  : 无
 返 回 值  : int
             -1 -- error , details can check errno
             1 -- interface link up
             0 -- interface link down.int get_netlink_status(const char * const if_name)
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2017年7月17日
    作    者   : cw
    修改内容   : 增加注释
*****************************************************************************/
int get_netlink_status(const char * const if_name)
{
    int skfd;
    struct ifreq ifr;
    struct ethtool_value edata;
 
    edata.cmd = ETHTOOL_GLINK;
    edata.data = 0;
 
    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, if_name, sizeof(ifr.ifr_name) - 1);
    ifr.ifr_data = (char *) &edata;
 
    if (( skfd = socket( AF_INET, SOCK_DGRAM, 0 )) < 0)
        return -1;
 
    if(ioctl( skfd, SIOCETHTOOL, &ifr ) == -1)
    {
        close(skfd);
        return -1;
    }
 
    close(skfd);
	//HH_SYSLOG(HH_LOG_DEBUG,"%s LINK %s\n",if_name,edata.data>0?"up":"down");
    return edata.data;
}
 
/*****************************************************************************
 函 数 名  : get_ip_addr
 功能描述  : 获取网卡IP地址
 输入参数  : char *name
             char *net_ip
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2017年7月17日
    作    者   : cw
    修改内容   : 增加注释
*****************************************************************************/
int get_ip_addr(char *name,char *net_ip)
{
	struct ifreq ifr;
	int ret = 0;
	int fd;
	
	strcpy(ifr.ifr_name, name);
	ifr.ifr_addr.sa_family = AF_INET;
	
	fd = socket(PF_INET, SOCK_DGRAM, 0);
	if(fd < 0)
		ret = -1;
		
	if (ioctl(fd, SIOCGIFADDR, &ifr) < 0) 
	{
		ret = -1;
	}
	else
		strcpy(net_ip,inet_ntoa(((struct sockaddr_in *)&(ifr.ifr_addr))->sin_addr));
 
	close(fd);
 
	return	ret;
}
 
/*****************************************************************************
 函 数 名  : get_gateway_addr
 功能描述  : 获取默认网关
 输入参数  : char *name
             char *gateway_addr
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2017年7月17日
    作    者   : cw
    修改内容   : 增加注释
*****************************************************************************/
int get_gateway_addr(char *name,char *gateway_addr)
{
	char buff[256];
	char ifname[32] = {0};
	int  nl = 0 ;
	struct in_addr gw;
	int flgs, ref, use, metric;
	unsigned  long d,g,m;
 
	FILE	*fp;
	
 
	if((fp = fopen("/proc/net/route", "r")) == NULL)
		return -1;	
		
	nl = 0 ;
	while( fgets(buff, sizeof(buff), fp) != NULL ) 
	{
		if(nl) 
		{
			int ifl = 0;
			if(sscanf(buff, "%s%lx%lx%X%d%d%d%lx",
				   ifname,&d, &g, &flgs, &ref, &use, &metric, &m)!=8) 
			{
				//continue;
				fclose(fp);
				return	-2;
			}
 
			ifl = 0;        /* parse flags */
			if(flgs&RTF_UP && (strcmp(name,ifname)== 0)) 
			{			
				gw.s_addr   = g;
					
				if(d==0)
				{
					strcpy(gateway_addr,inet_ntoa(gw));
					fclose(fp);
					return 0;
				}				
			}
 
		}
		nl++;
	}	
	
	if(fp)
	{
		fclose(fp);
		fp = NULL;
	}
	
	return	-1;
}
 
 
/*****************************************************************************
 函 数 名  : get_mask_addr
 功能描述  : 得到指定名字的子网掩码
 输入参数  : char *name
             char *net_mask
 输出参数  : 
 返 回 值  : int
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2017年7月17日
    作    者   : cw
    修改内容   : 增加注释
*****************************************************************************/
int get_mask_addr(char *name,char *net_mask)
{
	struct ifreq ifr;
	int ret = 0;
	int fd; 
	
	strcpy(ifr.ifr_name, name);
	ifr.ifr_addr.sa_family = AF_INET;
	
	fd = socket(PF_INET, SOCK_DGRAM, 0);
	if(fd < 0)
		ret = -1;
		
	if (ioctl(fd, SIOCGIFNETMASK, &ifr) < 0) 
	{
		ret = -1;
	}
	
	strcpy(net_mask,inet_ntoa(((struct sockaddr_in *)&(ifr.ifr_addr))->sin_addr));
 
	close(fd);
 
	return	ret;
}
 
/*****************************************************************************
 函 数 名  : get_mac_addr
 功能描述  : 获得网卡物理地址
 输入参数  : const char *pIfName
             unsigned char *pMacBuf
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2017年7月17日
    作    者   : cw
    修改内容   : 增加注释
*****************************************************************************/
int get_mac_addr(const char *pIfName,unsigned char *pMacBuf)
{
	struct ifreq ifreq;
	int nSockFd;
	int cRet=0;
 
	if ( pIfName == NULL )
	{
		printf ( "get_mac_addr: input the invalid argument!\n" );
		cRet= -1;
	}
	if((nSockFd=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		printf ( "get_mac_addr: creat socket error\n" );
		cRet= -1;
	}
	strcpy(ifreq.ifr_name,pIfName);
	if(ioctl(nSockFd,SIOCGIFHWADDR,&ifreq)<0)
	{
		printf( "get_mac_addr: ioctl: %s\n",strerror(errno));
		cRet= -1;
	}
 
	sprintf(pMacBuf,"%02x:%02x:%02x:%02x:%02x:%02x",(unsigned char)ifreq.ifr_hwaddr.sa_data[0],
		(unsigned char)ifreq.ifr_hwaddr.sa_data[1],
		(unsigned char)ifreq.ifr_hwaddr.sa_data[2],
		(unsigned char)ifreq.ifr_hwaddr.sa_data[3],
		(unsigned char)ifreq.ifr_hwaddr.sa_data[4],
		(unsigned char)ifreq.ifr_hwaddr.sa_data[5]);
 
 
	close(nSockFd);
	return cRet;
}
 
 
char *safe_strncpy(char *dst, const char *src, size_t size)
{
	dst[size-1] = '\0';
	return strncpy(dst, src, size-1);
}
 
/*****************************************************************************
 函 数 名  : ifconfig_up_down
 功能描述  : 加载或卸载指定名字的网络
 输入参数  : char *name
             char *action
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2017年7月17日
    作    者   : cw
    修改内容   : 增加注释
*****************************************************************************/
int ifconfig_up_down(char *name, char *action) // name :  eth0 eth1 lo and so on
{											   // action: down up
	const struct options *op;
	int 	sockfd;
	int 	selector;
	struct 	ifreq ifr;
	unsigned char mask;
 
	/* Create a channel to the NET kernel. */
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		return -1;
	}
 
	/* get interface name */
	safe_strncpy(ifr.ifr_name, name, IFNAMSIZ);
	mask = N_MASK;
 
	for (op = OptArray ; op->name ; op++)
	{
			if (strcmp(action,op->name) == 0)
			{
				if ((mask &= op->flags))
				{
				    goto IFCONFIG_UP_DOWN_FOUND_ARG;
				}
			}
	}
	close(sockfd);
	return -4;
 
IFCONFIG_UP_DOWN_FOUND_ARG:
 
	if (ioctl(sockfd, SIOCGIFFLAGS, &ifr) < 0)
	{
		close(sockfd);
		return -2;
	}
	else
	{
		selector = op->selector;
		if (mask & SET_MASK)
		{
			ifr.ifr_flags |= selector;
		}
		else
		{
			ifr.ifr_flags &= ~selector;
		}
		if (ioctl(sockfd, SIOCSIFFLAGS, &ifr) < 0)
		{
			close(sockfd);
			return -3;
		}
	}
 
	close(sockfd);
	return  0;
}
 
/*****************************************************************************
 函 数 名  : del_default_eth0_route
 功能描述  : 删除网卡默认路由
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2017年7月17日
    作    者   : cw
    修改内容   : 增加注释
*****************************************************************************/
void del_default_eth0_route()
{	
	int ret = 0;
	int nTryCount = 0;
	int errsv = errno;
 
	for (nTryCount = 0; nTryCount < 10; nTryCount++)
	{
		ret = system("route del default eth0");
		errsv = errno;
		if (ret > 0)
		{
			printf("---route del default eth0 Success !\n");
			return;
		}
		else if(ret == 0)
		{
			printf( "---route del default eth0 done ! but not subprocess created !\n");
		}
		else
		{
			printf( "---route del default eth0 faile! err(%d)nTryCount == %d\n", errsv, nTryCount);
		}
	}
}
 
/*****************************************************************************
 函 数 名  : del_default_wifi_route
 功能描述  : 删除网卡默认路由
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2017年7月17日
    作    者   : cw
    修改内容   : 增加注释
*****************************************************************************/
void del_default_wifi_route()
{	
	system("route del default wlan0");
	system("route del default wlan0");
		
}
 
/*****************************************************************************
 函 数 名  : Common_PUB_Write_DNS_Param_To_Files
 功能描述  : 添加指定DNS到文件
 输入参数  : unsigned int dnsaddr
             unsigned int dnsaddr2
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2017年7月17日
    作    者   : cw
    修改内容   : 增加注释
*****************************************************************************/
void Common_PUB_Write_DNS_Param_To_Files(unsigned int dnsaddr, unsigned int dnsaddr2)
{
	int  ret;
	char str[128] = {0};
	char ss[128]  = {0};
	FILE *dst_fd;
	unsigned int nIP = dnsaddr;
	unsigned int mIP = 0;
 
	unsigned int nIP2 = dnsaddr2;
	unsigned int mIP2 = 0;
 
	int q[4];
 
	if (0 == dnsaddr) //202.96.134.133
		dnsaddr = 0xCA608685;
 
	if (0 == dnsaddr2) //202.106.0.20
  		dnsaddr2 = 0xCA6A0014;	
		
	if ((dst_fd = fopen("/etc/jffs2/resolv.conf", "r+b")) != NULL)
	{
		fgets(str, 128, dst_fd);
		memset(str, 0, 128);
		fgets(str, 128, dst_fd);
		if(strlen(str) > 20)
		{
			if((ret = sscanf(str, "%s %d.%d.%d.%d", ss, &(q[0]), &(q[1]), &(q[2]), &(q[3])) )== 5)
			{
				mIP = (q[0] << 24) | (q[1] << 16) | (q[2] << 8) | (q[3] << 0);
			}
		}
 
		memset(str, 0, 128);
		fgets(str, 128, dst_fd);
		if(strlen(str) > 20)
		{
			if((ret = sscanf(str, "%s %d.%d.%d.%d", ss, &(q[0]), &(q[1]), &(q[2]), &(q[3])) )== 5)
			{
				mIP2 = (q[0] << 24) | (q[1] << 16) | (q[2] << 8) | (q[3] << 0);
			}
		}
		
		printf("mIP = %x mIP2 = %x\n", mIP, mIP2);
 
		fclose(dst_fd);
	}
	
	if(nIP == mIP && nIP2 == mIP2)
		return;
	
	dst_fd = fopen("/etc/jffs2/resolv.conf", "w+b");
	
	if(dst_fd ==NULL)
	{
		printf("open dst file(%s):  error!\n", "/etc/jffs2/resolv.conf");
		return;
	}
	
	memset(str, 0, 128);
	sprintf(str, "search localdomain\n");
	ret =  fputs(str, dst_fd);
	
	memset(str, 0, 128);
	sprintf(str, "nameserver %d.%d.%d.%d\n",  (nIP & 0xff000000) >> 24,   (nIP & 0xff0000) >> 16,  (nIP & 0xff00) >> 8,  (nIP & 0xff) >> 0);
	ret =  fputs(str, dst_fd);
 
	memset(str, 0, 128);
	sprintf(str, "nameserver %d.%d.%d.%d\n",  (nIP2 & 0xff000000) >> 24,  (nIP2 & 0xff0000) >> 16, (nIP2 & 0xff00) >> 8, (nIP2 & 0xff) >> 0);
	ret =  fputs(str, dst_fd);
	
	fclose(dst_fd);
	
}
unsigned long HH_Ip_N2A(unsigned long ip, char *ourIp, int len)
{
	if(!ourIp)
		return -1;
	
	memset(ourIp, 0, len);
	ip = ntohl(ip);
	inet_ntop(AF_INET, &ip, ourIp, len);	
	return 0;
}
 
unsigned long  HH_Ip_A2N(char *szIp)
{
	int nIp = 0;
	if(!szIp)
		return 0xFFFFFFFF;
	inet_pton(AF_INET, szIp,&nIp);
	return ntohl(nIp);
}
 

int main()
{
	/* 备注： */
	
	return 0;
}
