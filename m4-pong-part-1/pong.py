# PONG CODE FROM https://www.geeksforgeeks.org/create-pong-game-using-python-turtle/
# MULTITHREADING CODE FROM https://stackoverflow.com/questions/27021440/python-requests-dont-wait-for-request-to-finish

# To run:
#    1. Run Node Server
#    2. Plug in and run Arduino
#    3. Run the pong.py


# Movement
#  Arduino Pointing Nose UP: Paddle Up
#  Arduino Pointing Nose DOWN: Paddle Down
#  Arduino Face Up: Paddle Stay

# Import required library
import turtle
import requests 
import threading



# Create screen
sc = turtle.Screen()
sc.title("Pong game")
sc.bgcolor("white")
sc.setup(width=1000, height=600)
sc.delay(1)






# Right paddle
right_pad = turtle.Turtle()
right_pad.speed(0)
right_pad.shape("square")
right_pad.color("black")
right_pad.shapesize(stretch_wid=6, stretch_len=2)
right_pad.penup()
right_pad.goto(400, 0)


# Ball of circle shape
hit_ball = turtle.Turtle()
hit_ball.speed(30)
hit_ball.shape("circle")
hit_ball.color("blue")
hit_ball.penup()
hit_ball.goto(0, 0)
hit_ball.dx = 5
hit_ball.dy = -5


# Initialize the score
right_player = 0


# Displays the score
sketch = turtle.Turtle()
sketch.speed(0)
sketch.color("blue")
sketch.penup()
sketch.hideturtle()
sketch.goto(0, 260)
sketch.write("Right_player: 0",
			align="center", font=("Courier", 24, "normal"))


data = 0
def send_req():
	while(True):
		# GET ARDUINO DATA
		URL = "http://127.0.0.1:3000"
		r = requests.get(url = URL)
		global data
		data = r.json()['value']
	

threading.Thread(target=send_req).start()

while True:

	

	right_pad.sety(data * -240)
	
	sc.update()

	hit_ball.setx(hit_ball.xcor()+hit_ball.dx)
	hit_ball.sety(hit_ball.ycor()+hit_ball.dy)

	# Checking borders
	if hit_ball.ycor() > 280:
		hit_ball.sety(280)
		hit_ball.dy *= -1

	if hit_ball.ycor() < -280:
		hit_ball.sety(-280)
		hit_ball.dy *= -1

	if hit_ball.xcor() < -500:
		hit_ball.setx(-500)
		hit_ball.dx *= -1

	if hit_ball.xcor() > 500:
		hit_ball.goto(0, 0)
		hit_ball.dy *= -1
		right_player -= 1
		sketch.clear()
		sketch.write("Right_player: {}".format(
					right_player), align="center",
					font=("Courier", 24, "normal"))



	# Paddle ball collision
	if (hit_ball.xcor() > 360 and hit_ball.xcor() < 370) and (hit_ball.ycor() < right_pad.ycor()+65 and hit_ball.ycor() > right_pad.ycor()-65):
		hit_ball.setx(360)
		hit_ball.dx*=-1
		right_player += 1
		sketch.clear()
		sketch.write("Right_player: {}".format(
								right_player), align="center",
								font=("Courier", 24, "normal"))

