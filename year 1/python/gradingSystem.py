print("This program print your grade. \n\n")
print("""
90 <= marks : Grade A
80 <= marks < 90 : Grade B
70 <= marks < 80 : Grade C
60 <= marks < 70 : Grade D
50 <= marks < 60 : Grade E
marks < 50 : Grade F
""")

n = int(input("Enter number of subjects : "))
m = float(input("Enter maximum marks : "))
total = 0
print()
for i in range(n):
    print("Enter marks of {0} subject".format(i + 1))
    sub = float(input())
    print()
    while( sub > m):
        print("You have entered a wrong marks. \nMarks obtained is greater than maximum marks.\n")
        print("Enter marks of {0} subject".format(i + 1))
        sub = int(input())
        print()

    total = sub + total

mm = m * n
per = (total/mm) * 100
print("Total marks obtained is :", total)
print("Total percentage obtained is :", per)

# while(m*n > total):
if(per >= 90) :
    print("Grade : A")
elif(per >= 80) :
    print("Grade : B")
elif(per >= 70) :
    print("Grade : C")
elif(per >= 60) :
    print("Grade : D")
elif(per >= 50) :
    print("Grade : E")
else:
    print("Grade : F")
    print("You are fail. Best of Luck next time.")

print('\nThanks.')