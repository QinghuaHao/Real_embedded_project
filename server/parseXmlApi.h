#ifndef _H_XML_API
#define _H_XML_API
#include "tinyxml.h"
#include <iostream>
#include <fstream>
#include <string>
# include <vector>
#define FROM_FILE 0
#define FROM_DATA 1
#define ROUTER_XML 0
#define INIT_XML 1

extern TiXmlDocument * pXmlManager ;
TiXmlDocument * load_xml(const char *pData,char flag);
int save_xml(TiXmlDocument * pDoc,const char * filename);
int add_xml(TiXmlDocument * pDoc, TiXmlDocument * pTarget, const char * firstChildStr);
bool GetValue(TiXmlElement *element, const char * name, std::string &strVal);
bool GetChild(TiXmlElement *pParent, TiXmlElement **pChild, const char * name,
        const char * value);
char * GetData(TiXmlDocument *pDoc);
char * GetXmlData(const char* tmpFileName);
int pasre_router_xml(TiXmlDocument *pDoc);
#endif
