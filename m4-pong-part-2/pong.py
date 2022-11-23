# PONG CODE FROM https://www.geeksforgeeks.org/create-pong-game-using-python-turtle/
# MULTITHREADING CODE FROM https://stackoverflow.com/questions/27021440/python-requests-dont-wait-for-request-to-finish

# To run:
#    1. Run Node Server
#    2. Plug in and run Arduino
#    3. Run the pong.py

# Gesture
#  Arduino Face UP: Paddle Up
#  Arduino Face DOWN: Paddle Down
#  Arduino on its SIDE: Paddle Stay


# Import required library
import turtle
import requests 
import threading
from time import sleep



# Create screen
sc = turtle.Screen()
sc.title("Pong game")
sc.bgcolor("white")
sc.setup(width=1000, height=600)
sc.delay(1)


# Left paddle	
left_pad = turtle.Turtle()	
left_pad.speed(0)	
left_pad.shape("square")	
left_pad.color("black")	
left_pad.shapesize(stretch_wid=6, stretch_len=2)	
left_pad.penup()	
left_pad.goto(-400, 0)



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
left_player = 0
right_player = 0


# Displays the score
sketch = turtle.Turtle()
sketch.speed(0)
sketch.color("blue")
sketch.penup()
sketch.hideturtle()
sketch.goto(0, 260)
sketch.write("Left_player : 0 Right_player: 0",	
			align="center", font=("Courier", 24, "normal"))


# Functions to move paddle vertically	
def paddleaup():	
	y = left_pad.ycor()	
	y += 45	
	left_pad.sety(y)	
def paddleadown():	
	y = left_pad.ycor()	
	y -= 45
	left_pad.sety(y)	
def paddlebup():	
	y = right_pad.ycor()	
	y += 45	
	right_pad.sety(y)	
def paddlebdown():	
	y = right_pad.ycor()	
	y -= 45
	right_pad.sety(y)



data_p1 = 0
control_p1 = 0
def send_req_p1():
	while(True):
		# GET ARDUINO DATA
		URL = "http://127.0.0.1:3000"
		r = requests.get(url = URL)
		global data_p1
		global control_p1
		data_p1 = r.json()['value']

		if(data_p1 > 0.7): 
			control_p1 = 1
		elif(data_p1 < -0.7):
			control_p1 = -1
		else:
			control_p1 = 0



data_p2 = 0
control_p2 = 0
def send_req_p2():
	while(True):
		# GET ARDUINO DATA
		URL = "http://127.0.0.1:3001"
		r = requests.get(url = URL)
		global data_p2
		global control_p2
		data_p2 = r.json()['value']

		if(data_p2 > 0.7): 
			control_p2 = 1
		elif(data_p2 < -0.7):
			control_p2 = -1
		else:
			control_p2 = 0


		

		
	
threading.Thread(target=send_req_p1).start()
threading.Thread(target=send_req_p2).start()

while True:

	if(control_p1 == 1):
		paddlebup()
		control = 0
	elif(control_p1 == -1):
		paddlebdown()
		control = 0
	
	if(control_p2 == 1):
		paddlebup()
		control = 0
	elif(control_p2 == -1):
		paddlebdown()
		control = 0
	
	
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

	if hit_ball.xcor() > 500:
		hit_ball.goto(0, 0)
		hit_ball.dy *= -1
		left_player += 1
		sketch.clear()
		sketch.write("Left_player : {}    Right_player: {}".format(
                      left_player, right_player), align="center",
                      font=("Courier", 24, "normal"))

	if hit_ball.xcor() < -500:
		hit_ball.goto(0, 0)
		hit_ball.dy *= -1
		right_player += 1
		sketch.clear()
		sketch.write("Left_player : {}    Right_player: {}".format(
                                 left_player, right_player), align="center",
                                 font=("Courier", 24, "normal"))



	# Paddle ball collision
	if (hit_ball.xcor() > 360 and hit_ball.xcor() < 370) and (hit_ball.ycor() < right_pad.ycor()+65 and hit_ball.ycor() > right_pad.ycor()-65):
		hit_ball.setx(360)
		hit_ball.dx*=-1

	if (hit_ball.xcor()<-360 and hit_ball.xcor()>-370) and (hit_ball.ycor()<left_pad.ycor()+65 and hit_ball.ycor()>left_pad.ycor()-65):
		hit_ball.setx(-360)
		hit_ball.dx*=-1

