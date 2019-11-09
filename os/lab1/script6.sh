# Start with: ./f.txt

if [[ "$HOME" == "$PWD" ]]
then
	echo $HOME
	exit 0
else
	echo "You're lose. Error"
	exit 1
fi