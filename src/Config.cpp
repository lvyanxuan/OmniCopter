/*
 * Config.cpp
 *
 *  Created on: 2017年2月21日
 *      Author: jiawei
 */
#include "OmniCopter.h"
#include "Config.h"
#include "EEPROM.h"

bool Config::dataValid()
{
	char data1,data2;
	EEPROM.get(eepromValid,data1);
	EEPROM.get(eepromValid+1,data2);
	if(data1==0x51&&data2==0x15)
	{
		return true;
	}else
	{
		return false;
	}
}
void Config::setDataValid(bool status)
{
	char data1=0x51;
	char data2=0x15;
	if(status)
	{
		EEPROM.put(eepromValid,data1);
		EEPROM.put(eepromValid+1,data2);
	}else
	{
		EEPROM.put(eepromValid,0x00);
		EEPROM.put(eepromValid+1,0x00);
	}

}

void Config::loadConfig()
{
	if(!dataValid())
	{
		saveConfig();
		setDataValid(true);
		return;
	}
	EEPROM.get(percision*4,PERCISION);
	EEPROM.get(rcPercicion*4,RC_PERCISION);
	EEPROM.get(escStartPoint*4,ESC_START_POINT);
	EEPROM.get(desireConditionFMax*4,DESIRE_CONDITION_F_MAX);
	EEPROM.get(desireConditionTorqueMax*4,DESIRE_CONDITION_TORQUE_MAX);
	EEPROM.get(fPropMax*4,F_PROP_MAX);
	EEPROM.get(fPropMin*4,F_PROP_MIN);
	EEPROM.get(tAtt*4,TATT);
	EEPROM.get(tRate*4,TRATE);
	EEPROM.get(j*4,J);
	EEPROM.get(innerOuterRatio*4,INNER_OUTER_RATIO);
	EEPROM.get(desireBodyRateRatio*4,DESIRE_BODY_RATE_RATIO);
	EEPROM.get(desireConditionForceRatio*4,DESIRE_CONDITION_FORCE_RATIO);
	EEPROM.get(desireConditionTorqueRatio*4,DESIRE_CONDITION_TORQUE_RATIO);
	EEPROM.get(feedForwardRatio*4,FEED_FORWARD_RATIO);

}
void Config::saveConfig()
{
	EEPROM.put(percision*4,PERCISION);
	EEPROM.put(rcPercicion*4,RC_PERCISION);
	EEPROM.put(escStartPoint*4,ESC_START_POINT);
	EEPROM.put(desireConditionFMax*4,DESIRE_CONDITION_F_MAX);
	EEPROM.put(desireConditionTorqueMax*4,DESIRE_CONDITION_TORQUE_MAX);
	EEPROM.put(fPropMax*4,F_PROP_MAX);
	EEPROM.put(fPropMin*4,F_PROP_MIN);
	EEPROM.put(tAtt*4,TATT);
	EEPROM.put(tRate*4,TRATE);
	EEPROM.put(j*4,J);
	EEPROM.put(innerOuterRatio*4,INNER_OUTER_RATIO);
	EEPROM.put(desireBodyRateRatio*4,DESIRE_BODY_RATE_RATIO);
	EEPROM.put(desireConditionForceRatio*4,DESIRE_CONDITION_FORCE_RATIO);
	EEPROM.put(desireConditionTorqueRatio*4,DESIRE_CONDITION_TORQUE_RATIO);
	EEPROM.put(feedForwardRatio*4,FEED_FORWARD_RATIO);
}
void Config::decode(unsigned char data)
{
	static int count=0;
	static unsigned char buf[20];
	if(count==0&&data==0x51)
	{
		buf[count++]=data;return;
	}else if(count==1&&data==0x15)
	{
		buf[count++]=data;return;
	}else if(count==2)//数据名称位
	{
		buf[count++]=data;return;
	}else if(count==3)//数据位1
	{
		buf[count++]=data;return;
	}else if(count==4)//数据位2
	{
		buf[count]=data;
		int value=(int)buf[3];
		value<<=8;
		value+=buf[4];
		switch(buf[2])
		{
		case percision:
			setPercision(value/1000);
			break;
		case rcPercicion:
			setRcPercision(value/1000);
			break;
		case escStartPoint:
			setEscStartPoint(value/1000);
			break;
		case desireConditionFMax:
			setDesireConditionFMax(value/1000.0);break;
		case desireConditionTorqueMax:
			setDesireConditionTorqueMax(value/1000.0);break;
		case fPropMin:
			setPropMin(value/1000.0);break;
		case fPropMax:
			setPropMax(value/1000.0);break;
		case tAtt:
			setTatt(value/1000.0);break;
		case tRate:
			setTrate(value/1000.0);break;
		case j:
			setJ(value/1000.0);break;
		case innerOuterRatio:
			setInnerOuterRatio(value/1000);break;
		case desireBodyRateRatio:
			setDesireBodyRateRatio(value/1000.0);break;
		case feedForwardRatio:
			setFeedForwardRatio(value/1000.0);break;
		case desireConditionForceRatio:
			setDesireConditionForceRatio(value/1000.0);break;
		case desireConditionTorqueRatio:
			setDesireConditionTorqueRatio(value/1000.0);break;
		case 0x51:
			encode();
			//digitalWrite(LED_BUILTIN,LOW);
			break;
		}
		count=0;
		return;
	}
	count=0;
	return;
}
void Config::encode()
{
	SERIALNUM.print(percision);				SERIALNUM.print(",");SERIALNUM.print("percision");SERIALNUM.print(",");SERIALNUM.print("i");SERIALNUM.print(",");SERIALNUM.print(PERCISION);SERIALNUM.println(";");
	SERIALNUM.print(rcPercicion);				SERIALNUM.print(",");SERIALNUM.print("rcPercicion");SERIALNUM.print(",");SERIALNUM.print("i");SERIALNUM.print(",");SERIALNUM.print(RC_PERCISION);SERIALNUM.println(";");
	SERIALNUM.print(escStartPoint);			SERIALNUM.print(",");SERIALNUM.print("escStartPoint");SERIALNUM.print(",");SERIALNUM.print("i");SERIALNUM.print(",");SERIALNUM.print(ESC_START_POINT);SERIALNUM.println(";");
	SERIALNUM.print(desireConditionFMax);		SERIALNUM.print(",");SERIALNUM.print("desiredConditionFMax");SERIALNUM.print(",");SERIALNUM.print("d");SERIALNUM.print(",");SERIALNUM.print(DESIRE_CONDITION_F_MAX);SERIALNUM.println(";");
	SERIALNUM.print(desireConditionTorqueMax);	SERIALNUM.print(",");SERIALNUM.print("desiredConditionTorqueMax");SERIALNUM.print(",");SERIALNUM.print("d");SERIALNUM.print(",");SERIALNUM.print(DESIRE_CONDITION_TORQUE_MAX);SERIALNUM.println(";");
	SERIALNUM.print(fPropMin);					SERIALNUM.print(",");SERIALNUM.print("fPropMin");SERIALNUM.print(",");SERIALNUM.print("d");SERIALNUM.print(",");SERIALNUM.print(F_PROP_MIN);SERIALNUM.println(";");
	SERIALNUM.print(fPropMax);					SERIALNUM.print(",");SERIALNUM.print("fPropMax");SERIALNUM.print(",");SERIALNUM.print("d");SERIALNUM.print(",");SERIALNUM.print(F_PROP_MAX);SERIALNUM.println(";");
	SERIALNUM.print(tAtt);						SERIALNUM.print(",");SERIALNUM.print("tatt");SERIALNUM.print(",");SERIALNUM.print("d");SERIALNUM.print(",");SERIALNUM.print(TATT);SERIALNUM.println(";");
	SERIALNUM.print(tRate);					SERIALNUM.print(",");SERIALNUM.print("trate");SERIALNUM.print(",");SERIALNUM.print("d");SERIALNUM.print(",");SERIALNUM.print(TRATE);SERIALNUM.println(";");
	SERIALNUM.print(j);						SERIALNUM.print(",");SERIALNUM.print("j");SERIALNUM.print(",");SERIALNUM.print("d");SERIALNUM.print(",");SERIALNUM.print(J);SERIALNUM.println(";");
	SERIALNUM.print(innerOuterRatio);			SERIALNUM.print(",");SERIALNUM.print("innerOuterRatio");SERIALNUM.print(",");SERIALNUM.print("i");SERIALNUM.print(",");SERIALNUM.print(INNER_OUTER_RATIO);SERIALNUM.println(";");
	SERIALNUM.print(desireBodyRateRatio);		SERIALNUM.print(",");SERIALNUM.print("desireBodyRateRatio");SERIALNUM.print(",");SERIALNUM.print("d");SERIALNUM.print(",");SERIALNUM.print(DESIRE_BODY_RATE_RATIO);SERIALNUM.println(";");
	SERIALNUM.print(feedForwardRatio);			SERIALNUM.print(",");SERIALNUM.print("feedForwardRatio");SERIALNUM.print(",");SERIALNUM.print("d");SERIALNUM.print(",");SERIALNUM.print(FEED_FORWARD_RATIO);SERIALNUM.println(";");
	SERIALNUM.print(desireConditionForceRatio);SERIALNUM.print(",");SERIALNUM.print("desireConditionForceRatio");SERIALNUM.print(",");SERIALNUM.print("d");SERIALNUM.print(",");SERIALNUM.print(DESIRE_CONDITION_FORCE_RATIO);SERIALNUM.println(";");
	SERIALNUM.print(desireConditionTorqueRatio);SERIALNUM.print(",");SERIALNUM.print("desireConditionTorqueRatio");SERIALNUM.print(",");SERIALNUM.print("d");SERIALNUM.print(",");SERIALNUM.print(DESIRE_CONDITION_TORQUE_RATIO);SERIALNUM.println(";");
}


