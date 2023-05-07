import pickle


# make alphabetical list
import string
alphabet = list(string.ascii_lowercase)
alphabet = ["*","#"]+alphabet
print(alphabet)
# load it with hand folding and full open
# make alphabetical list 



with open('DecisionTree.pkl', 'rb') as file:  
    DecisionTree = pickle.load(file)
with open('K-NearestNeighbors.pkl', 'rb') as file:  
    KNearestNeighbors = pickle.load(file)
with open('RandomForest.pkl', 'rb') as file:  
    RandomForest = pickle.load(file)
print ("models loaded")


def predictReult(values):
    global alphabet
    for i in range(0, len(values)):
        values[i] = int(values[i])
    predicted_value  =KNearestNeighbors.predict([ 
        values
        ]) 
    predicted_text = alphabet[int(predicted_value[0])]
    # print(predicted_text)
    return predicted_text