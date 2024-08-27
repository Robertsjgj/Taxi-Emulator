# Taxi Emulator

##Overview
This project is a taxi emulator developed in C, designed to simulate the movements of taxis on a console-based map. The emulator showcases taxi operations as they pick up and drop off passengers at various locations on the map. The map and the coordinate system are rendered using the conio.h library with console API functions.

##Features
Taxi Movement Simulation: The emulator visualizes taxi movement between buildings on a map, showing the process of picking up and dropping off passengers in real-time.

Data Management in Binary Format:
- Passenger and vehicle data are stored in binary files for enhanced efficiency, precision, and security compared to traditional text-based storage.
- Data operations such as initialization, modification, retrieval, and logical deletion are supported.

Optimized File Handling:
- The program utilizes dynamic editing of file headers and employs the fseek function to manage file operations effectively.
- This method avoids the need for line-by-line searching, significantly improving performance by directly accessing specific data locations within the binary files.

##File Structure
- Binary Files: Store data related to passengers and vehicles.
- Map Rendering: Utilizes conio.h to display the map and taxi movements.

##Technical Details
- Dynamic Header Management: Headers in the binary files are dynamically edited to keep track of active records and empty spots.
- Efficient Data Access: The use of fseek allows quick access to specific file locations, making data management operations more efficient.

##Getting Started
- Compile the Code: Ensure that your C environment supports the conio.h library, then compile the source files.
- Run the Emulator: Execute the compiled binary to see the taxi movement on the console-based map.
- Manage Data: Use the provided functions to initialize, delete, retrieve, and modify passenger and vehicle data as needed.

This project is a practical demonstration of integrating console-based graphics with efficient file management techniques in C programming.
