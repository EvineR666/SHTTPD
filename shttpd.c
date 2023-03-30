#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>

// 配置文件的结构定义：
struct conf_opts{
	char 	CGIRoot[128];			/*CGI跟路径*/
	char 	DefaultFile[128];		/*默认文件名称*/
	char 	DocumentRoot[128];		/*根文件路径*/
	char 	ConfigFile[128];		/*配置文件路径和名称*/
	int 	ListenPort;				/*侦听端口*/
	int	 	MaxClient;				/*最大客户端数量*/
	int 	TimeOut;				/*超时时间*/
};

// default config：
struct conf_opts conf_para={
/*CGIRoot*/			"/usr/local/var/www/cgi-bin/",
/*DefaultFile*/		"index.html",
/*DocumentRoot*/	"/usr/local/var/www/",
/*ConfigFile*/		"/etc/SHTTPD.conf",
/*ListenPort*/		8080,
/*MaxClient*/		4,	
/*TimeOut*/			3,
};

// option结构体定义：
// struct option {
// const char* name;  		// 选项名
// int         has_arg;  	// 是否需要选项参数
// int*        flag;  		// 指向标志变量的指针，用于设置选项是否出现. 如果选项出现，则将flag指向的变量赋值为val。
// int         val;  		// 选项对应的 short_option 值
// };

// 命令行选项定义：
struct option long_options[] = {
	{"CGIRoot", 		required_argument, 	NULL, 'c'},
	{"DefaultFile", 	required_argument, 	NULL, 'd'},
	{"DocumentRoot", 	required_argument, 	NULL, 'o'},
	{"ConfigFile", 		required_argument, 	NULL, 'f'},
	{"ListenPort", 		required_argument, 	NULL, 'l'},
	{"MaxClient",		required_argument, 	NULL, 'm'},
	{"TimeOut",			required_argument, 	NULL, 't'},
	{"Help",			no_argument, 		NULL, 'h'},
	{0, 0, 0, 0}  // 结束标志
};


int main(int argc, char *argv[])
{
	// parse configfile
	char configpath[] = "shttpd.ini";
	FILE* fp = fopen(configpath, "r");
	if(fp==NULL){
		printf("No config file! Start with default params.");
		
	} else {
		printf("Start with config file: %s ......\n", configpath);
		char line[256];
		while (fgets(line, sizeof(line), fp)) {
			line[strcspn(line, "\n")] = '\0';
			char* name = strtok(line, "=");			
			char* value_str = strtok(NULL, "=");

			if (strcmp(name, "CGIRoot") == 0) {
				strcpy(conf_para.CGIRoot, value_str);
			
			} else if (strcmp(name, "DefaultFile") == 0) {
				strcpy(conf_para.DefaultFile, value_str);
			
			} else if (strcmp(name, "ConfigFile") == 0) {
				strcpy(conf_para.ConfigFile, value_str);
			
			} else if (strcmp(name, "DocumentRoot") == 0) {
				strcpy(conf_para.DocumentRoot, value_str);
			
			} else if (strcmp(name, "ListenPort") == 0) {
				conf_para.ListenPort = atoi(value_str);
			
			} else if (strcmp(name, "MaxClient") == 0) {
				conf_para.MaxClient = atoi(value_str);
			
			} else if (strcmp(name, "TimeOut") == 0) {
				conf_para.TimeOut = atoi(value_str);
			
			}
		}
	}
	fclose(fp);

	// parse cmd input
	printf("Parsing cmd input......\n");
	
	// int getopt_long(int argc, char* const argv[], const char* short_options, const struct option* long_options, int* opt_index);
	// 参数解析：
	// argc：命令行参数个数；
	// argv：命令行参数数组；
	// short_options：短选项字符串；
	// long_options：长选项结构体数组；
	// opt_index：如果不为 NULL，则指向一个变量，用于存储当前解析到的长选项在 long_options 数组中的下标。
	// 如果是需要参数的选项，参数的值会保存在optarg里。

    int help_flag = 0;
	static const char optstring[] = "c:d:f:o:l:m:t:h";

	while (1) {
		int opt = getopt_long(argc, argv, optstring, long_options, NULL);
		// parse finished
        if (opt == -1) break;
        switch (opt) {
            case 'h': {		// Help
				help_flag = 1;
				break;
			}
            case 'c': {		// CGIRoot
				strcpy(conf_para.CGIRoot, optarg);
                break;
            }
            case 'd': {		// DefaultFile
                strcpy(conf_para.DefaultFile, optarg);
                break;
            }
            case 'f': {		// ConfigFile
                strcpy(conf_para.ConfigFile, optarg);
                break;
            }
            case 'o': {		// DocumentRoot
                strcpy(conf_para.DocumentRoot, optarg);
                break;
            }
            case 'l': {		// ListenPort
                conf_para.ListenPort = atoi(optarg);
                break;
            }
            case 'm': {		// MaxClient
                conf_para.MaxClient = atoi(optarg);
                break;
            }
            case 't': {		// TimeOut
                conf_para.TimeOut = atoi(optarg);
                break;
            }
            case '?': return 1;
            default: {
                puts("Error.");
                return 1;
            }
        }
    }
    
    if (help_flag) {
        printf("Usage: %s [-h] [-v] [-f <input_file>] [-o <output_file>]\n", argv[0]);
        printf("Options:\n");
        printf("  -h, --help       	Show help information\n");
        printf("  -c, --CGIRoot    	CGIRoot\n");
        printf("  -d, --DefaultFile     DefaultFile\n");
        printf("  -f, --ConfigFile     	ConfigFile\n");
		printf("  -o, --DocumentRoot   	DocumentRoot\n");
		printf("  -l, --ListenPort     	ListenPort\n");
		printf("  -m, --MaxClient     	MaxClient\n");
		printf("  -t, --TimeOut     	TimeOut\n");
        exit(EXIT_SUCCESS);
    }
    
	printf("Params:\n");
	printf("	---CGIRoot: %s\n", conf_para.CGIRoot);
	printf("	---DefaultFile: %s\n", conf_para.DefaultFile);
	printf("	---ConfigFile: %s\n", conf_para.ConfigFile);
	printf("	---DocumentRoot: %s\n", conf_para.DocumentRoot);
	printf("	---ListenPort: %d\n", conf_para.ListenPort);
	printf("	---MaxClient: %d\n", conf_para.MaxClient);
	printf("	---TimeOut: %d\n", conf_para.TimeOut);
	
	return 0;
}





