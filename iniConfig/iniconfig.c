#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

#include<ctype.h>

#define KEYVALLEN 64 
static int trim(char * buf)
{
    if(!buf)return 0;
    char *p1,*p2;
    p1=p2=buf;
    while(p2 && *p2!='\0'){
        if(!isspace(*p2) && p1<p2)
            *p1=*p2,p1++;
        else if(!isspace(*p2) && p1==p2)
            p1++;
        p2++;
    }
    *p1='\0';
    return strlen(buf);
}
int GetToken( char *profile, char *AppName, char *KeyName, char *KeyVal)
{
    char appname[20],keyname[20];
    char buf[KEYVALLEN],*c;
    FILE *fp;
    int found=0; /* 1 AppName 2 KeyName */
 
    if( (fp=fopen( profile,"r" ))==NULL ){
        printf( "openfile [%s] error [%s]\n", profile,strerror(errno) );
        return(-1);
    }
    fseek( fp, 0, SEEK_SET );
 
    sprintf( appname,"[%s]", AppName );
    memset( keyname, 0, sizeof(keyname) );
 
    while( !feof(fp) && fgets( buf, KEYVALLEN, fp )!=NULL ){
        if(trim( buf )==0)
            continue;
 
        if( found==0 ){
            if( buf[0]!='[' ) { 
                continue;
            } else if ( strncmp(buf,appname,strlen(appname))==0 ){
                found=1;
                continue;
            }
        } else if( found==1 ){
            if( buf[0]=='#' ){
                continue;
            } else if ( buf[0]=='[' ) {
                break;
            } else {
                if( (c=(char*)strchr(buf,'='))==NULL )
                    continue;
                memset( keyname, 0, sizeof(keyname) );
                sscanf( buf, "%[^=]", keyname );
                if( strcmp(keyname, KeyName)==0 ){
                    sscanf( ++c, "%[^\n]", KeyVal );
                    found=2;
                    break;
                } else {
                    continue;
                }
            }
        }
    }
 
    fclose( fp );
 
    if( found==2 )
        return(0);
    else
        return(-1);
}
int main(void)
{
    char * app="LOG";
    char * keyname="errorlog";
    char keyval[KEYVALLEN] = {'\0'};
    int ret = 0;
 
    ret = GetToken("ddgcsync.conf",app,keyname,keyval);
    if(ret<0)
    {
        printf("no token found \n ");
    }else{
        printf("value = %s\n",keyval);
    }
    return 0;
}