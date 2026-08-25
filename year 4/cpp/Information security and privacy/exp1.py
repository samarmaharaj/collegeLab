# Program to find the GCD of two integers using the Euclidean algorithm

num1 = int(input("Enter first integer: "))
num2 = int(input("Enter second integer: "))

def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a

result = gcd(num1, num2)
print(f"The GCD of {num1} and {num2} is: {result}")


def extended_gcd(a, b):
    if b == 0:
        return a, 1, 0
    else:
        gcd_val, s1, t1 = extended_gcd(b, a % b)
        s = t1
        t = s1 - (a // b) * t1
        return gcd_val, s, t

gcd_result, s, t = extended_gcd(num1, num2)
print(f"The GCD of {num1} and {num2} is: {gcd_result}")
print(f"S (coefficient of {num1}): {s}")
print(f"T (coefficient of {num2}): {t}")
print(f"Verification: {num1} * {s} + {num2} * {t} = {num1 * s + num2 * t}")