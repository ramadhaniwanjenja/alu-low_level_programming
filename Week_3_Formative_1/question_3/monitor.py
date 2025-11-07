import sensor_module
import matplotlib
matplotlib.use('Agg')  # Use non-interactive backend
import matplotlib.pyplot as plt
import time

temperature_data = []
humidity_data = []
battery_data = []
time_points = []

fig, (ax1, ax2, ax3) = plt.subplots(3, 1, figsize=(10, 8))

start_time = time.time()
iteration = 0

while time.time() - start_time < 30:
    data = sensor_module.get_sensor_data()
    
    temperature_data.append(data['temperature'])
    humidity_data.append(data['humidity'])
    battery_data.append(data['battery'])
    time_points.append(iteration * 2)
    
    ax1.clear()
    ax1.plot(time_points, temperature_data, 'r-')
    ax1.set_ylabel('Temperature (C)')
    ax1.set_title('Temperature Over Time')
    ax1.grid(True)
    
    ax2.clear()
    ax2.plot(time_points, humidity_data, 'b-')
    ax2.set_ylabel('Humidity (%)')
    ax2.set_title('Humidity Over Time')
    ax2.grid(True)
    
    ax3.clear()
    ax3.plot(time_points, battery_data, 'g-')
    ax3.set_ylabel('Battery (%)')
    ax3.set_xlabel('Time (seconds)')
    ax3.set_title('Battery Level Over Time')
    ax3.grid(True)
    
    plt.tight_layout()
    plt.savefig('sensor_monitor.png', dpi=100)
    
    time.sleep(2)
    iteration += 1

# Final plot
plt.tight_layout()
plt.savefig('sensor_monitor_final.png', dpi=100)
print(f"Monitoring complete! Final plot saved as 'sensor_monitor_final.png'")
print(f"Temperature range: {min(temperature_data):.1f}°C - {max(temperature_data):.1f}°C")
print(f"Humidity range: {min(humidity_data):.1f}% - {max(humidity_data):.1f}%")
print(f"Battery range: {min(battery_data)}% - {max(battery_data)}%")

