from roberta import Hal
import time

hal = Hal()
print hal.exec_command('DiagTest')
print hal.exec_command('PlaySound SoundID 2')
print hal.sample_analog_sensors()
# print hal.sample_digital_sensor()
# print hal.sample_ultrasonic_sensor('right', 'center')
# print hal.sample_touch_sensor('left', 'front')
# print hal.sample_drop_sensor('right')
# print hal.sample_wall_sensor()
# print hal.exec_command('GetAccel')
# print hal.exec_command('GetDigitalSensors')

print hal.sample_accelerometer_sensor('y')
hal.exec_command('TestMode Off')
# time.sleep(10)
print hal.sample_analog_sensors()