import paho.mqtt.client as mqtt
import time 
import pickle
# make alphabetical list 
import string
alphabet = list(string.ascii_lowercase)
# make alphabetical list 
alphabet = ["hold","open"]+alphabet
# load it with hand folding and full open


print(alphabet)

with open('DecisionTree.pkl', 'rb') as file:  
    DecisionTree = pickle.load(file)
DecisionTree

with open('K-NearestNeighbors.pkl', 'rb') as file:  
    KNearestNeighbors = pickle.load(file)
KNearestNeighbors

with open('RandomForest.pkl', 'rb') as file:  
    RandomForest = pickle.load(file)
RandomForest

print ("models loaded")


# mqtt
broker_address="localhost" 
client = mqtt.Client() 
# mqtt


def predictReult(values):
    for i in range(0, len(values)):
        values[i] = int(values[i])
    
    predicted_value  =KNearestNeighbors.predict([ 
        values
        ]) 
    predicted_text = alphabet[int(predicted_value[0])]
    print(predicted_text)

def on_message(client, userdata, message):
    messageStr = str(message.payload.decode("utf-8"))
    # print("message : ", messageStr )
    AllSensorData = messageStr.split(":")
    FlexData = AllSensorData[:5]
    AcceleroData = AllSensorData[5:]
    print("FlexData:",FlexData)
    print("AcceleroData:",AcceleroData)
    predictReult(FlexData)
    # update_file(str(message.payload.decode("utf-8")))

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
        # local_time = read_time()
        # print("local time : ", local_time)
        # display_oled_time(local_time.split(" "))
        # compare_time(ring_time_list, local_time)
        # is_switch_on()
        time.sleep(0.5)
    except Exception as e:
        print(e)
client.loop_stop() 

# client.subscribe("ringtime/")
# client.loop_start() 
# retrain -  rsvhiju