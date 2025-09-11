print("This program create class of solid. \n\n")
class Cuboid:
    def __init__(self, length, width, height):
        self.length = length
        self.width = width
        self.height = height

    def calculate_surface_area(self):
        return 2 * (self.length * self.width + self.length * self.height + self.width * self.height)

    def calculate_volume(self):
        return self.length * self.width * self.height

# Example usage
y = 7, 8, 9

print(type(y))
cuboid = Cuboid(5, 3, 2)
surface_area = cuboid.calculate_surface_area()
volume = cuboid.calculate_volume()

print("Surface Area:", surface_area)
print("Volume:", volume)

# class solid:
#     def __init__(self , radius) :
#         self.radius= radius
#         self.area= 4*3.14*radius*radius
#         self.volume= 4/3*3.14*radius*radius*radius


# n= int(input("enter radius: "))
# s1= solid(n)
# print(s1.area)
# print(s1.volume)