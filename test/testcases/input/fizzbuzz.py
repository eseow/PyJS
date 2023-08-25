def fizzbuzz(n):
	for i in range(1, n + 1):
		if i % 3 == 0 and i % 5 == 0:
			print("FizzBuzz")
		elif i % 3 == 0:
			print("Fizz")
		elif i % 5 == 0:
			print("Buzz")
		else:
			print(i)

# Test the function
fizzbuzz(20)

"""
function fizzbuzz(var n){
    for(var i = 1;i < n + 1;i++){
        if(i % 3 == 0 && i % 5 == 0){
            console.log("FizzBuzz")            
        }else if(i % 3 == 0){
            console.log("Fizz")
        }else if(i % 5 == 0){
            console.log("Buzz")
        }else {
            console.log(i)
        }
    }
}


range(start, stop, step) -> _i = [start, start + step... stop]

for i in hello
for(var i : hello)

"""