#include"repertoryManageStruct.h"
#include"reagentApplyStruct.h"
#include"repertoryStruct.h"
#include"user.h"


//��ʼ��ʵ���ҿ���¼��
Status initManageLabList();

//ʵʱ����ʵ���ҿ���¼��
Status updateManageLabList();


Status addApplyResultToManageLabList();

//�����Լ�����ʱ�����ģ�������ļ�¼��
Status createConsumMnanageItem(int,int);

//ö��ת�ַ���������ʾ��
String getUpdateWayName(int);