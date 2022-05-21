#include <string.h>
#include <stdlib.h>
int main()
{
	int i;
	int j;
	char t[44][800] = {"TMPDIR=/var/folders/zz/zyxvpxvq6csfxvn_n000ccsr00336f/T/","SHELL=/bin/zsh","HOME=/Users/mfagri","SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.8yq3Ir4A0F/Listeners","Apple_PubSub_Socket_Render=/private/tmp/com.apple.launchd.ffd4dJVX5Z/Render",
	"LOGNAME=mfagri","PATH=/Users/mfagri/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Users/mfagri/.brew/bin:/Users/mfagri/goinfre/devtools/Android/sdk/tools/bin:/Users/mfagri/goinfre/devtools/Android/sdk/emulator:/Users/mfagri/goinfre/devtools/flutter/bin:/Users/mfagri/goinfre/devtools/gradle/bin:/Applications/Visual Studio Code.app/Contents/Resources/app/bin:/Users/mfagri/goinfre/devtools/jdk/Contents/Home/bin:/Users/mfagri/goinfre/devtools/Android/sdk/tools/bin:/Users/mfagri/goinfre/devtools/Android/sdk/emulator:/Users/mfagri/goinfre/devtools/flutter/bin:/Users/mfagri/goinfre/devtools/gradle/bin:/Applications/Visual Studio Code.app/Contents/Resources/app/bin:/Users/mfagri/goinfre/devtools/jdk/Contents/Home/bin",
	"XPC_SERVICE_NAME=0","COMMAND_MODE=unix2003","USER=mfagri","SECURITYSESSIONID=186a8","XPC_FLAGS=0x0","__CF_USER_TEXT_ENCODING=0x18CCE:0x0:0x0","ORIGINAL_XDG_CURRENT_DESKTOP=undefined","SHLVL=1","PWD=/Users/mfagri/Desktop/minishellnew","OLDPWD=/Users/mfagri/Desktop/minishellnew/tests","DEV_TOOLS=/Users/mfagri/goinfre/devtools","APPS=/Users/mfagri/goinfre/apps","ANDROID_SDK_ROOT=/Users/mfagri/goinfre/devtools/Android/sdk","GRADLE_USER_HOME=/Users/mfagri/goinfre/devtools/gradle","GRADLE_OPTS=-Dgradle.user.home=/Users/mfagri/goinfre/devtools/gradle","JAVA_17_HOME=/Users/mfagri/goinfre/devtools/jdk/Contents/Home","JAVA_HOME=/Users/mfagri/goinfre/devtools/jdk/Contents/Home","ZSH=/Users/mfagri/.oh-my-zsh","PAGER=less","LESS=-R","LSCOLORS=Gxfxcxdxbxegedabagacad","P9K_SSH=0","HOMEBREW_CACHE=/tmp/mfagri/Homebrew/Caches","HOMEBREW_TEMP=/tmp/mfagri/Homebrew/Temp","TERM_PROGRAM=vscode","TERM_PROGRAM_VERSION=1.67.0","LANG=en_US.UTF-8","COLORTERM=truecolor","VSCODE_GIT_IPC_HANDLE=/var/folders/zz/zyxvpxvq6csfxvn_n000ccsr00336f/T/vscode-git-cb219adbea.sock","VSCODE_GIT_ASKPASS_NODE=/Applications/Visual Studio Code.app/Contents/MacOS/Electron","VSCODE_GIT_ASKPASS_EXTRA_ARGS=--ms-enable-electron-run-as-node","VSCODE_GIT_ASKPASS_MAIN=/Applications/Visual Studio Code.app/Contents/Resources/app/extensions/git/dist/askpass-main.js","GIT_ASKPASS=/Applications/Visual Studio Code.app/Contents/Resources/app/extensions/git/dist/askpass.sh","TERM=xterm-256color","P9K_TTY=old","_P9K_TTY=/dev/ttys001","_=/usr/bin/env"};
	char tmp[800];
	i = 0;
	while(i < 44)
	{
		j = 0;
		while(j < 44 - i - 1)
		{
			if((strcmp(t[j],t[j + 1])) > 0)
			{
       			strcpy(tmp, t[j]);
       			strcpy(t[j], t[j+1]);
       			strcpy(t[j+1], tmp);
			}
			j++;
		}
		i++;
	}
	for(int k=0; k < 44; k++)
    	printf("$%s$\n", t[k]);
}

//"SHLVL=1","PWD=/Users/mfagri/Desktop/minishellnew","OLDPWD=/Users/mfagri/Desktop/minishellnew/tests","DEV_TOOLS=/Users/mfagri/goinfre/devtools","APPS=/Users/mfagri/goinfre/apps","ANDROID_SDK_ROOT=/Users/mfagri/goinfre/devtools/Android/sdk","GRADLE_USER_HOME=/Users/mfagri/goinfre/devtools/gradle","GRADLE_OPTS=-Dgradle.user.home=/Users/mfagri/goinfre/devtools/gradle","JAVA_17_HOME=/Users/mfagri/goinfre/devtools/jdk/Contents/Home","JAVA_HOME=/Users/mfagri/goinfre/devtools/jdk/Contents/Home","ZSH=/Users/mfagri/.oh-my-zsh","PAGER=less","LESS=-R","LSCOLORS=Gxfxcxdxbxegedabagacad","P9K_SSH=0","HOMEBREW_CACHE=/tmp/mfagri/Homebrew/Caches","HOMEBREW_TEMP=/tmp/mfagri/Homebrew/Temp","TERM_PROGRAM=vscode","TERM_PROGRAM_VERSION=1.67.0","LANG=en_US.UTF-8","COLORTERM=truecolor","VSCODE_GIT_IPC_HANDLE=/var/folders/zz/zyxvpxvq6csfxvn_n000ccsr00336f/T/vscode-git-cb219adbea.sock","VSCODE_GIT_ASKPASS_NODE=/Applications/Visual Studio Code.app/Contents/MacOS/Electron","VSCODE_GIT_ASKPASS_EXTRA_ARGS=--ms-enable-electron-run-as-node","VSCODE_GIT_ASKPASS_MAIN=/Applications/Visual Studio Code.app/Contents/Resources/app/extensions/git/dist/askpass-main.js","GIT_ASKPASS=/Applications/Visual Studio Code.app/Contents/Resources/app/extensions/git/dist/askpass.sh","TERM=xterm-256color","P9K_TTY=old","_P9K_TTY=/dev/ttys001","_=/usr/bin/env"