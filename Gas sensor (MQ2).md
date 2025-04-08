## Gas sensor (MQ2)

https://www.seeedstudio.com/Grove-Gas-Sensor-MQ2.html

Doing an A/B test with "no smoke" vs "smoke" should give you an idea about sensor levels to setup alerting automations.

Don't forget the [manufacturer recommendation](https://wiki.seeedstudio.com/Grove-Gas_Sensor-MQ2/) to leave it sitting, powered on, for the first 48 hours before you put it into production due to the way the sensor works.

<pre>
sensor:
  - platform: adc
    pin: 32 #PIN32 on AtomLite, PIN17 on PoESP32
    name: "Gas (confidence)"
    icon: mdi:fire
    update_interval: 10s
    filters:
      - multiply: 100
    unit_of_measurement: "%"
</pre>

Example output:

![image](https://github.com/user-attachments/assets/7d6de161-1af6-4d4c-8e1f-ba1a32ade076)
