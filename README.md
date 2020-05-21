# PID Controller Project
---
The goals / steps of this project are the following:
* Implement PID equations
* Iterate to fine-tune parameters through testing
* Develop an understanding of one controller type
* Use the simulator to test PID parameters
* Summarize the results with a written report


[//]: # (Image References)

[image1]: report_images/Sim1.JPG

---
## Project Overview
Using a driving simulator that provides the cross track error (CTE) and velocity in mph, I designed and tuned a PID controller in C++ that controls the vehicle to be near the center of the lane when driving around the track. My controller controlled the steering adjustments on each iteration.

* `main.cpp` - communicates with the simulator and receives error, speed, and angle measurements. It calls PID functions to adjust the steering angle
* `tools.cpp` - contains the PID object that can initialize, calculate errors, and return a PID controller output

### Tuning Parameters
Several methods could've been used to tune the parameters, such as manual tuning, Zieglor-Nichols tuning, SGD, Twiddle. I used manual tuning for its ease of implementation (less up-front time but can be time consuming to obtain precise values. This helped me understand the effect of each PID parameter.

The influence can be summarized into a table:
| Parameter | Rise Time | Overshoot | Settling Time | Steady-state error |
|---|---|---|---|---|
| Kp | Decrease | Increase | Small change | Decrease |
| Ki | Decrease | Increase | Increase | Decrease |
| Kd | Small change | Decrease | Decrease | No change |

#### P - Propotional
This parameter controls the error proportionally. Increasing the proportional gain has the effect of proportionally increasing the control signal for the same level of error. Setting only P control is agressive and has oscillations.

#### I - Integral
This parameter controls the accumulating error. Addition of this term reduces the steady state error. If there is a bias in the system, the integrator builds and builds, thereby increasing the control signal and driving the error down. 

#### D - Derivative
This parameter controls the rate of change of error. Addition of this term reduces the oscillary effect in  the system. With derivative control, the control signal can become large if the error begins sloping upward, even while the magnitude of the error is still relatively small. This anticipation tends to add damping to the system, thereby decreasing overshoot.

I followed the approach below to manually tune my PID controller parameters:

* Set Kp, Ki, and Kd to 0
* Increase Kp until it provides a marginally stable oscillation
* Increase Ki to remove the systematic bias error, which also removes the oscillations (lead)
* Increase Kd until the overshoot at the start is minimized and to improve the trajectory smoothness(lag)
* Test around the Kp, Ki, Kd parameters until the squared error is minimized and the motion is visually smooth

An example of the output is shown below:

![][image1]
---
## Try it yourself!

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

Tips for setting up your environment can be found [here](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/0949fca6-b379-42af-a919-ee50aa304e6a/lessons/f758c44c-5e40-4e01-93b5-1a82aa4e044f/concepts/23d376c7-0195-4276-bdf0-e02f1f3c665d)

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1(mac, linux), 3.81(Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.
