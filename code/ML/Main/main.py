import paho.mqtt.client as mqtt
import time 
from MachineLearningServices import predictReult 
from TextToSpeechModule import speak
# mqtt
broker_address="localhost" 
client = mqtt.Client() 
# mqtt
strVal = ""

handYAxisDown  = False
handXAxisRight = False
handClosed     = False

def IsHandOpen(_val_to_check):
    open="*"
    return _val_to_check==open
def IsHandClosed(_val_to_check):
    closed="#"
    return _val_to_check==closed
def IsHandYAxisDown(_Ay):
    return _Ay<-10000
def IsHandYAxisNormal(_Ay):
    return _Ay>-6000

def IsHandXAxisToRight(_Ax):
    return _Ax>10000
def IsHandxAxisNormal(_Ax):
    return _Ax>-6000 and _Ax<5000

def HandAlreadyClosed(fontSelected):
    global handClosed
    if(handClosed==False):
        return 0
    else:
        print("HandAlreadyClosed")
        if( IsHandOpen(fontSelected) ):
            handClosed=False
        return 1

def HandAlreadyDown(Ay):
    global handYAxisDown
    if(handYAxisDown==False):
        return 0
    else:
        print("HandAlreadyDown : ",Ay)
        if( IsHandYAxisNormal(Ay) ):
            print("IsHandYAxisNormal : ",Ay)
            handYAxisDown=False

def HandAlreadyRight(Ax):
    global handXAxisRight
    if(handXAxisRight==False):
        return 0
    else:
        print("HandAlreadyRight")
        if( IsHandxAxisNormal(Ax) ):
            handXAxisRight=False

def AcceleroDataProcessing(AcceleroData):
    Ay = int(AcceleroData[0])
    Ax = int(AcceleroData[1])
    # print(Ax, ' : ', Ay)
    return Ax,Ay

def on_message(client, userdata, message):
    global handYAxisDown
    messageStr = str(message.payload.decode("utf-8"))
    AllSensorData = messageStr.split(":")
    FlexData = AllSensorData[:5]
    AcceleroData = AllSensorData[5:]
    Ax, Ay = AcceleroDataProcessing(AcceleroData)
    fontSelected = predictReult(FlexData)
    closeStatus = HandAlreadyClosed(fontSelected)
    if(closeStatus==0):
        handDownStatus = HandAlreadyDown(Ay)
        if(handDownStatus==0):
            handRightStatus = HandAlreadyRight(Ax)
            if(handRightStatus==0):
                DataProccessing(fontSelected , Ax, Ay)
        
def DataProccessing(fontSelected , Ax, Ay):
    global strVal
    global handYAxisDown
    global handClosed
    global handXAxisRight
    print(fontSelected," : " ,strVal)
    # client.publish("data", fontSelected,":",strVal,":live")
    client.publish("glassData", fontSelected+":"+strVal+":live")

    # if(IsHandClosed(fontSelected)):
    #     print("the word is :" , strVal)
    #     speak(strVal)
    #     strVal=""    
    if(IsHandYAxisDown(Ay)):
        print("ifIsHandYAxisDown(Ay) :")
        if( ((IsHandOpen(fontSelected)) or (IsHandClosed(fontSelected))) ==False ):
            strVal+=fontSelected
            print("strVal : ", strVal )
            handYAxisDown=True
        if(IsHandClosed(fontSelected)):
            print("the word is :" , strVal)
            speak(strVal)
            strVal=""
        
    if(IsHandXAxisToRight(Ax)):
        print("if(IsHandXAxisToRight(Ax)):")
        BackSpaceHandler(fontSelected)
        SpaceBarHandler(fontSelected)
        handXAxisRight=True
        
    
def SpaceBarHandler(fontSelected):
    global strVal
    if(fontSelected=="p"):
        fontSelected=" "
        strVal+=fontSelected
        print("strVal : ", strVal )
def BackSpaceHandler(fontSelected):
    global strVal
    if(fontSelected=="a"):
        if(strVal!=""):
            strVal = strVal.rstrip(strVal[-1])
            print("strVal : ", strVal )

def on_disconnect(client, userdata, rc):
    print("disconnected")

client.on_message=on_message 
print("connecting to broker")
client.connect(broker_address) 
print("Subscribing to topic","message")
client.subscribe("message")
client.loop_start()

while(1):
    try:
        time.sleep(0.5)
    except Exception as e:
        print(e)
client.loop_stop() 