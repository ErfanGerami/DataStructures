def minimize_sum(arr):
    arr.sort()  # Sort the array in ascending order

    while True:
        if len(arr) == 1:
            # If there's only one element, increment it by 3
            arr[0] += 3
        else:
            # Increment the two smallest elements
            arr[0] += 1
            arr[1] += 1

        # Check if the array is now sorted
        if arr == sorted(arr):
            break

    return sum(arr)

# Example usage:
my_array = [4, 7, 1, 3, 9]
result = minimize_sum(my_array)
print(result)
