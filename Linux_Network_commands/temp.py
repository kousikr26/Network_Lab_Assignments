import numpy as np
import matplotlib.pyplot as plt
import scipy.stats as stats
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import scipy.stats as stats
# file=open("ping_size.txt","r")
# lines=file.readlines()
# i=0
# x=[]
# y=[]
# sz=64
# while(i<=len(lines)):
    
#     try:
#         # print(list(lines[i+1].split('/'))[5])
#         y.append(float(list(lines[i].split('/'))[5]))
#         x.append(sz)
#         sz+=50
#     except:
#         break
#     i+=1
# file.close()

# fig, ax = plt.subplots(figsize=(10, 10))

# # We change the fontsize of minor ticks label 
# ax.tick_params(axis='both', which='major', labelsize=20)
# ax.tick_params(axis='both', which='minor', labelsize=20)
# ax.xaxis.set_major_locator(ticker.MultipleLocator(400))
# ax.xaxis.set_minor_locator(ticker.MultipleLocator(200))

# plt.plot(x,y)
# plt.title('Plot of RTT vs Packet Size',fontsize=20)

# plt.xlabel('Size',fontsize=20)
# plt.ylabel('RTT',fontsize=20)

# plt.show()

# #Q.3 c)
h=[]  
file=open("ping_1000p.txt","r")
lines=file.readlines()
for line in lines:
    line=list(line.strip().split())[6]
    latency=float(list(line.split('='))[1])
    h.append(latency)
h=np.array(h)

file.close()
yh=[]
file=open("ping_1000.txt","r")
lines=file.readlines()
for line in lines:
    line=list(line.strip().split())[6]
    latency=float(list(line.split('='))[1])
    yh.append(latency)
yh=np.array(yh)
yh.sort()
h.sort()
file.close()
# print(h)
# print(yh)

#print(h)
std = np.std(h) 
mean = np.mean(h)   
median = np.median(h)

ystd = np.std(yh) 
ymean = np.mean(yh)   
ymedian = np.median(yh)
print(mean,median,std,min(h),max(h))
print(ymean,ymedian,ystd,min(yh),max(yh))
plt.title('Normal plot',fontsize=20)

plt.xlabel('Latency',fontsize=15)
# plt.ylabel('Count',fontsize=15)
fit = stats.norm.pdf(yh, np.mean(yh), np.std(yh))
fit2 = stats.norm.pdf(h, np.mean(h), np.std(h))
plt.plot(yh,fit,label="ping -n")
plt.plot(h,fit2,label="ping -p ff00")
plt.legend(loc="upper right")
# plt.hist(yh,bins=100)
plt.show()
