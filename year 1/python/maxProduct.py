print("This program print subarray whose product is maximum from a given list. \n\n")
def max_product_subarray(arr):
    if not arr:
        return None

    max_product = arr[0]
    current_max = arr[0]
    current_min = arr[0]

    for i in range(1, len(arr)):
        if arr[i] < 0:
            current_max, current_min = current_min, current_max

        current_max = max(arr[i], current_max * arr[i])
        current_min = min(arr[i], current_min * arr[i])

        max_product = max(max_product, current_max)

    return max_product

# Example usage
arr = [2, 3, -2, 4, 7, -1, -4]
result = max_product_subarray(arr)
print("Maximum product subarray:", result)