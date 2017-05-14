import pandas as pd
import sys
from sklearn.cluster import KMeans

train = pd.read_csv("train_titanic_age.csv",header=None)


col=train[5]


#print(col)

#train[4] = train[4].fillna("S")

train[0] = train[0].map({'female': 1, 'male': 0})
train[5] = train[5].fillna(train[5].median())
train[4] = train[4].map({'S': 0, 'C': 1,'Q':2})
#print(train.head)

kmeans = KMeans(n_clusters=4, random_state=0).fit(col.reshape(-1,1))
print kmeans.labels_

train[7]=kmeans.labels_
print(train.head)

print kmeans.cluster_centers_

train.to_csv("train_titanic_age_cluster_4.csv",header=False)
