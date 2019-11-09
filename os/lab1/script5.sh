# Start with: ./e.txt 1

echo "1 - nano"
echo "2 - vi"
echo "3 - links"
echo "4 - exit"

while [[ true ]] 
do
    read cur_string
    case $cur_string in
        "1" )
            nano
	    ;;
	"2" )
	    vi
	    ;;
	"3" )
	    links
	    ;;
	"4" )
	    break
	    ;;
    esac
done