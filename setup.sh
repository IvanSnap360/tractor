catkin_make
# echo "$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
echo "source $( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )/devel/setup.bash" >> ~/.bashrc
bash