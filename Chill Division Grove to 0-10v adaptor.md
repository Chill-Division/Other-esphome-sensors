## Chill Division Grove to 0-10v adaptor

<pre>
i2c:
  scan: true
  frequency: 50kHz
  sda: 16
  scl: 17
  
gp8403:
  id: chilldivision_gp8403
  voltage: 10V

output:
  - platform: gp8403
    id: output_1
    gp8403_id: chilldivision_gp8403
    channel: 0
    min_power: 0.05
    max_power: 1.0
  - platform: gp8403
    id: output_2
    gp8403_id: chilldivision_gp8403
    channel: 1
    min_power: 0.05
    max_power: 1.0

light:
  - platform: monochromatic
    name: "Light1"
    id: "Light1"
    output: output_1
    restore_mode: RESTORE_DEFAULT_OFF
  - platform: monochromatic
    name: "Light2"
    id: "Light2"
    output: output_2
    restore_mode: RESTORE_DEFAULT_OFF
</pre>
