# Start with: ./d.txt

read input_string

let count=1
let isOdd=$input_string%2

while [[ $isOdd -eq 1 ]]
do
let count=count+1
read input_string
let isOdd=$input_string%2
done

echo $count