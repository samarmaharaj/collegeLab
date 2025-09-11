import time

print("This program call a function after sometime. \n\n")

def square(x):
    return x*x

num = int(input("Enter a number to square : "))
delay = int(input("Enter the delay time in seconds: "))
print("Calling the square function after {0} seconds.".format(delay))
time.sleep(delay)  # Wait for 5 seconds
result = square(num)

print("Result:", result)
