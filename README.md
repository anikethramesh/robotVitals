# Robot Vitals and Robot Health

This is the repository used for all experiments using the robot vitals and robot health. All experiments were carried out using Ros Melodic and Gazebo 9. While Gazebo 11 can still render the worlds, we recommend using Gazebo 9.

# Building the robot vitals package

After cloning this repository, `cd` into the `robotVitals` directory and run `catkin_make` to build the robot vitals package. In some cases, you may have to delete the `build` and `devel` folders to successfully build the package.  After building the package, source the bash file by typing `source ./devel/setup.bash`

## Running Simulated Experiments

To run the experiment, run the following command - 
`roslaunch rv_test rv_sampler_emptyArena.launch`
The Gazebo directory has three arenas with four different levels of uneven terrain - empty, easy, medium and hard.  Each of these arenas can be used by changing to the appropriate gazebo file used on line 16 of the `rv_sampler_emptyArena.launch`launch file. 

To add noise to the Laser scanner -  Connect a joystick and then re-build and run the experiments. The laser noise can be activated by pressing the 'x' button the joystick.

Alternatively, to automatically trigger laser noise, navigate to `./robotVitals/tree/main/robotVitals/src/laser_noise)/CMakeLists.txt`, comment out line 113, unncomment line 112, rebuild and launch the experiment again. The duration of laser noise and the noise scale can be controlled by modifying the `laser_noise_spacebartrigger.cpp` file.
## Running Real Robot Experiments
In the real robot experiments, the gazebo stuff was removed, and only the rviz interface was used.  To run the corresponding launch file type:
`roslaunch rv_test rv_sampler_realRobot.launch`

The experiments were carried out using a husky robot but this should ideally work for other robots as long as the corresponding robot libraries are added to the `catkin_ws`

## Experimental Data Analysis

In the folder named `DataAnalysis` there are two jupyter notebooks that were used for analysing the experiments. One for simulation and the other for real experiments. Follow these instructions to run these for your experiments:

 1. After each experimental trial, save the rosbags into a common directory
 2. Point the jupyter lab notebook to the directory with all the rosbags
 3. Alternatively, if the rosbags are saved as pickle files, they can be used directly.

## Using Robot Vitals in real time:

The launch file `rv_realtime_husky.launch` demonstrates a setup to monitor the robot health and robot vitals in real time. After running that launch file, give the robot a waypoint. The robot health can then easily be visualised. Open a new terminal window and run `rosrun rqt_plot rqt_plot`. In the `rqt_plot` window choose the topic `/robotHealth` to visualise the robot health trend
