import pyformulas as pf
import matplotlib.pyplot as plt
import numpy as np
import time
import requests
import warnings
warnings.filterwarnings("ignore")

fig = plt.figure()

screen = pf.screen(title='Plot')

start = time.time()
y = [0 for i in range(100)]
for i in range(10000):
    t = time.time() - start

    x = np.linspace(t-3, t, 100)

    URL = "http://127.0.0.1:3000"
    r = requests.get(url = URL)
    data = r.json()
    print(data['value'])
    y.pop(0)
    y.append(data['value'])


    plt.xlim(t-3,t)
    plt.ylim(-3,3)
    plt.plot(x, y, c='black')

    # If we haven't already shown or saved the plot, then we need to draw the figure first...
    fig.canvas.draw()

    image = np.fromstring(fig.canvas.tostring_rgb(), dtype=np.uint8, sep='')
    image = image.reshape(fig.canvas.get_width_height()[::-1] + (3,))

    screen.update(image)

#screen.close()