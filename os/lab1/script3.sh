# Start with: ./c.txt 

answer=""
input_string=""

while [[ $input_string != q ]]
do
read input_string
answer=$answer$input_string
done

echo $answer