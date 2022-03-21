#ifndef INCLUDES_H
#define INCLUDES_H

#include <stdio.h>
#include <string.h>
#include <QString>
#include <QDateTime>
#include <QMutex>
#include <sys/timeb.h>
#include "unistd.h"
#include <QLabel>
#include <QPushButton>
//#include <sys/types.h>
//#include <sys/stat.h>
#include "messageboxdialog.h"


class QFormLayout;
class QLineEdit;
class QMutex;
class QComboBox;
class CMonShareData;
class QGroupBox;
class QMessageBox;
class QBoxLayout;
class CAlarmDataFile;
class QAbstractItemView;

#include <QMessageBox>


#define CONFIG_FILE_NAME        "/Life100UWH.cfg"
#define CONFIG_FILE_NAME_BAK    "/Life100UWH_BAK.cfg"
#define DEV_TYPE_CFG_NAME       "/DevTypePrm.cfg"
#define PWD_CONFIG_FILE         "/PwdCfgInfo.cfg"
#define ALM_FILE_NAME           "/AlmData.dat"
#define ALM_UPD_POS_NAME        "/AlmUpdPos.dat"
#define MCU_UPD_FILE_PATH       "/DshUpdFiles/"


//���������־�ļ�
#define SAVE_FILE_INFO_NAME     "/SaveMonInfo.dat"
#define SAVE_MON_DATA_NAME      "/SaveMonData.dat"
#define OPER_LOG_INFO_NAME      "/OperLogInfoData.dat"

//��λ���ϴ���Ϣ�����ļ�
#define SLAVE_UP_INFO_NAME      "/SlaveUpInfo.txt"


#define MAX_SRN_WIDTH   1280
#define MAX_SRN_HEIGHT  800

#define SAVE_BUT_NAME       "����"
#define INPUT_BUT_NAME      "����"
#define CANCEL_BUT_NAME     "ȡ��"
#define CONFIRM_BUT_NAME    "ȷ��"


#define FONT_NAME  "wenquanyi"//"simsun"//"arial"//"wenquanyi"

//������־����
#define SAVE_OPER_LOG_NUM    1000

//
#define SAVE_MON_LOG_NUM     1000
//��ע�洢���ݸ���
#define SAVE_POUR_DAT_NUM   1000

//��ע��Ԥ��עÿ���ļ��洢�������
#define MAX_DATA_REC_COUNT  10000


//�ؼ��߶�
#define MINI_HEIGHT 30



#define INVALID_DEV_ID     0xFF //���豸ID���
#define INVALID_DEV_CMD_ID 0xFF //���豸����ID

//�û�Ѫ�ý����������
#define USR_BP_CMD_STRT    0x00
#define USR_BP_CMD_STOP    0x01
#define USR_BP_CMD_NONE    0xFF

//���Ѫ����
#define MAX_BP_GRP_COUNT  2
//�����豸ID����
#define MAX_COMPORT_SIZE    30

//���ٵ��ڲ������
#define SET_VAL_DLG_W       1280//343 
#define SET_VAL_DLG_H       760//151 

//ת�������ֵ
#define SET_SPEED_LIMIT_V   6000
#define SET_SPEED_LIMIT_MIN_V   10//1000
#define SET_SPEED_LIMIT     6000
#define SET_SPEED_LIMIT_MIN 10//1000

#define SET_STEP_1          1
#define SET_SPEED_DEF       2000 //Ĭ��ֵ
#define CHK_SPEED_STP       10000 //���ֹͣ��עת��

#define SET_PRESS_LIMIT_V   140
#define SET_PRESS_LIMIT_MIN_V   0

#define SET_PRESS_LIMIT     800
#define SET_PRESS_LIMIT_MIN 0

#define SET_STEP_5          5
#define SET_PRESS_STP       900 //���ֹͣ��עѹ��
#define SET_AUTO_PRESS      300 //����ѹ���ص�Ĭ��ֵ
#define SET_STEP_100          100


#define SET_TMP_LIMIT     390
#define SET_TMP_LIMIT_MIN     350

//���ð�ȫֵ
#define SET_POUR_SPEED    2000
#define SET_POUR_PRESS    300
#define SET_POUR_VAL_TMT  10

#define SET_POUR_SPEED_V    2000
#define SET_POUR_PRESS_V    50
//��ȫ������ֵ
#define POUR_PRESS_A    1000
#define POUR_SPEED_MAX_A    10000
#define POUR_SPEED_MIN_A    1000
#define POUR_TMP_A    390
#define POUR_FLO_U_A        800

#define POUR_PRESS_V    200
#define POUR_FLO_U_V    2500

#define WAT_UP_TMP         410

//�澯������ֵ
#define SET_ALM_PRES_U_A    850
#define SET_ALM_TMP_U_A     380
#define SET_ALM_FLO_U_A     300
#define SET_ALM_FLO_L_A     0

#define SET_ALM_PRES_U_V    160
#define SET_ALM_TMP_U_V     380
#define SET_ALM_FLO_U_V     1500
#define SET_ALM_FLO_L_V     0

#define SET_ALM_TMP_U_WAT   395

//�쳣�澯��ֵ
#define PRESS_ERR_VAL_A     2000 //����ѹ���쳣200.0
#define FLOW_ERR_VAL_A      3000 //���������쳣3000||-3000
#define RMP_ERR_VAL_A       1000 //����ѪҺ�¶�> 100���<0�� 100.0

#define PRESS_ERR_VAL_V     2000 //����ѹ���쳣200.0
#define FLOW_ERR_VAL_V      3000 //���������쳣3000||-3000
#define RMP_ERR_VAL_V       1000 //����ѪҺ�¶�> 100���<0�� 100.0

#define TMP_ERR_VAL_W       1000 //ˮԡ�¶�> 100���<0�� 100.0
#define PRESS_ERR_VAL_W     2000 //ˮԡѹ��


//ͨ���豸ID
#define MAIN_DEV_BAS_ID     0x01 //�����豸ID
#define APUM_DEV_BAS_ID     0x10 //�������豸ID
#define VPUM_DEV_BAS_ID     0x18 //�������豸ID
#define WAT_DEV_BAS_ID      0x20 //ˮԡ�豸ID
#define BAT_DEV_BAS_ID      0x02 //����豸ID


//�豸����
#define DEV_ON  1
#define DEV_OFF 0

//Ԥ��ע����ע
#define PRE_POUR  0 //Ԥ��ע
#define STR_POUR  1 //��ʼ��ע


//�����豸����
#define DEV_MAIN_TYPE   0  //��λ���豸����
#define DEV_APUMP_TYPE   1  //����Ѫ������
#define DEV_WAT_TYPE    2  //ˮԡ����
#define DEV_VPUMP_TYPE   3  //����Ѫ������
#define DEV_BAT_TYPE   4  //����豸����


//������־����
//Զ��1/����0/ϵͳ2
#define LOC_CTL 0 //����0
#define NET_CTL 1 //Զ��1
#define SYS_CTL 2 //�澯����/ϵͳ2
#define SWT_CTL 3 //Ԥ��ע�͹�ע�л�
#define WAT_TMP 4 //ˮ����
#define APUM_TMP 5 //AѪ����
#define VPUM_TMP 6 //VѪ����




//Ѫ������豸
#define MAX_PUM_GRP_COUNT 0
//ˮԡ����豸
#define MAX_WAT_GRP_COUNT 0

//�û����������������
#define CFG_BASIC_ITEM          0x00    //�������ý���

#define CFG_ARTERY_SPD_ITEM     0x01    //����Ѫ�ý���ת�ٲ�������
#define CFG_ARTERY_PRS_ITEM     0x02    //����Ѫ�ý���ѹ����������
#define CFG_ARTERY_FLW_ITEM     0x03    //����Ѫ�ý���������������

#define CFG_VEIN_SPD_ITEM     0x04    //����Ѫ�ý���ת�ٲ�������
#define CFG_VEIN_PRS_ITEM     0x05    //����Ѫ�ý���ѹ����������
#define CFG_VEIN_FLW_ITEM     0x06    //����Ѫ�ý���������������

#define CFG_WAT_ROOM_ITEM     0x07    //ˮԡ���ý���
#define CFG_ALM_PRM_ITEM      0x08    //�澯�����ý���

#define CFG_POUR_PRM_ITEM     0x09    //��ע�����ý���

#define CFG_PUL_PRM_ITEM     0x0A    //���������ý���

#define CFG_BAT_PRM_ITEM     0x0B    //��ز����ý���

//�澯������
#define ALM_LEV_H     1
#define ALM_LEV_M     2
#define ALM_LEV_L     3
#define ALM_LEV_A     4

#define ALM_LEV_N     0


//���ݸ澯���ݣ�(�澯ID: unAlmID)
#define MAX_ALM_REC_COUNT 6000         //ϵͳ���֧�ָ澯��¼����

//��������	����ѹ����	������	         ��עģʽ�£�16<����ѹ��<200 mmHg	��	1		����ѹ����	
#define H_P_ALM_ITEM_V_PRE_UP    0x01    //������-ѹ����
//��������	����ѹ����	������	         ��עģʽ�£�����ѹ��<0 mmHg	��	3		����ѹ���������쳣	
#define H_P_ALM_ITEM_V_PRE_DN    0x03    //������-ѹ����
//��������	����ѹ���쳣	��������	��עģʽ�£�����ѹ��>=200 mmHg	��	5		�����������쳣	
#define H_T_ALM_ITEM_V_PRE_SEN   0x05    //������-ѹ���������쳣
//��������	����Ѫ�¸�	������	����ѪҺ�¶�> 38��	��	7		����ѪҺ�¶ȸ�
#define H_P_ALM_ITEM_V_TMP_UP    0x07    //������-�¶ȸ�
//��������	���������� ������	             ��עģʽ�£���������<0 ml �� 9		����������
#define H_P_ALM_ITEM_V_FLO_DN    0x09    //������-�¶ȵ�
//��������	���������� ������	             ��עģʽ�£�1500ml/min<��������<2500ml/min	�� 12		����������
#define H_P_ALM_ITEM_V_FLO_UP    0x0C    //������-������
//��������	�������ư�ʧ��	��������	�������ư�����λ�����ư�ʧ��	�� 15		��������ģ��ʧ��
#define H_T_ALM_ITEM_V_DEV_TMT   0x0F    //�������ư�ʧ��
//��������     ������δ����	��������	������δ����	�� 17		������δ����
#define H_T_ALM_ITEM_V_PUM_TMT   0x11    //����Ѫ��δ����
//��������	�������쳣 ��������	�������޷�����	�� 19		�������쳣
#define H_T_ALM_ITEM_V_PUM_ERR   0x13    //�������쳣
//��������	�������ݱ���	������	��⵽ֱ����С��3mm������	�� 23		������·������
#define H_P_ALM_ITEM_V_BUBBLE    0x17    //������-������
//��������	����ѹ������������δ����	��������	����ѹ������������ʧ��	��	32		����ѹ������������δ����
#define M_T_ALM_ITEM_V_PRE_TMT   0x20    //����ѹ������������δ����
//��������	����Ѫѹ����ʧ�� ��������	����ѹ������ʧ�� �� 34		����ѹ�����ģ��ʧ��
#define M_T_ALM_ITEM_V_PRE_DEV_TMT   0x22    //����ѹ�����ģ��ʧ��
//��������	��������������δ����	��������	��������������δ����	�� 36		��������������δ����
#define M_T_ALM_ITEM_V_FLO_TMT   0x24    //��������������δ����
//��������	����ת�ٸ� ��������	����ת��>8000RPM	�� 38		����ת�ٸ�
#define M_T_ALM_ITEM_V_PRE_UP    0x26    //������ת�ٸ�
//��������	���������������쳣	��������	��������>=3000 ml �� <=-3000 ml	��	44		���������������쳣
#define M_T_ALM_ITEM_V_FLO_SEN   0x2C    //������-�����������쳣
//��������	����Ѫ�´�����δ����	��������	����Ѫ�´�����δ����	��	82		����Ѫ�´�����δ����
#define L_T_ALM_ITEM_V_TMP_TMT   0x52    //����Ѫ�´�����δ����
//��������	����Ѫ�´������쳣	��������	����ѪҺ�¶�> 100���<0��	��	84		����Ѫ�´������쳣
#define L_T_ALM_ITEM_V_TMP_SEN   0x54    //����Ѫ�´������쳣


//��������	����ѹ����	������	��עģʽ�£�85<����ѹ��<200 mmHg	��	2		����ѹ����	"���棺��������ɫ���������Ⱥ�ɫ����
#define H_P_ALM_ITEM_A_PRE_UP    0x02    //������-ѹ����
//��������	����ѹ����	��������	��עģʽ�£�����ѹ��<0 mmHg	��	4		�����������쳣	"���ƣ��л�Ԥ��עģʽ
#define H_T_ALM_ITEM_A_PRE_DN    0x04    //������-ѹ����
//��������	����ѹ���쳣	��������	��עģʽ�£�����ѹ��>=200 mmHg	��	6		�����������쳣	"���ƣ��л�Ԥ��עģʽ
#define H_T_ALM_ITEM_A_PRE_SEN   0x06    //������-ѹ���������쳣
//��������	����ѪҺ�¶ȳ���ֵ����	������	����ѪҺ�¶�> 38��	��	8		����ѪҺ�¶ȸ�	
#define H_P_ALM_ITEM_A_TMP_UP    0x08    //������-�¶ȸ�
//��������	����������	������	��עģʽ�£���������<0 ml	��	10		����������	
#define H_P_ALM_ITEM_A_FLO_DN    0x0A    //������-������
//��������	����������	������	��עģʽ�£�300ml/min<��������<2500 ml/min	��	13		����������	
#define H_P_ALM_ITEM_A_FLO_UP    0x0D    //������-������
//��������	�������ư�ʧ��	��������	�������ư�����λ�����ư�ʧ��	��	16		��������ģ��ʧ��	
#define H_T_ALM_ITEM_A_DEV_TMT   0x10    //�������ư�ʧ�� �������� H
//��������	������δ����	��������	������δ����	��	18		������δ����	
#define H_T_ALM_ITEM_A_PUM_TMT   0x12    //����Ѫ��δ����
//��������	�������쳣	��������	�������޷�����	��	20		�������쳣
#define H_T_ALM_ITEM_A_PUM_ERR   0x14    //�������쳣
//��������	�������ݱ���	������	��������⵽����	��	24		������·������	
#define H_P_ALM_ITEM_A_BUBBLE    0x18    //������-������
//��������	����Ѫѹ����������ʧ��	��������	����ѹ������������ʧ��	��	31		����ѹ������������δ����	
#define M_T_ALM_ITEM_A_PRE_TMT   0x1F    //����ѹ������������δ����
//��������	����Ѫѹ����ʧ��	��������	����ѹ�����ģ��ʧ��	��	33		����ѹ�����ģ��ʧ��	"���棺��������ɫ���������Ȼ�ɫ����
#define M_T_ALM_ITEM_A_PRE_DEV_TMT   0x21    //����ѹ�����ģ��ʧ��
//��������	��������������δ����	��������	��������������δ����	��	35		��������������δ����	
#define M_T_ALM_ITEM_A_FLO_TMT   0x23    //��������������δ����
//��������	����ת�ٳ���ֵ����	��������	����ת��>8000RPM	��	37		������ת�ٸ�	
#define M_T_ALM_ITEM_A_PRE_UP    0x25    //������ת�ٸ�
//��������	���������쳣	��������	��עģʽ�£���������>=3000 ml���߶�������<=-3000ml/min	��	43		���������������쳣	
#define M_T_ALM_ITEM_A_FLO_SEN   0x2B    //������-�����������쳣
//��������	����Ѫ�´�����δ����	��������	����Ѫ�´�����δ����	��	81		����Ѫ�´�����δ����
#define L_T_ALM_ITEM_A_TMP_TMT   0x51    //����Ѫ�´�����δ����
//��������	����Ѫ�´������쳣	��������	����ѪҺ�¶�> 100���<0��	��	83		����Ѫ�´������쳣	
#define L_T_ALM_ITEM_A_TMP_SEN   0x53    //����Ѫ�´������쳣



//ˮԡģ��	ˮԡ�¶ȸ�	��������	ˮԡ�¶�: 39.5��-100��	��	11		ˮԡ�¶ȸ�	
#define H_T_ALM_ITEM_WAT_TMP_UP    0x0B    //ˮԡ-�¶ȸ�
//ˮԡģ��	����ϵͳѹ������	��������	ˮ�ó���ѹ��>	��	14		����ϵͳѹ������ֵ	
#define H_T_ALM_ITEM_WAT_PPRE_UP   0x0E    //
//ˮԡģ��	ˮԡ�¶ȴ������쳣	��������	ˮԡ�¶�> 100���<0��	��	21		ˮԡ�¶ȴ������쳣	
#define H_T_ALM_ITEM_WAT_TMP_SEN   0x15    //ˮԡ-�¶ȴ������쳣
//ˮԡģ��	ˮԡ���ư�ʧ��	��������	ˮԡ���ư�����λ�����ư�ʧ��	��	22		ˮ�¿���ģ��ʧ��	
#define H_T_ALM_ITEM_WAT_DEV_TMT   0x16    //ˮԡ���ư�ʧ��
//ˮԡģ��	ˮ��Һλ��	��������	ˮ��ˮλ����50%	��	39		ˮ��Һλ��	
#define M_T_ALM_ITEM_WAT_LIN_DN    0x27    //ˮԡ-ˮλ��
//ˮԡģ��	ϵͳ���ȹ���	��������	ϵͳ���ȹ���	��	42		ϵͳ���ȹ���	
#define M_T_ALM_ITEM_WAT_FAN_ERR   0x2A    //ˮԡ-���ȹ���
//ˮԡģ��	ˮ��Һλ��	��ʾ��Ϣ	ˮ��Һλ����95%��������	��	NA		NA	
#define L_T_ALM_ITEM_WAT_LIN_UP    0x30    //ˮԡ-ˮλ��


//��Դģ��	��ص�����	��������	��ص�������20%	��	25		��ص�����	
#define H_T_ALM_ITEM_BAT_VOL_DN    0x19    //
//��Դģ��	δ��⵽���	��������	���ͨѶʧ������5s����	��	40		δ��⵽���	
#define M_T_ALM_ITEM_BAT_DEV_TMT   0x28    //
//��Դģ��	��س���	��������	�ŵ��¶ȸ���55�汨��������¶ȸ���45�汨��	��	41		��س���	
#define M_T_ALM_ITEM_BAT_TMP_UP    0x29    //
//��Դģ��	��Դ��δ����	��ʾ��Ϣ	����Դδ����	��	NA		��Դ��δ����	
#define M_T_ALM_ITEM_AC_LOS        0x31    //
//��Դģ��	���������ά������	��ʾ��Ϣ	�ӳ������ڿ�ʼ1����һ�Σ������������һ�μ��	��	NA		�����Ҫά������	
#define M_T_ALM_ITEM_BAT_DIS       0x32    //


#define MAX_ALARM_INFO_COUNT   12      //�澯���ݸ���
//������
#define ALM_ITEM_A_PRE_DN    0x01    //������-ѹ����
#define ALM_ITEM_A_PRE_UP    0x02    //������-ѹ����
#define ALM_ITEM_A_SPE_DN    0x03    //������-ת�ٵ�
#define ALM_ITEM_A_SPE_UP    0x04    //������-ת�ٸ�
#define ALM_ITEM_A_FLO_DN    0x05    //������-������
#define ALM_ITEM_A_FLO_UP    0x06    //������-������
#define ALM_ITEM_A_TMP_DN    0x07    //������-�¶ȵ�
#define ALM_ITEM_A_TMP_UP    0x08    //������-�¶ȸ�
#define ALM_ITEM_A_BUBBLE    0x11    //������-������
#define ALM_ERROE_A_TMP      0x13    //������-�¶��쳣

#define ALM_ITEM_A_TMP_SEN    0x15    //������-Ѫ�¶ȴ������쳣
#define ALM_ITEM_A_FLO_SEN    0x16    //������-�����������쳣
#define ALM_ITEM_A_PRE_SEN    0x17    //������-ѹ���������쳣
#define ALM_ITEM_A_SPE_SEN    0x18    //������-ת�ٴ������쳣



//������
#define ALM_ITEM_V_PRE_DN    0x09    //������-ѹ����
#define ALM_ITEM_V_PRE_UP    0x0A    //������-ѹ����
#define ALM_ITEM_V_SPE_DN    0x0B    //������-ת�ٵ�
#define ALM_ITEM_V_SPE_UP    0x0C    //������-ת�ٸ�
#define ALM_ITEM_V_FLO_DN    0x0D    //������-������
#define ALM_ITEM_V_FLO_UP    0x0E    //������-������
#define ALM_ITEM_V_TMP_DN    0x0F    //������-�¶ȵ�
#define ALM_ITEM_V_TMP_UP    0x10    //������-�¶ȸ�
#define ALM_ITEM_V_BUBBLE    0x12    //������-������
#define ALM_ERROE_V_TMP      0x14    //������-�¶��쳣

#define ALM_ITEM_V_TMP_SEN    0x19    //������-Ѫ�¶ȴ������쳣
#define ALM_ITEM_V_FLO_SEN    0x1A    //������-�����������쳣
#define ALM_ITEM_V_PRE_SEN    0x1B    //������-ѹ���������쳣
#define ALM_ITEM_V_SPE_SEN    0x1C    //������-ת�ٴ������쳣



//ˮԡ
#define ALM_ITEM_WAT_TMP_DN    0x20    //ˮԡ-�¶ȵ�
#define ALM_ITEM_WAT_TMP_UP    0x21    //ˮԡ-�¶ȸ�
#define ALM_ITEM_WAT_LIN_DN    0x22    //ˮԡ-ˮλ��
#define ALM_ITEM_WAT_LIN_UP    0x23    //ˮԡ-ˮλ��
#define ALM_ITEM_BLOOD_LIN_DN  0x24    //ѪҺҺλ��

#define ALM_ITEM_WAT_TMP_SEN    0x25    //ˮԡ-�¶ȴ������쳣
#define ALM_ITEM_WAT_LIN_SEN    0x26    //ˮԡ-ˮλ�������쳣
#define ALM_ITEM_WAT_BLO_SEN    0x27    //ˮԡ-Ѫλ�������쳣




#define ALM_ITEM_SUB_DEV_TMT   0xF0    //���������豸ͨ�ų�ʱ

//�澯����ֵ��
#define MAX_ALM_PRES_DIF_DN     20
#define MAX_ALM_PRES_DIF        50
#define MAX_ALM_FLOW_DIF        20
#define MAX_ALM_TMP_DIF         5

#define V_MAX_ALM_PRES_DIF_DN     10
#define V_MAX_ALM_PRES_DIF        20
#define V_MAX_ALM_FLOW_DIF        50
#define V_MAX_ALM_FLOW_DIF_DN     20

#define MAX_ALM_WAT_TMP_DIF     5 //�澯����ˮ�²�
#define MAX_ALM_WAT_LIN_DIF     2 //�澯����ˮλ��
#define MAX_ALM_BLOOD_LIN_DIF   2 //�澯����Ѫλ��
#define MAX_ALM_WAT_PRE_DIF     20 //�澯����ˮѹ��


#define SET_MAX_ALM_TMP_DIF     30 //Ѫ�º�ˮ�����ò�ֵ


//��ֹ�������
#define STP_ERR_USR_CNL_ERR		0x00	//�û��ֶ�ȡ��
#define STP_ERR_DEV_TMT_ERR		0x01	//�豸Ӧ��ʱ
#define STP_ERR_SUB_STP_ERR		0x02	//���豸����ֹͣ
#define STP_ERR_WAT_TMP_ERR		0x03	//ˮ�¸澯����ֹͣ

//У������
#define CAL_SET      0x01
#define CAL_SET_SND  0x81
#define CAL_SET_FAL  0x91


#define CAL_READ     0x02
#define CAL_SET_OK   0x03
#define CAL_READ_OK  0x04

//Ѫ�ô�������λ
#define PUM_TMP_LOS_BITS  0x0001 //�¶�δ����
#define PUM_FLO_LOS_BITS  0x0002 //����δ����
#define PUM_PRE_BOA_BITS  0x0004 //ѹ��С��δ���ӣ�ѹ���������쳣��
#define PUM_PRE_SEN_BITS  0x0008 //ѹ��������δ����
#define PUM_LOS_BITS      0x0010 //Ѫ��δ����
#define PUM_ERR_BITS      0x0020 //Ѫ���쳣

//ˮԡ��������λ
#define WAT_TMP_BITS     0x0001
#define WAT_LIN_UP_BITS  0x0002 //ˮλ����
//#define WAT_BLO_BITS  0x0004
#define WAT_FAN_BITS  0x0004



#define RUN_ARM_LINUX 0
#ifndef UINT8
#define UINT8 unsigned char
#endif

#ifndef INT8
#define INT8 signed char
#endif

#ifndef UINT16
#define UINT16 unsigned short
#endif

#ifndef INT16
#define INT16 signed short
#endif

#ifndef INT32
#define INT32 signed int
#endif

#ifndef UINT32
#define UINT32 unsigned int
#endif

#ifndef BYTE
#define BYTE   unsigned char
#endif

#ifndef BOOL
#define BOOL	UINT8
#endif


/*
#ifndef _WIN32
    #ifndef UINT32
    #define UINT32 unsigned long
    #endif

    #ifndef BYTE
    #define BYTE   unsigned char
    #endif

    #ifndef BOOL
    #define BOOL    UINT8
    #endif
#endif
#ifdef _WIN32
    #include <windef.h>
#endif
*/
#pragma pack(1)

typedef struct TIME_INFO
{
    UINT8 unYear;	//��ݼ���2000
    UINT8 unMonth;	//�·�(1-12)
    UINT8 unDay;	//��(1-31)
    UINT8 unHour;	//Сʱ(0 - 23)
    UINT8 unMinute;	//Сʱ(0 - 59)
    UINT8 unSecond;	//Сʱ(0 - 59)
}DateTime;

typedef struct DEV_UPD_FLAGS
{
    bool bBasicFlag;    //������������
    bool bArteryFlag;   //������������
    bool bVeinFlag;     //������������
    bool bWtrRoomFlag;  //ˮ���������
    bool bAlmSetFlag;   //�澯���ø���
    bool bPourSetFlag;   //�澯���ø���
    bool bPulSetFlag;    //�������ø���
    bool bBatSetFlag;    //������ø���
}DevUpdFlags;

//��������
#define MAX_PATH_SIZE       100
typedef struct BASIC_CONFIG_INFO
{
    char strDataPath[MAX_PATH_SIZE];    //��ʷ���ݱ���·��
    char strLogPath[MAX_PATH_SIZE];     //��־�ļ�����·��

    UINT8  unAPumCount; //����Ѫ������
    UINT8  unVPumCount; //����Ѫ������
    UINT8  unWatCount;  //ˮԡ����
    
    UINT8  unAlmEnFlag;//�澯�������û����
    UINT32 unMonSavTmt;//��ش洢ʱ�䣨�룩
}BasicCofnigInfo;

//Ѫ�ò�������
typedef struct BLOOD_PUMN_PARAM
{
    UINT8  unDevID;     //�豸ͨ��ID
    UINT8  unEnFlag;    //�Ƿ�����
    
    UINT16 unPress;     //ѹ��
    UINT16 unSpeed;     //ת��
    UINT16 unFlow;      //����

    UINT16 unPressLimt;     //ѹ��������ֵ
    UINT16 unSpeedLimt;     //ת��������ֵ
    UINT16 unFlowLimt;      //����������ֵ
    //UINT8  unSetVal[3];
}BloodPumnParam;

//�����豸����
typedef struct SET_DEV_PARAM
{
    UINT8  unIndex;       //������
    UINT16 unPrmVald;     //����ֵ
}SetDevPrm;

//������������
typedef struct SET_PUL_PARAM
{
    UINT8  unPumType;      //��״̬
    UINT8  unPulFreq;      //����Ƶ��
    UINT16 unPulVal;       //������Χ
}SetPulPrm;


//ˮԡ��������
typedef struct WARTER_ROOM_PARAM
{
    UINT8  unDevID;     //�豸ͨ��ID
    UINT8  unEnFlag;     //�Ƿ�����
    UINT16 unTmpVal;     //�¶�����

	UINT16 unTmpValLimt;   //�¶�������ֵ
}WatRooParam;

//��ز�������
typedef struct BATTERY_PARAM
{
    UINT8  unDevID;     //�豸ͨ��ID
    UINT8  unEnFlag;     //�Ƿ�����

}BatteryParam;


//�澯��ֵ
typedef struct DEV_ALM_PARAM
{
    INT16 unAlmUPresA;   //����ѹ�����޸澯
    INT16 unAlmLPresA;   //ѹ�����޸澯
    INT16 unAlmUTmpA;    //��Ѫ�����޸澯
    INT16 unAlmUSpeeA;   //ת�����޸澯
    //INT16 unAlmLSpee; //ת�����޸澯
    INT16  unAlmUFlowA;  //�����������߸澯
    INT16  unAlmLFlowA;  //���������͸߸澯
    INT16  unAlmBubbleA; //�������ݸ澯ֵ

    INT16  unAlmUPresV;  //����ѹ�����޸澯
    INT16  unAlmLPresV;  //����ѹ�����޸澯
    INT16  unAlmUTmpV;    //��Ѫ�����޸澯
    INT16  unAlmUSpeeV;   //ת�����޸澯
    INT16  unAlmUFlowV;  //�����������߸澯
    INT16  unAlmLFlowV;  //���������͸߸澯
    INT16  unAlmBubbleV; //�������ݸ澯ֵ
    
    INT16  unAlmUWatTmp; //ˮԡˮ�¸澯
    INT16  unAlmUWatLin;  //ˮλ�߸澯��ֵ
    INT16  unAlmLWatLin;  //ˮλ�͸澯��ֵ
    UINT8  unAlmBloodLin;//Ѫλ�澯
    INT16  unAlmUWatPre;   //ˮѹ��
    
}DevAlmParam;

typedef struct DEV_POUR_PARAM
{
    UINT16 unPourUPresA;  //����ѹ������ֹͣ
    //UINT16 unPourLPres;  //ѹ������ֹͣ
    UINT16 unPourUSpeeA;  //ת������ֹͣ
    INT16  unPourUTmpA;   //Ѫ�����ް�ȫֵ
    INT16  unPourUFlowA;  //������������ֹͣ
    INT16  unPourLFlowA;  //���������͸�ֹͣ

    UINT16 unPourUPresV;  //����ѹ������ֹͣ
    UINT16 unPourUSpeeV;
	INT16  unPourUTmpV;   //Ѫ�����ް�ȫֵ
    INT16  unPourUFlowV;  //������������ֹͣ
    INT16  unPourLFlowV;  //���������͸�ֹͣ
    
    INT16  unPourUWatTmp; //ˮԡˮ��ֹͣ
    INT16  unPourWatLin;  //ˮλֹͣ

}DevPourParam;


typedef struct DEV_CONFIG_INFO
{
    UINT16 unCheckSum;  //����У��
    UINT32 unVersion;   //�汾��
    UINT16 unInitFlag;  //��ʼ����־
    UINT8  unDevType;   //�豸����
    UINT8  unBloPumType; //Ѫ������
    UINT8  unArteryType; //����Ѫ������
    UINT8  unVeinType;   //����Ѫ������
    UINT8  unWatTRooType; //ˮԡ����
    BasicCofnigInfo basicCfgInfo;   //�������ò���
    BloodPumnParam  arteryParm;    //����Ѫ�ò���
    BloodPumnParam  veinParm;      //����Ѫ�ò���
    WatRooParam     watRooParam;   //ˮԡ��������
    DevAlmParam     devAlmParam;   //�豸�澯����
    DevPourParam    devPourParam;  //��ע���ò���
    BatteryParam    batParam;
}DevCofnigInfo;//�豸������������Ϣ

//Ѫ����澯
typedef struct PUM_GRP_ALM_BITS
{
    BYTE bPressUBits:1; //ѹ�����߸澯
    BYTE bPressLBits:1; //ѹ�����͸澯
    BYTE bPressErrBits:1; //ѹ���쳣
    BYTE bTmpUBits:1;	//Ѫ�¹��߸澯
    BYTE bFlowLBits:1;  //�����͸߸澯
    BYTE bFlowUBits:1;  //�������߸澯
    BYTE bPumTmtBits:1; //��/������δ����
    BYTE bPumErrBits:1; //Ѫ���쳣
	BYTE bBubblBits:1;	//Ѫ�����ݸ澯
	BYTE bPreLinBits:1;	//ѹ����������δ��
	BYTE bPreTmtBits:1;	//ѹ�������������豸ʧ��
	BYTE bFloTmtBits:1;	//����������δ��
	BYTE bSpeedUBits:1;	//ת�ٸ�
	BYTE bFlowSensorBits:1; //�����������쳣
	BYTE bTmpTmtBits:1;	 //�¶ȴ�����δ����
	BYTE bTmpSensorBits:1; //�¶ȴ������쳣
	
}PumGrpAlmBits;


//Ѫ����澯
typedef struct WAT_GRP_ALM_BITS
{
    BYTE bTmpUBits:1; //ˮԡ�¶ȹ��߸澯
    BYTE bWatPreUBits:1; //����ϵͳѹ��(ˮѹ)
    BYTE bTmpSensorBits:1; //ˮ�´������쳣
    BYTE bLinLBits:1; //ˮԡˮλ�͸߸澯
    BYTE bFanBits:1;  //ˮԡ���ȸ澯
    BYTE bLinUBits:1; //ˮԡˮλ���߸澯
    BYTE unUndefBits:2;
    //BYTE bTmpLBits:1; //ˮԡ�¶ȹ��͸澯
    //BYTE bBloodBit:1; //Ѫλ�澯
	//BYTE bLinSensorBits:1; //ˮλ�������쳣
	//BYTE bBloSensorBits:1; //Ѫλ�������쳣
}WatGrpAlmBits;
	
//���õ�Դ�澯
typedef struct BAT_ALM_BITS
{
	BYTE bBatSocBits:1; //��ص�����
	BYTE bACLosBits:1; //��Դ��δ����
	BYTE bBatTmpBits:1; //��س���
	BYTE bBatChkBits:1;  //���������ά������
	BYTE unUndefBits:4;
}BatAlmBits;


typedef struct DEV_ALM_BITS
{
    DateTime dtCreate;
	PumGrpAlmBits ApumGrpAlm; //����Ѫ��
	PumGrpAlmBits VpumGrpAlm; //����Ѫ��
	WatGrpAlmBits watGrpAlm;  //ˮԡ
	BatAlmBits    BatAlm;
	UINT32 unAPumModBits:1; //�������豸
	UINT32 unVPumModBits:1; //�������豸
	UINT32 unWatModBits:1;  //ˮԡ�豸
	UINT32 unBatModBits:1;  //����豸
    UINT32 unSysRestartBit:1; //�豸��������
    UINT32 unUndefBits:27;
    UINT32 unDevAlm1;      //Ԥ��
    UINT32 unDevAlm2;      //Ԥ��
}DevAlmBits;


//�澯���ݽṹ��
typedef struct ALM_ITEM
{
    DateTime dtCreate;	//�澯ʱ������ʱ��
    UINT8 unAlmID;	 	//�澯���ID
    UINT8 unAlmObjID;	//�澯����ID
    UINT8 unAlmSubObjID;//�澯�Ӷ���ID
    UINT8 unAlmFlag;    //�澯״̬:����ʾ����澯������ʾ�����澯
    INT32 unAlmVal;	//�澯ʱ����ǰֵ(������)�����Ȼ���ݲ�ͬ����(unAlmID)����ͬ
}AlmItem;

typedef struct ALM_ITEM_EX
{
    UINT8 unUpdFlag;
    AlmItem almItem;
}AlmItemEx;

//�����������豸��Ϣ
typedef struct PUMP_DEV_DATA
{
    UINT8  unRunFlg;    //����״̬
    UINT8  unPourSta;   //��ע״̬
    INT16  unTmpVal;	//�¶�(��)
	INT16  unFlowVal;	//����(ml)
    INT16  unPrssVal;	//ѹ��(mmHg)
    INT16  unSpeeVal;	//ת��(RPM)
    UINT8  unBubbVal;    //����(mm)
    UINT32 unDevCode;   //�豸״̬��
}PumpDevData;

//ˮԡ�����豸��Ϣ
typedef struct WAT_DEV_DATA
{
    UINT8  unRunFlg;    //����״̬
    UINT16 unTmpVal;	//�¶�(��)
	UINT16 unWatLine;	//ˮλ
	UINT8  unBloodSta; //Ѫλ״̬(0:�޸澯,1:�澯)
    UINT32 unDevCode;   //�豸״̬��
}WatDevData;

//Ԥ��ע����ע��Ϣ
typedef struct POUR_INFO
{
    UINT8 unStopType;	//ֹͣ����
    DateTime dtStart;	//����ʱ��
    DateTime dtEnd;		//ֹͣʱ��
    UINT32 unRecords;	//��¼����
    UINT32 unSectorID;	//����ID
    UINT32 unTotalTime; //��ʼ��ʱ�䣬����Ϊ��λ
}PourInfo;

//��ע����
typedef struct POUR_DATA
{
    //����
    UINT8  unADataType;  //������������
    UINT16 unASpeeSet;	 //����ת��(RPM)�趨ֵ
    UINT16 unAPrssSet;	 //����ѹ��(mmHg)�趨ֵ

    INT16  unATmpVal;	//�¶�(��)
    INT16  unAFlowVal;	//����(ml)
    INT16  unAPrssVal;	//ѹ��(mmHg)
    INT16  unASpeeVal;	//ת��(RPM)
    //ˮԡ
	INT16  unWatTmpSet; //ˮԡ�¶��趨ֵ
	INT16  unWatTmpVal; //ˮԡֵ(��)
	INT16  unWatLine;	//ˮλ
	INT16  unWatPreVal; //ˮѹ
    //����
    UINT8  unVDataType;   //������������
    UINT16 unVSpeeSet;	  //����ת��(RPM)�趨ֵ
    UINT16 unVPrssSet;	  //����ѹ��(mmHg)�趨ֵ
    
    INT16  unVTmpVal;	//�¶�(��)
    INT16  unVFlowVal;	//����(ml)
    INT16  unVPrssVal;	//ѹ��(mmHg)
    INT16  unVSpeeVal;	//ת��(RPM)
    
    DateTime dtSample;	//����ʱ��
}PourData;

//��ע��������
typedef struct POUR_TST_DATA
{
    PourInfo	tstInfo;	//��ע��Ҫ����
    PourData	tstData;	//��ע��������
}PourTstData;

//У������linmi20180502
//bCalIndex---��ʾУ����ֵ��ο�ֵ��
//0x00----У����ֵ, �����<unRefVal>��û����
//0x01----У���ο�ֵ, �����<unRefVal>��ʾ�ο�ֵ
typedef struct CAL_PRM
{
	UINT8  bCalItem;        //0-->ѹ��1-->�¶�
	UINT8  bCalIndex;      
	UINT32 unRefVal;
}CalPrm;


typedef struct SET_READ_CAL_PRM
{
    CalPrm bstCalPrm;
	UINT8  calPrmFlag;// 1:���óɹ���2:��ȡ�ɹ�
}SetReadCalPrm;


//������λ��״̬����λ��һ��
typedef struct SET_DEV_STA_SYNC
{
    UINT8  unDevSat;       //�豸״̬
    UINT8  unPourSta;      //��ע״̬
    INT16  unDevVal;       //�豸����
}SetDevStaSync;


#define MAX_PWD_SIZE    10
typedef struct PWD_PARAM_INFO
{
    UINT8 bPwdEnFlg;
    char  pAdminStrPwd[MAX_PWD_SIZE];
    char  pUserStrPwd[MAX_PWD_SIZE];
}PwdParamInfo;

//��λ�ϴ���Ϣ
#define MAX_INFO_SIZE    250
typedef struct DEV_UP_ERROE_INFO
{
    DateTime dtSave;	//�ɼ�ʱ��
    UINT8 unInfoLen;
    char  pDevErrInfo[MAX_INFO_SIZE];
}DevUpErrInfo;

typedef struct DEV_UP_ERROE_SAVE
{
    DateTime dtSave;	//����ʱ��
    DevUpErrInfo devUpErrInfo;
}DevUpErrSave;


//�����־��Ϣ
typedef struct MON_SAVE_INFO
{
    UINT32   unMonDataNum;   //�����������
    UINT32   unMonCurrPar;   //������ݵ�ǰָ��λ��
}MonSaveInfo;

//BatteryBascInfo
typedef struct BAT_BASC_INFO
{
	UINT16 unBatVol;  //�ܵ�ѹ  2BYTE,��λ 10mV�����ֽ���ǰ����ͬ
	INT16  unBatCur;  //����  2BYTE����λ 10mA  ͨ�������жϵ�س�ŵ�״̬�����Ϊ�����ŵ�Ϊ����
	UINT16 unLeftCap; //ʣ������  2BYTE����λ 10mAh 
    UINT16 unRatedCap;//�������  2BYTE����λ 10mAh 
	UINT16 unDshChgNum;//ѭ����ŵ����  2BYTE 
	UINT16 unMadDate;  //��������  2BYTE  ���� 2 ���ֽڴ��ͱ��� 0x2068,��������Ϊ��� 5 Ϊ��0x2028&0x1f = 8 ��ʾ����;�·ݣ�0x2068>>5��&0x0f=
                      //0x03 ��ʾ 3 ��;��ݾ�Ϊ 2000+ (0x2068>>9) = 2000 + 0x10 =2016;
    UINT16 unCllBln;  //����״̬  2BYTE  ÿһ�� bit ���ʾÿһ�����⣬0 Ϊ�رգ�1 Ϊ�� ��ʾ 1~16 ��
	UINT16 unCllBln_H;//����״̬_��  2BYTE  ÿһ�� bit ���ʾÿһ�����⣬0 Ϊ�رգ�1 Ϊ�� ��ʾ 17~32 �������֧�� 32 �� V0 �����������
	UINT16 unSafeStat;//����״̬  2BYTE  ÿһ�� bit ��ʾһ�ֱ���״̬��0 Ϊδ������1 �������� ���ע 1��
	UINT8  unVer;     //����汾  1byte  0x10 ��ʾ 1.0 �汾
	UINT8  unRSOC;    //RSOC  1byte  ��ʾʣ�������ٷֱ�
	UINT8  unFETMOS;  //FET ����״̬  1byte  MOS ָʾ״̬��bit0 ��ʾ��磬bit1 ��ʾ�ŵ磬0 ��ʾ MOS �رգ�1 ��ʾ��
	UINT8  unCllNum;  //��ش���  1byte  ��ش���
	UINT8  unNTCNum;//NTC ���� N  1byte  NTC ����
	UINT16 unNTCTmp[2];//2���¶ȴ�����
}BatBascInfo;

typedef struct BQ_BAT_BASC_INFO
{
	UINT16 unBatTmp;  
	UINT16 unBatVol;  //�ܵ�ѹ  2BYTE,��λ 10mV�����ֽ���ǰ����ͬ
	INT16  unBatCur;  //����  2BYTE����λ 10mA  ͨ�������жϵ�س�ŵ�״̬�����Ϊ�����ŵ�Ϊ����
    UINT8  unBatSoc;  //Soc
    UINT16 unCycNum;  //��ŵ����
}BqBatBascInfo;




//������־����
#define OPER_LOG_TYPE_BAS  1  //��������
#define OPER_LOG_TYPE_ALM  2  //�澯����
#define OPER_LOG_TYPE_POUR 3  //��ע����
#define OPER_LOG_TYPE_WAT  4  //ˮԡģ������
#define OPER_LOG_TYPE_APUM  5  //����Ѫ��ģ������
#define OPER_LOG_TYPE_VPUM  6  //����Ѫ��ģ������

#define OPER_CTRL_TYPE_WAT  7  //ˮԡ��ͣ

#define OPER_CTRL_SYS_UP    8  //������λ��
#define OPER_SYS_TYPE_REST  9  //����ϵͳ

#define OPER_LOG_TYPE_PUL  0x0A  //Ѫ��ģ����������
#define OPER_LOG_TYPE_BAT  0x0B  //�������


#define OPER_CTRL_TYPE_APUM  0x10  //��������ͣ
#define OPER_CTRL_TYPE_VPUM  0x20  //��������ͣ

#define OPER_CTRL_TYPE_APOUR  0x30  //������ע��Ԥ��ע�л�
#define OPER_CTRL_TYPE_VPOUR  0x40  //������ע��Ԥ��ע�л�

#define OPER_CTRL_REST_APOUR  0x50  //������λ����λ
#define OPER_CTRL_UP_APOUR    0x51  //����������λ��

#define OPER_CTRL_REST_VPOUR  0x60  //������λ����λ
#define OPER_CTRL_UP_VPOUR    0x61  //����������λ��

#define OPER_CTRL_REST_WATER  0x70  //ˮԡ��λ����λ
#define OPER_CTRL_UP_WATER    0x71  //����ˮԡ��λ��



//������־�ļ��洢��Ϣ
typedef struct OPER_LOG_INFO
{
    UINT16   unOperLogFileNum;   //������־�ļ�����
    UINT16   unOperLogCurrPar;   //������־�ļ���ǰָ��λ��
}OperLogInfo;

//������־
typedef struct OPER_LOG_BSC  //��������
{
    UINT8 unType;   //��������
    UINT8 unSite;   //Զ��/����/ϵͳ2
    DateTime dtCreate;  //����ʱ��
    
    UINT8  unAlmEnFlag[2]; //�澯ʹ��
    UINT32 unMonSavTmt[2]; //��֤ʹ��
    DateTime dtSystem[2];
}OperLogBasic;

typedef struct OPER_LOG_ALM  //�澯����
{
    UINT8 unType;   //��������
    UINT8 unSite;   //Զ��/����/ϵͳ2
    DateTime dtCreate;  //����ʱ��

    INT16 unAlmUPresA[2];   //����ѹ�����޸澯ֵ
    //INT16 unAlmLPresA[2];   //����ѹ�����޸澯ֵ
    INT16 unAlmUTmpA[2];   //����Ѫ��Ѫ�����޸澯ֵ
	INT16 unAlmUFlowA[2];    //�������޸澯ֵ
	INT16 unAlmLFlowA[2];    //�������޸澯ֵ
	INT16 unAlmBubbleA[2];    //���ݸ澯ֵ
	
    INT16 unAlmUPresV[2];   //����ѹ�����޸澯ֵ
    //INT16 unAlmLPresV[2];   //����ѹ�����޸澯ֵ
    INT16 unAlmUTmpV[2];   //����Ѫ��Ѫ�����޸澯ֵ
	INT16 unAlmUFlowV[2];    //�������޸澯ֵ
	INT16 unAlmLFlowV[2];    //�������޸澯ֵ
	INT16 unAlmBubbleV[2];	 //���ݸ澯ֵ

    INT16 unAlmUWatTmp[2];      //ˮԡ�¶����޸澯
    INT16 unAlmUWatLin[2];       //ˮԡˮλ�߸澯
    INT16 unAlmLWatLin[2];       //ˮԡˮλ�͸澯
    UINT8 unAlmBloodLin[2];       //ˮԡѪλ�澯
}OperLogAlm;

typedef struct OPER_LOG_POUR  //��ע����
{
    UINT8 unType;   //��������
    UINT8 unSite;   //Զ��/����/ϵͳ2
    DateTime dtCreate;  //����ʱ��

    INT16 unPourUPresA[2];   //����ѹ������ֵֹͣ
    INT16 unPourUSpeeA[2];   //����ת������ֵֹͣ
    INT16 unPourUTmpA[2];    //����Ѫ������ֵֹͣ
	INT16 unPourUFlowA[2];    //��������ֵֹͣ
	INT16 unPourLFlowA[2];    //��������ֵֹͣ
	
    INT16 unPourUPresV[2];   //����ѹ������ֵֹͣ
    INT16 unPourUSpeeV[2];   //����ת������ֵֹͣ
    INT16 unPourUTmpV[2];    //����Ѫ������ֵֹͣ
	INT16 unPourUFlowV[2];    //��������ֵֹͣ
	INT16 unPourLFlowV[2];    //��������ֵֹͣ

    INT16 unPourUWatTmp[2];      //ˮԡ�¶�����ֹͣ
    INT16 unPourWatLin[2];       //ˮԡˮλֹͣ
}OperLogPour;

typedef struct OPER_LOG_WAT_DEV  //ˮԡ�豸����
{
    UINT8 unType;   //��������
    UINT8 unSite;   //Զ��/����/ϵͳ2
    DateTime dtCreate;  //����ʱ��

    UINT8  unEnFlag[2];   //ʹ��״̬
    UINT16 unTmpVal[2];   //����ˮԡ�¶�
    UINT16 unTmpValLimt[2];   //����ˮԡ�¶���ֵ
}OperLogWatDev;

typedef struct OPER_LOG_BAT_DEV  //����豸����
{
    UINT8 unType;   //��������
    UINT8 unSite;   //Զ��/����/ϵͳ2
    DateTime dtCreate;  //����ʱ��

    UINT8  unEnFlag[2];   //ʹ��״̬
}OperLogBatDev;


typedef struct OPER_LOG_PUM_DEV  //Ѫ���豸����
{
    UINT8 unType;   //��������
    UINT8 unSite;   //Զ��1/����0/ϵͳ2
    DateTime dtCreate;  //����ʱ��

    UINT8  unEnFlag[2];   //ʹ��״̬
    UINT16 unPress[2];    //����Ѫ��ѹ��
    UINT16 unSpeed[2];    //����Ѫ��ת��
    UINT16 unPressLimt[2];    //Ѫ��ѹ������ֵ����
    UINT16 unSpeedLimt[2];    //Ѫ��ת������ֵ����
}OperLogPumDev; 

typedef struct OPER_LOG_CTL  //���Ʋ���(����/ֹͣ�ã�����/ֹͣˮԡ����ע״̬�л�����������)
{
    UINT8 unType;   //��������
    UINT8 unSite;   //Զ��/����/ϵͳ2
    DateTime dtCreate;  //����ʱ��
    
	UINT8  unOperType[2];    //�������� 1������0ֹͣ
	UINT8  unResult[2];      //������� 1�ɹ���2ʧ�� 0��
}OperLogCtl;


typedef struct MCU_VER_INFO
{
    char McuVer[15];
    char McuSn[16];
}McuVerInfo;

typedef struct MCU_UPD_STATE
{
    UINT8 McuUpdResult;
	McuVerInfo mcuVerInfo;
}McuUpdateState;

#define MAX_UPD_SND_DATA_LEN_EX 2048
typedef struct UPDATE_MCU
{
    UINT16  unTotalPkg;     //�����ݰ�
    UINT16  unPkgIndex;     //���ݰ����
    UINT8   unSendData[MAX_UPD_SND_DATA_LEN_EX];
}UpdateMcu;

typedef struct MCU_UPD_INFO
{
    UINT8  unMcuUpdState;
	UINT16 unTotalPkg;
	UINT16 unPkgIndex;     //���ݰ����
}McuUpdateInfo;


//����״̬���
typedef enum
{
    UpdNotStart = 0x00,         //��ʾδ��ʼ����
    UpdDoing = 0x01,            //��ʾ������
    UpdSuccess = 0x02,          //��ʾ��Ƭ���̼������ɹ�
    
    UpdFileOpenErr = 0x03,      //��ʾ�������ļ�ʧ��
    UpdFileChkErr  = 0x04,      //��ʾ�����ļ����ʧ��
    UpdFileReadChkErr = 0x05,   //��ʾ�����ļ������ʧ��
    UpdFileReadErr = 0x06,      //��ʾ�����ļ���ʧ��
    UpdSndPackErr  = 0x07,      //��ʾ����ʧ��3��
    UpdFindFileErr = 0x08       //��ʾ�����ļ��Ҳ���
    
}McuUpdEnum;


#pragma pack()


//������ʾ��ṹ����
#define MAX_STR_LEN   200
#define MAX_ERR_COUNT 10
#define DBG_SHOW      0
#define DLG_SHOW      1
#define ICON_INFO     0
#define ICON_ERROR    1

typedef struct ERR_INFO
{
    unsigned char unShowMode;
    unsigned char unErrIcon;
    char pString[MAX_STR_LEN];
}ErrInfo;

typedef struct DEV_BASIC_PARAM_CFG
{
    UINT16 unCheckSum;  //����У��
    UINT32 unVersion;   //�汾��

    UINT8  unDevType;   //�豸����
    UINT8  unBloPumType; //Ѫ������
    UINT8  unArteryType; //����Ѫ������
    UINT8  unVeinType;   //����Ѫ������
    UINT8  unWatTRooType; //ˮԡ����

    UINT8  unAPumCount; //����Ѫ������
    UINT8  unVPumCount; //����Ѫ������
    UINT8  unWatCount;  //ˮԡ����	

	UINT32 unMonSavCount; //��ش洢����
	UINT32 lComBrdVal[5];
	char   strComPort[5][MAX_COMPORT_SIZE];
	
}DevBasicParamCfg;



//ȫ��ͨ�ú����ӿ�
QString ValueToString(int lValue,int lFactScale,int lDotNum);
QDateTime DateTimeToQDateTime(DateTime* pdtValue,bool bTimeFlag);
QString DateTimeToString(DateTime* pDateTime,bool bTimeFlag = true);
void StringToDateTime(DateTime* pDateTime,QString strDateTime);
bool IsValidDateTime(DateTime* pDateTime);
void GetDateTime(DateTime* pDateTime);
UINT16 CreateCRCCheckSum(BYTE* pDataBuf,UINT32 unDataLen);
UINT16 CreateJBDCheckSum(BYTE* pDataBuf, UINT32 unDataLen);
void CtrlRs485RvcSnd(UINT8 unCtrl);

UINT32 GetMsTimer(timeb* pOldTimeb);

bool LoadDevTypeParam(QString& strError);
bool SaveDevTypeParam(QString& strError);
bool LoadConfigInfo(QString strPathName,QString& strError);
bool SaveConfigInfo(QString& strError);
void InitDefParam(void);
//extern bool LoadPwdInfo(QString strPathName,QString& strError);
int SystemEx(const char *cmdstring);
void SetMessageBoxFont(QMessageBox* pMsgBox, int w = 80, int h = 0);
void ShowInfo(QMessageBox* pMsgBox,QString strInfo,QString strTitle,enum QMessageBox::Icon icon);
void AddRowItem(QBoxLayout* pBoxLayout,QWidget* pInputItem,QString strLabel);
void AddItem(QFormLayout* pParentForm,QLineEdit* pEditInput,QString strLabel,QString strUnit,long lEditWidth);
ulong GetItemValue(QLineEdit* pLineEdit,long lScale = 1000);

UINT32  GetMaxTstInfoSctID(UINT32* punFileCount);//ȡ��������Ŀ¼���SectorID
bool ReadTestInfoEx(UINT32 unSectorID,PourInfo* pTestInfo);
bool ReadTestInfo(const char* pFileName,PourInfo* pTestInfo);
bool ReadTestData(char* pFileName,UINT32 unReadPos,BYTE* pDataBuf,UINT32 unDataLen);
bool GetTestDataFile(UINT32 unSectorID,char* pFileName);
bool DelTestDataFile(UINT32 unSectorID);
QString StopCodeToString(UINT32 unStopCode);
QString DataTypeToString(UINT8 unDataType);

UINT32  DoMsTimer(UINT32 unTimer,UINT32 unMsCount);
QComboBox*  CreateComboBox(QWidget * parent = 0);
QGroupBox*  CreateGroupBox(QWidget * parent = 0);
void LoadCompanyInfo(QString& strCoInfo);
QString AlmIDToName(UINT8 unAlmID);
QString  AlmFlagToString(UINT8 unAlmFlag);
QString AlmTmtIDToName(UINT8 unAlmObjID);
QString CheckOneAlmShow(UINT8 *unGetLevel);

void InitWatchdog(void);
void SetWatchdog(void);
//�����־�����ӿ�
bool SaveOperLogData(const char* saveBuf, int bufLen);
bool ReadOperLogData(char* readBuf, int bufLen, UINT16 logCerrPar);
void OPenOperLogInfoFile(void);
bool ReadOperLogInfo(QString pFileName);
bool SaveOperLogInfo(void);
bool LoadPwdInfo(QString strPathName,QString& strError);
bool SavePwdInfo(QString& strError);
int FindMCUSoftwareFile(char* fileName, char* devType, \
	                            char* ver , unsigned char unType);
void CleanDevAlm(UINT8 unDevtype);




//ȫ��ͨ�ñ����ӿ�
extern DevCofnigInfo   g_devConfigInfo;
extern DevCofnigInfo   g_devConfigInfo_Edt;//�û��༭
extern DevBasicParamCfg   g_devBasicPrmCfg;//�豸�������ò���

extern SetPulPrm       g_setPulPrm;


extern CAlarmDataFile* g_pAlmFile;
extern DevAlmBits g_devAlmBits;
extern PourData   g_DataAlarm;//��ǰ�澯��������ֵ



extern CMonShareData*   g_pCfgDataUI;   //�����������
extern CMonShareData*   g_pCfgDataNwk;

extern DevUpdFlags      g_devUpdFlags;  //�豸���ø��±�־λ

extern PourTstData      g_pourTstData;
extern AlmItemEx        g_almItemEx;
extern OperLogInfo      g_operLogInfo;
extern int  g_fdOperLogFle;//������־�洢��Ϣ
//�����־
extern PourData         g_DataTests[SAVE_MON_LOG_NUM+10];//�������
extern MonSaveInfo      g_MonSaveInfo;
extern PwdParamInfo    g_pwdCfgInfo;
extern bool    g_bLoginFlag;

extern int g_fWtchDog;
extern bool g_bMainWindRunFlg;//�������߳�������ʶ
extern bool g_bDataCopyFlag;

extern bool g_bWorkThRunRunFlg;//�����߳�������ʶ

extern SetReadCalPrm   g_setReadCalPrm[3];




#endif // INCLUDES_H
