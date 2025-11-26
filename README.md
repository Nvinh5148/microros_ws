# microros_ws

This repository contains a **micro-ROS** workspace configured for **ROS 2 Humble**. It is designed to control a robot vehicle system with the following functionalities:

* **Speed Control:** Controls 2 rear motors.
* **Steering Control:** Controls the steering angle.
* **Algorithm:** Uses **PID controller** for precise motor and steering adjustments.

## 🛠 Technology Stack

* **Framework:** ROS 2 Humble
* **Middleware:** micro-ROS
* **Hardware Target:** STM32 (via `micro_ros_stm32cubemx_utils`)

## 🔗 References

* **micro-ROS Official Guide:** [https://micro.ros.org](https://micro.ros.org)
* **STM32 CubeMX Utils:** [https://github.com/micro-ROS/micro_ros_stm32cubemx_utils](https://github.com/micro-ROS/micro_ros_stm32cubemx_utils)

---

## 🏗 Build System (Docker)

This project uses **Docker** to build the micro-ROS firmware and system. Ensure you have Docker installed on your machine.

*(Add your specific docker build command here if available, e.g., `docker run -it ...`)*

---

## 🚀 Usage Guide

Follow the steps below to start the micro-ROS agent and establish communication with your microcontroller.

### Step 1: Prepare Docker Permissions (Terminal 1)

Since the system uses Docker, you need to grant the necessary permissions to the Docker socket.

Open a new terminal (**T1**) and run:

```bash
sudo chmod 666 /var/run/docker.sock
```bash
### Step 2: Run micro-ROS Agent (Terminal 2)

Connect your STM32 board to the computer via USB. Ensure it is detected as `/dev/ttyUSB0`.

Open a second terminal (**T2**), navigate to your workspace, source the setup file, and run the agent:

# Navigate to the workspace
```bash
cd ~/microros_ws
```bash
# Source the ROS 2 environment
```bash
source install/local_setup.bash
```bash
# Run the micro-ROS agent via Serial connection
```bash
ros2 run micro_ros_agent micro_ros_agent serial --dev /dev/ttyUSB0
```bash
