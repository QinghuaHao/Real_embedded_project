#include <stdio.h>
#include <string>
#include "tinyxml.h"
#include "parseXmlApi.h"
using namespace std;
const char xml_root_name[] = "xmlconfig";
TiXmlDocument * pXmlManager = NULL;


bool GetValue(TiXmlElement *element, const char * name, std::string &strVal)
{
    bool ret = false;
    TiXmlAttribute *Attribute = NULL;
    for (Attribute = element->FirstAttribute(); Attribute; Attribute
            = Attribute->Next())
    {
        std::string tmp = Attribute->Name();
        if (tmp == name)
        {
            ret = true;
            strVal = Attribute->Value();
        }
    }
    return ret;
}
bool GetChild(TiXmlElement *pParent, TiXmlElement **pChild, const char * name,
        const char * value)
{
    bool ret = false;
    std::string strValue = std::string(value);
    for (*pChild = pParent->FirstChildElement(); *pChild; *pChild
            = (TiXmlElement *) (*pChild)->NextSiblingElement())
    { //target>>
        std::string tmp;
        ret = GetValue(*pChild, name, tmp);
        if (ret)
        {
            if (tmp == strValue)
            {
                printf("Find Service:%s config\n", value);
                ret = true;
                break;
            }
            else
            {
                ret = false;
                continue;
            }

        }
        else
        {
            printf("Can't service_name config\n");
            continue;
        }
    }
    return ret;
}
TiXmlDocument * load_xml(const char *pData, char flag)
{
    TiXmlDocument *pDoc;
    printf("++++%s+++",pData);
    if (flag == FROM_FILE)
    {
        pDoc = new TiXmlDocument(pData);
        bool loadOkay = pDoc->LoadFile();
        if (loadOkay == false)
        {
            char errStr[256];
            sprintf(errStr, "File:%s is not right xml file\n", pData);

            //REPORT(REPORT_ERROR,errStr);
        }
    }
    else
    {
        pDoc = new TiXmlDocument();
        pDoc->Parse(pData, NULL);
    }

    return pDoc;
}
int add_xml(TiXmlDocument * pDoc, TiXmlDocument * pTarget,
        const char * firstChildStr)
{
    TiXmlNode* firstChild = 0;
    TiXmlNode* newFirstChild;
    TiXmlNode* rootNode;
    if ((pDoc == NULL) || (pTarget == NULL))
        return -1;
    newFirstChild = pTarget->FirstChild(firstChildStr);
    if (newFirstChild == NULL)
    {
        TiXmlElement firstChildElement(firstChildStr);
        pTarget->InsertEndChild((const TiXmlNode &) firstChildElement);//if no init node add
        newFirstChild = pTarget->FirstChild(firstChildStr);
        //REPORT(//REPORT_INFO,"create new\n");
    }
    rootNode = pDoc->FirstChild(xml_root_name);
    if (rootNode == NULL)
    {
        TiXmlElement rootElement(xml_root_name);
        pDoc->InsertEndChild((const TiXmlNode &) rootElement);//if no init node add
        rootNode = pDoc->FirstChild(xml_root_name);
    }
    firstChild = rootNode->FirstChild(firstChildStr);
    if (firstChild == NULL)
    {
        firstChild = rootNode->InsertEndChild(
                (const TiXmlNode &) *newFirstChild);//if no init node add
        //REPORT(//REPORT_INFO,"insert\n");

    }
    else
    {
        rootNode->ReplaceChild((TiXmlNode *) firstChild,
                (const TiXmlNode &) *newFirstChild);//if no FirstPersonTarget add directory
        //REPORT(//REPORT_INFO,"replace\n");
    }
    return 0;
}
int save_xml(TiXmlDocument * pDoc, const char * filename)
{
	//printf("----------------filename = %s\n",filename);
    bool bRet = pDoc->SaveFile(filename);
    if (bRet == true)
    {
        //REPORT(//REPORT_INFO,"Save file :%s success\n",filename);
    }
    else
    {
    	printf("save faild -----------------\n");
        char err_string[100];
        //REPORT(//REPORT_ERROR,"Save file111 :%s failed\n",filename);
        sprintf(err_string, "Save file :%s failed", filename);

        return -1;
    }
    return 0;
}
char * GetData(TiXmlDocument *pDoc)
{
    char tmpFileName[] = "/tmp/HiIOManager.xml";
    pDoc->SaveFile(tmpFileName);

    FILE* file = fopen(tmpFileName, "r");
    long length = 0;
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);
    if (length <= 0)
        return NULL;
    char* buf = new char[length + 1];
    buf[0] = 0;
    if (fread(buf, length, 1, file) == 0)
    {
        delete[] buf;
        return NULL;
    }
    return buf;
}

char * GetXmlData(const char* tmpFileName)
{

	FILE* file = fopen(tmpFileName, "r");
	if(file == NULL)
	{
		printf("//REPORT_ERROR : open xml failed!\n");
		perror("");
		return NULL;
	}
	long length = 0;
	fseek(file, 0, SEEK_END);
	length = ftell(file);
//	printf(">>>>>>>>---------length=%d\n",length);
	fseek(file, 0, SEEK_SET);
	if (length < 0)
	{
		return NULL;
	}

	char* buf = new char[length + 1];
	buf[0] = 0;
	if (fread(buf, 1, length,file) == 0)
	{
		printf("//REPORT_ERROR : read xml failed!\n");
		delete[] buf;
		return NULL;
	}
	return buf;
}
