import csv as csv
import numpy as np
from pylab import *
from sklearn.svm import SVC
from sklearn.linear_model import SGDClassifier
from sklearn import tree
from sklearn.neighbors.nearest_centroid import NearestCentroid

csv_file = csv.reader(open('original.csv'))
header= csv_file.next()

data = []

for row in csv_file:
	data.append(row)

data = np.array(data)

for i in range(0,698):
	data[i,9] = data[i,9].replace('2',"0")
	data[i,9] = data[i,9].replace('4',"1")

xtrain = data[0:560,0:9].astype(np.float)
ytrain = data[0:560,9].astype(np.int)
xtest = data[560:699,0:9].astype(np.float)
ytest = data[560:699,9].astype(np.int)




clf = SGDClassifier(loss="modified_huber", penalty="elasticnet").fit(xtrain,ytrain)
#clf=SVC().fit(xtrain,ytrain)
#clf = NearestCentroid().fit(xtrain,ytrain)
#clf = tree.DecisionTreeClassifier().fit(xtrain,ytrain)
p = map(clf.predict,xtest)
#print ('test actual values',ytest)
#print
print p
score1="benign"
score2="malignant"

index=0
arr=[]

for index in range(len(p)):
	if p[index]==1:
		print 'tumor ',index+1,'is ',score1	
	else:
		print 'tumor',index+1,'is ',score2
	arr.append(p[index][0]-ytest[index])
	
#print type(p[0])

#testing accuracy

f11=0.0
f10=0.0
f01=0.0
f00=0.0
for j in range(0,138):
	if ytest[j]==0 and p[j]==0:
		f11=f11+1
	if ytest[j]==0 and p[j]!=0:
		f10=f10+1	
	if ytest[j]==1 and p[j]!=1:
		f01=f01+1
	if ytest[j]==1 and p[j]==1:
		f00=f00+1 
print 'accuracy of testing is',((f11+f00)/(f11+f00+f10+f01))*100



#for testing set
flag=0
flag1=0
scatter(data[560:699,0],ytest, s=220, facecolors='none', edgecolors='r',label="actual value")
for i in range(0,138):
	if int(ytest[i]) == int(p[i]):
		if flag ==0:
			scatter(data[560+i,0],p[i],s=140,color='lightskyblue',alpha=0.4,label=" correct prediction")
			flag=1
		else:
			scatter(data[560+i,0],p[i],s=140,color='lightskyblue',alpha=0.4)
for i in range(0,138):
	if int(ytest[i]) != int(p[i]):
		if flag1== 0:
			scatter(data[560+i,0],p[i],s=180,marker='x',color='black',alpha=0.9,label="incorrect prediction")
			flag1=1
		else:
			scatter(data[560+i,0],p[i],s=180,marker='x',color='black',alpha=0.9)

xticks([2,4,6,8,10])
yticks([-1,0,1,2],[r'$0$',r'$benign$',r'$benign$',r'$0$'],size=20)

legend(loc="upper right")

xlabel('Clump Thickness',size=15)
ylabel('Class',size=15,position=(2,0.5))
title('Stochastic Gradient Descent',size=18)
savefig('somdt.png', format='png', dpi=600)
show()


