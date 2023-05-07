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


# Predict using the loaded model

print(DecisionTree, " : predicted : ",  DecisionTree.predict([
        [3203,3721,2607,2600,3646]
        ]) )

# Predict using the loaded model

print(KNearestNeighbors, " : predicted : ",  KNearestNeighbors.predict([
        [3203,3721,2607,2600,3646]
        ]) )

# Predict using the loaded model

print(RandomForest, " : predicted : ",  RandomForest.predict([
        [3203,3721,2607,2600,3646]
        ]) )
