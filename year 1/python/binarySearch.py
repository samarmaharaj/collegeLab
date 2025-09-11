print("This program perform binary search. \n\n")

def binarySearch(arr, low, high, element):
    if high >= low:
        mid = (low + high)//2
        # print(mid)
        if arr[mid] == element:
            return mid
        
        elif arr[mid] > element:
            high = mid - 1
            return binarySearch(arr, low, high, element)
        
        else:
            low = mid + 1
            return binarySearch(arr, low, high, element)

    else:
        return -1
    
list = [int(x) for x in input("Enter element: ").split(" ")]
print(list)
element = int(input("Enter element to search for : "))
result = binarySearch(list, 0, len(list)-1, element)

if result != -1:
    print("Element {} is found at {} position!".format(element, result+1))
else:
    print("element is not found!")