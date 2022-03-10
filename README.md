# turtlesim_pub_sub_srv_example
turtlesim publisher subscriber srv example

#1. Install turtlesim 

#2 Configure the workspace 
```
  $ source devel/setup.bash
```

#3. Run rosmaster:
```
  $ roscore
```
 
#4. Run turtlesim:
```
  $ rosrun turtlesim turtlesim_node
```
  
#5. Build example:
```
  $ catkin build
```
  
#6. Check C++ example
```
  $ rosrun turtlesim_pub_sub_srv_example node
```
  
#7. Check Python example
```
  $ rosrun turtlesim_pub_sub_srv_example move_node.py
```
