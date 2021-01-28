function cleanup()
{
    echo "\rKilling all philosophers..."
    pkill philo
    echo "They're all dead !"
    exit
}

trap cleanup SIGINT

scriptdir=$(dirname $(realpath $0))
cd $scriptdir

if [ -z $1 ]
then
    echo "Need an philo name"
    exit 1
fi

ls $scriptdir/../$1 > /dev/null
if [ $? != "0" ]
then
    echo "No such philo"
    exit 1
fi

philo=../$1/$1


t=7
died=0

rm philo_*_log*
sleep 1
for i in {1..150}
do
    echo "Test n$i"
    $philo 5 800 200 200  >> $1_log_1 &
    sleep 0.1
    $philo 5 800 200 200  >> $1_log_2 &
    # sleep 0.1
    $philo 5 800 200 200  >> $1_log_3 &
    # sleep 0.1
    $philo 5 800 200 200  >> $1_log_4 &
    # sleep 0.1
    $philo 5 800 200 200  >> $1_log_5 &
    sleep $t
    pkill philo
done

# rm results 2> /dev/null
echo "$1 $(grep dying $1_log | wc -l) philosophers died over 50 tests" >> results