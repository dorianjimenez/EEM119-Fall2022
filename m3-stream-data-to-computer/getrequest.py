# importing the requests library
import requests
import numpy as np
import matplotlib.pyplot as plt

plt.axis([0, 10, 0, 1])

while(True):

    URL = "http://127.0.0.1:3000"
    r = requests.get(url = URL)
    data = r.json()
    
    y = np.random.random()
    plt.scatter(i, y)
    plt.pause(0.05)

plt.show()
# api-endpoint

while(True):

    

    



print(data)